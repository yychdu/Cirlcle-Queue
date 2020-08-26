#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE 1
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "pthread.h"
#include "stdbool.h"
#include "queue.h"
#include "signal.h"
#include "windows.h"
#pragma comment(lib,"pthreadVC2.lib")
//用push_count 压入
//检查pop_count-push_count ? 
//错误休眠
//错误打印信息

bool run_over = false;

void sighandler(int signum)
{
    run_over = true;
}

void *push(void *arg)
{
    TQueue tmp = (TQueue)arg;
    if (tmp != NULL)
    {
       while (!run_over)
       {
            if (!TQueue_Push(tmp, &tmp->Push_Count))
                Sleep(1);
       }
    }
    else
        printf("TQueueData ERR");
    return NULL;
}


void *pop(void *arg)
{
    unsigned long digit;
    TQueue tmp = (TQueue)arg;
    if (tmp != NULL)
    {
       while (!run_over)
       {
            if (!TQueue_Pop(tmp, &digit))
                Sleep(1);
            else if (tmp->Pop_Count - digit != 1)
            {
                run_over = true;
                printf("Pop ERROR\n");
                printf("digit = %d\n", digit);
                printf("Push_Count = %d\n", tmp->Push_Count);
                printf("Pop_Count = %d\n", tmp->Pop_Count); 
                break;
            }
       }    
    }
    else
        printf("TQueueData ERR");
    return NULL;
}

TQueueData _data;

int main() 
{
    int arr[10];
    TQueue tmp = TQueue_Init(&_data, arr, sizeof(int), sizeof(arr) / sizeof(int));
    if (tmp != NULL)
    {
        pthread_t th1, th2;
        pthread_create(&th1, NULL, push, tmp);
        pthread_create(&th2, NULL, pop, tmp);
        signal(SIGINT, sighandler);
        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
    }
    else
        printf("TQueue_Init Error");   
    return 0;
}