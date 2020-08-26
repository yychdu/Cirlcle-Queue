#ifndef __QUEUE
#define __QUEUE
typedef unsigned short      Word;
typedef struct
{
    char*          List;
    Word size;
    unsigned long  Push_Count;
    unsigned long  Push_Index;
    unsigned long  Pop_Count;
    unsigned long  Pop_Index;
    unsigned long Count;
} TQueueData;

typedef TQueueData* TQueue;
TQueue TQueue_Init(TQueueData *data, void *items, Word item_size, int count);
void TQueue_Fini(TQueueData *data);

bool TQueue_Push(TQueue Object, const void *item);
bool TQueue_Peek(TQueue Object, void *item);
bool TQueue_Pop(TQueue Object, void *item);

#endif // !__QUEUE
