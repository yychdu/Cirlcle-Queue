#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE 1
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "stdbool.h"
#include "queue.h"
//参数检查
TQueue TQueue_Init(TQueueData* data, void *items, Word item_size, int count)
{
    TQueue result = NULL;
    if (data != NULL && items != NULL && item_size > 0 && count > 0)
    {
        data->Push_Count = 0;
        data->Push_Index = 0;
        data->Pop_Count = 0;
        data->Pop_Index = 0;
        data->Count = count;
        data->size = item_size;
        data->List = items;
        result = data;
    }
    return result;
}

void TQueue_Fini(TQueueData* data)
{
    if (data != NULL)
    {
        data->Pop_Count = data->Push_Count;
    }
}

bool TQueue_Push(TQueue Object, const void *item)
{
    bool result = false;
    if (item != NULL && Object->Push_Count - Object->Pop_Count < Object->Count)
    {
        memcpy(Object->List + Object->Push_Index * Object->size, item, Object->size);       
        if (Object->Push_Index == Object->Count - 1)
            Object->Push_Index = 0;
        else
            Object->Push_Index++;
        Object->Push_Count++;
        result = true;
    }
    return result;
}

bool TQueue_Peek(TQueue Object, void *item)
{
    bool result = false;
    if (item != NULL && Object->Push_Count != Object->Pop_Count)
    {
        memcpy(item, Object->List + Object->Pop_Index * Object->size, Object->size);
        result = true;
    }
    return result;
}

bool TQueue_Pop(TQueue Object, void *item)
{
    bool result = false;
    if (item != NULL && Object->Push_Count != Object->Pop_Count)
    {
        memcpy(item, Object->List + Object->Pop_Index * Object->size, Object->size);
        if (Object->Pop_Index == Object->Count - 1)
            Object->Pop_Index = 0;
        else
            Object->Pop_Index++;
        Object->Pop_Count++;
        result = true;
    }
    return result;
}
