#ifndef _MYPTHREAD_H_
#define _MYPTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct myPthread_data {
   int a;
   int b;
   int result;
} myPthread_data;

int pthreadTest_1();
int pthreadTest_2();
int pthreadTest_3();
int pthreadTest_4();
int pthreadTest_5();
void* myPthread_func_chlid_1(void* data);
void* myPthread_func_chlid_2(void* arg);
void* myPthread_func_chlid_3(void* arg);
void* myPthread_func_chlid_4();
void* myPthread_func_chlid_5();


#endif