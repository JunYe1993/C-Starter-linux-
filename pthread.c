#include <stdio.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int x = 2;
int y = 1;

void func(int a, int b)
{
    printf("x is greater than y, the value is x,y = %d,%d\n", a, b);
    x++;
}

//生产者的线程执行函数
void threadfacter()
{
    while(1){
        pthread_mutex_lock(&mutex);
        //do some thing on x, y
        if(x > y){
            //如果条件符合，则通知消费者线程
            pthread_cond_broadcast(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void threadcomsumer()
{
    while(1){
        pthread_mutex_lock(&mutex);
        //如果条件不符合，则释放mutex锁，并等待。如果条件符合，表示条件已经符合，并且尝试再对mutex加锁，如果加锁成功，pthread_cond_wait返回0
        pthread_cond_wait(&cond, &mutex);
        func(x,y);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_t threadfactorID, threadcomsumerID;

    pthread_create(&threadfactorID, NULL, (void *) threadfacter, NULL);
    pthread_create(&threadcomsumerID, NULL, (void *) threadcomsumer, NULL);

    pthread_join(threadfactorID, NULL);
    pthread_join(threadcomsumerID, NULL);
    return 0;
}