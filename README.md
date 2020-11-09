# QueueForMcu
基于单片机实现的队列功能模块，主要用于8位、16位、32位非运行RTOS的单片机应用，兼容大多数单片机平台。

## 一、特性
* 动态创建队列对象
* 动态设置队列数据缓冲区
* 静态指定队列元素数据长度
* 采用值传递的方式保存队列数据

## 二、快速使用

```
#include "queue.h"

#define Q_UART_BUFFER_SIZE  1024

QUEUE_HandleTypeDef qUartTx;
QUEUE_DATA_T BufferUartTx[Q_UART_BUFFER_SIZE];

int main(void)
{
  QUEUE_DATA_T temp;
  
  //初始化队列
  Queue_Init(&qUartTx, BufferUartTx, Q_UART_BUFFER_SIZE);
  
  while(1)
  {
    //入队
    Queue_Push(&qUartTx, 'Q');
    Queue_Push(&qUartTx, 'u');
    Queue_Push(&qUartTx, 'e');
    Queue_Push(&qUartTx, 'u');
    Queue_Push(&qUartTx, 'e');
    
    //出队
    Queue_Pop(&qUartTx, &temp);
    Queue_Pop(&qUartTx, &temp);
    Queue_Pop(&qUartTx, &temp);
    Queue_Pop(&qUartTx, &temp);
    Queue_Pop(&qUartTx, &temp);
  }
}
```

## 三、配置说明

目前QueueForMcu只有一个静态配置项，具体如下：

在文件 `queue.h` 中有一个宏定义 `QUEUE_DATA_T` 用于指定队列元素的数据长度，默认是 `unsigned char` ，可以根据需要更改为其他数据类型。

## 四、数据结构

队列的数据结构为 `QUEUE_HandleTypeDef` 用于保存队列的状态，源码如下：

```
typedef struct QUEUE_HandleTypeDef{
    unsigned int head;                      //队列头指针
    unsigned int tail;                      //队列尾指针
    unsigned int buffer_length;             //队列缓存长度（初始化时赋值）
    QUEUE_DATA_T * buffer;                  //队列缓存数组（初始化时赋值）
}QUEUE_HandleTypeDef;
```

其中 `QUEUE_DATA_T` 为配置项中自定义的数据类型。

## 五、创建队列

### 1、创建队列缓存

由于我们采用值传递的方式保存队列数据，因此我们在创建队列前要手动创建一个队列缓存区，用于存放队列数据。

```
QUEUE_DATA_T BufferUartTx[1024];
```

以上代码即创建一个大小为 `1024` 的队列缓存区。

### 2、创建队列结构
接下来使用 `QUEUE_HandleTypeDef` 创建队列结构，用于保存队列的状态：

```
QUEUE_HandleTypeDef qUartTx;
```

### 3、初始化队列

准备好队列缓存和队列结构后调用 `Queue_Init` 函数来创建队列，该函数原型如下：

```
void Queue_Init(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * buffer, unsigned int len)
```

**参数说明：**

| 参数名 | 描述 |
|:--|:--|
| hqueue | 需要初始化的队列结构，如果二次初始化将清空原队列的内容。 |
| buffer | 队列缓存的首地址指针 |
| len | 队列长度，不能比队列缓存长度还要大。 |

**参考代码：**

```
Queue_Init(&qUartTx, BufferUartTx, Q_UART_BUFFER_SIZE);
```

****
待更新...