#ifndef __QUEUE_H
#define __QUEUE_H

//==============================================================================
//  常量定义
//==============================================================================
#define QUEUE_DATA_T  unsigned char         //队列数据类型定义

//==============================================================================
//  类型定义
//==============================================================================
typedef struct QUEUE_HandleTypeDef{
    unsigned int head;                      //队列头指针
    unsigned int tail;                      //队列尾指针
    unsigned int buffer_length;             //队列缓存长度（初始化时赋值）
    QUEUE_DATA_T * buffer;		              //队列缓存数组（初始化时赋值）
}QUEUE_HandleTypeDef;

typedef enum
{
    QUEUE_OK       = 0x00U,                 //队列OK
    QUEUE_ERROR    = 0x01U,                 //队列错误
    QUEUE_BUSY     = 0x02U,                 //队列忙
    QUEUE_TIMEOUT  = 0x03U,                 //队列超时
    QUEUE_OVERLOAD = 0x04U,                 //队列已满
    QUEUE_VOID     = 0x05U                  //队列已空
} QUEUE_StatusTypeDef;


//==============================================================================
//  公共函数声明
//==============================================================================
extern void Queue_Init(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * buffer, unsigned int len);
extern void Queue_Clear(QUEUE_HandleTypeDef * hqueue);
extern unsigned int Queue_Count(QUEUE_HandleTypeDef * hqueue);
extern QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T data);
extern unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdatas, unsigned int len);
extern QUEUE_StatusTypeDef Queue_Pop(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdata);
extern unsigned int Queue_Pop_Array(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdatas, unsigned int len); 
extern QUEUE_StatusTypeDef Queue_Peek(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdata);
extern unsigned int Queue_Peek_Array(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdatas, unsigned int len);

#endif

