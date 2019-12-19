#include "queue.h"

//==============================================================================
//  函数声明
//==============================================================================
void Queue_Init(QUEUE_HandleTypeDef * hqueue, unsigned char * buffer, unsigned int len);
void Queue_Clear(QUEUE_HandleTypeDef * hqueue);
unsigned int Queue_Count(QUEUE_HandleTypeDef * hqueue);
QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, unsigned char data);
unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len);
QUEUE_StatusTypeDef Queue_Pop(QUEUE_HandleTypeDef * hqueue, unsigned char * pdata);
unsigned int Queue_Pop_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len);


//==============================================================================
//  函数名称：
//  函数功能：
//  函数参数：
//  函数返回：
//==============================================================================
void Queue_Init(QUEUE_HandleTypeDef * hqueue, unsigned char * buffer, unsigned int len)
{
    hqueue->buffer = buffer;
    hqueue->buffer_length = len;
    Queue_Clear(hqueue);
}

//==============================================================================
//  函数名称：
//  函数功能：
//  函数参数：
//  函数返回：
//==============================================================================
void Queue_Clear(QUEUE_HandleTypeDef * hqueue)
{
    hqueue->head = 0;
    hqueue->tail = 0;
}

//==============================================================================
//  函数名称：Queue_Count
//  函数功能：获取队列内数据个数
//  函数参数：
//  函数返回：
//==============================================================================
unsigned int Queue_Count(QUEUE_HandleTypeDef * hqueue)
{
    if(hqueue->head <= hqueue->tail)
    {
        return (unsigned int)(hqueue->tail - hqueue->head);
    }
    else
    {
        return (unsigned int)(hqueue->buffer_length + hqueue->tail - hqueue->head);
    }
}

//==============================================================================
//  函数名称：Queue_Push
//  函数功能：压入数据到队列中
//  函数参数：
//  函数返回：
//==============================================================================
QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, unsigned char data)
{
    unsigned int tmp = (hqueue->tail + 1) % hqueue->buffer_length;

    if(tmp == hqueue->head)
    {
        return QUEUE_OVERLOAD;
    }
    else
    {
        hqueue->buffer[hqueue->tail] = data;
        hqueue->tail = tmp;
        return QUEUE_OK;
    }
}

//==============================================================================
//  函数名称：Queue_Push_Array
//  函数功能：压入一组数据到队列中
//  函数参数：
//  函数返回：成功压入队列数据的数量
//==============================================================================
unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len)
{
    unsigned int i;
    for(i=0; i<len; i++)
    {
        if(Queue_Push(hqueue,pdatas[i]) == QUEUE_OVERLOAD)
        {
            break;
        }
    }
    return i;
}


//==============================================================================
//  函数名称：Queue_Pop
//  函数功能：从队列中弹出数据
//  函数参数：
//  函数返回：
//==============================================================================
QUEUE_StatusTypeDef Queue_Pop(QUEUE_HandleTypeDef * hqueue, unsigned char * pdata)
{
    if(hqueue->head == hqueue->tail)
    {
        return QUEUE_VOID;
    }
    else
    {
        *pdata = hqueue->buffer[hqueue->head];
        hqueue->head = (hqueue->head + 1) % hqueue->buffer_length;
        return QUEUE_OK;
    }
}

//==============================================================================
//  函数名称：Queue_Pop_Array
//  函数功能：从队列中弹出一组数据
//  函数参数：
//  函数返回：实际弹出数据的数量
//==============================================================================
unsigned int Queue_Pop_Array(QUEUE_HandleTypeDef * hqueue, unsigned char * pdatas, unsigned int len)
{
    unsigned int i;
    for(i=0; i<len; i++)
    {
        if(Queue_Pop(hqueue, &pdatas[i]) == QUEUE_VOID)
        {
            break;
        }
    }
    return i;
}






