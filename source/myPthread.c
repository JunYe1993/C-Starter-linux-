#include "myPthread.h"

// 計數器
int counter = 0;

// 加入 Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// 旗標
sem_t semaphore;

int
pthreadTest_1()
{
    pthread_t t; // 宣告 pthread 變數
    pthread_create(&t, NULL, myPthread_func_chlid_1, "Child"); // 建立子執行緒

    // 主執行緒工作
    for(int i = 0;i < 3;++i) {
        printf("Master\n"); // 每秒輸出文字
        sleep(1);
    }

    pthread_join(t, NULL); // 等待子執行緒執行完成
    return 0;
}

int
pthreadTest_2()
{
    pthread_t t;
    void *ret; // 子執行緒傳回值
    int input[2] = {1, 2}; // 輸入的資料

    // 建立子執行緒，傳入 input 進行計算
    pthread_create(&t, NULL, myPthread_func_chlid_2, (void*) input);

    // 等待子執行緒計算完畢
    pthread_join(t, &ret);

    // 取得計算結果
    int *result = (int *) ret;

    // 輸出計算結果
    printf("%d + %d = %d\n", input[0], input[1], result[0]);

    // 釋放記憶體
    free(result);

    return 0;
}

int
pthreadTest_3()
{
    pthread_t t;
    myPthread_data data;

    data.a = 1;
    data.b = 2;

    // 建立子執行緒，傳入 data 進行計算
    pthread_create(&t, NULL, myPthread_func_chlid_3, (void*) &data);

    // 等待子執行緒計算完畢
    pthread_join(t, NULL);

    // 從 data.result 取回計算結果
    printf("pthreadTest_3 : %d + %d = %d\n", data.a, data.b, data.result);

    return 0;
}

int
pthreadTest_4()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, myPthread_func_chlid_4, NULL);
    pthread_create(&t2, NULL, myPthread_func_chlid_4, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

int
pthreadTest_5()
{
    // 初始化旗標，僅用於本行程，初始值為 0
    sem_init(&semaphore, 0, 0);

    pthread_t t;
    pthread_create(&t, NULL, myPthread_func_chlid_5, NULL);

    // 送出兩個工作
    printf("Post 2 jobs.\n");
    sem_post(&semaphore);
    sem_post(&semaphore);
    sleep(4);

    // 送出三個工作
    printf("Post 3 jobs.\n");
    sem_post(&semaphore);
    sem_post(&semaphore);
    sem_post(&semaphore);

    pthread_join(t, NULL);

    return 0;
}

void* 
myPthread_func_chlid_1(void* data)
{
    char *str = (char*) data; // 取得輸入資料
    for(int i = 0;i < 3;++i) {
        printf("%s\n", str); // 每秒輸出文字
        sleep(1);
    }
    pthread_exit(NULL); // 離開子執行緒
}

void* 
myPthread_func_chlid_2(void *arg) 
{
   int *input = (int *) arg; // 取得資料
   int *result = malloc(sizeof(int) * 1); // 配置記憶體
   result[0] = input[0] + input[1]; // 進行計算
   pthread_exit((void *) result); // 傳回結果
}

void* 
myPthread_func_chlid_3(void *arg) 
{
   myPthread_data *data=(myPthread_data *)arg; // 取得資料

   int a = data->a;
   int b = data->b;
   int result = a + b; // 進行計算

   data->result = result; // 將結果放進 data 中
   pthread_exit(NULL);
}

void* 
myPthread_func_chlid_4() 
{
    for(int i = 0;i < 3;++i) {
        pthread_mutex_lock( &mutex1 ); // 上鎖
        int tmp = counter;
        sleep(1);
        counter = tmp + 1;
        pthread_mutex_unlock( &mutex1 ); // 解鎖
        printf("Counter = %d\n", counter);
    }
    pthread_exit(NULL);
}

void* 
myPthread_func_chlid_5()
{
    for(int i = 0;i < 5;++i) {
        sem_wait(&semaphore); // 等待工作
        printf("Counter = %d\n", ++counter);
        sleep(1);
    }
    pthread_exit(NULL);
}

