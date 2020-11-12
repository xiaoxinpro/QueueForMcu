# QueueForMcu
基于单片机实现的队列功能模块，主要用于8位、16位、32位非运行RTOS的单片机应用，兼容大多数单片机平台。

> 开源代码：https://github.com/xiaoxinpro/QueueForMcu

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

## 六、压入队列

### 1、单数据压入
将数据压入队列尾部使用 `Queue_Push` 函数，该函数原型如下：

```
QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T data)
```

**参数说明：**

| 参数名 | 描述 |
|:--|:--|
| hqueue | 需要压入数据的队列结构。 |
| data| 待压入队列的数据。 |

**返回值说明：**

该函数会返回一个 `QUEUE_StatusTypeDef` 枚举数据类型，返回值会根据队列状态返回以下几个值：

| 返回值 | 描述 |
|:--|:--|
| QUEUE_OK | 数据压入队列成功。 |
| QUEUE_OVERLOAD | 未压入数据到队列中，原因队列已满。 |

**参考代码：**

```
Queue_Push(&qUartTx, 'Q');
Queue_Push(&qUartTx, 0x51);
Queue_Push(&qUartTx, 81);
```

### 2、多数据压入
若需要将多个数据（数组）压入队列可以使用 `Queue_Push_Array` 函数，原理上循环调用 `Queue_Push` 函数来实现的，函数原型如下：

```
unsigned int Queue_Push_Array(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdatas, unsigned int len)
```

**参数说明：**

| 参数名 | 描述 |
|:--|:--|
| hqueue | 需要压入数据的队列结构。 |
| pdatas | 待压入队列的数组首地址。 |
| len | 待压入队列的数组长度。 |

> 当数组长度大于队列剩余长度时，数组多余的数据将被忽略。

**返回值说明：**

* 该函数将返回实际被压入到队列中的数据长度。

* 当队列中的剩余长度富余时，返回值将等于参数 `len` 的值。

* 当队列中的剩余长度不足时，返回值为实际被压入到队列的数据长度。

## 七、弹出队列
### 1、单数据弹出
将队列头部数据弹出队列使用 `Queue_Pop` 函数，需要注意的是，弹出的数据将从队列中删除，该函数原型如下：

```
QUEUE_StatusTypeDef Queue_Pop(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdata)
```

**参数说明：**

| 参数名 | 描述 |
|:--|:--|
| hqueue | 需要弹出数据的队列结构。 |
| pdata | 用于保存弹出数据变量的指针。 |

**返回值说明：**

该函数会返回一个 `QUEUE_StatusTypeDef` 枚举数据类型，返回值会根据队列状态返回以下几个值：

| 返回值 | 描述 |
|:--|:--|
| QUEUE_OK | 数据弹出队列成功。 |
| QUEUE_VOID| 未弹出数据到队列中，原因队列为空。 |

**参考代码：**

```
QUEUE_DATA_T temp;
if(QUEUE_OK = Queue_Pop(&qUartTx, &temp))
{
    // temp 为队列弹出的数据
}
else
{
    // 弹出数据失败
}
```

### 2、多数据弹出
若需要将多个数据弹出队列可以使用 `Queue_Pop_Array` 函数，原理上循环调用 `Queue_Pop` 函数来实现的，需要注意的是，成功弹出的数据将从队列中删除，函数原型如下：

```
unsigned int Queue_Pop_Array(QUEUE_HandleTypeDef * hqueue, QUEUE_DATA_T * pdatas, unsigned int len)
```

**参数说明：**

| 参数名 | 描述 |
|:--|:--|
| hqueue | 需要弹出数据的队列结构。 |
| pdatas | 用于保存弹出数据数组的首地址。 |
| len | 需要弹出数据数组的长度。 |

> 当需要弹出数据的长度大于队列中的数据长度时，弹出数组多余的空间将不会被赋值。

**返回值说明：**

* 该函数将返回实际从队列中弹出的数据长度。

* 当队列中的数据长度足够时，返回值将等于参数 `len` 的值。

* 当队列中的数据长度不足时，返回值为实际从队列中弹出的数据长度。

### 3、单数据复制
当需要从队列头部获取数据，但又不希望数据从队列中删除时，可以使用 `Queue_Peek` 函数来实现，该函数的参数与返回值与 `Queue_Pop` 完全相同。

使用 `Queue_Peek` 和 `Queue_Pop` 函数的区别在于：
* `Queue_Pop` 得到队列中的数据后会删除队列中的数据。
* `Queue_Peek` 得到队列中的数据后会保留队列中的数据。

### 4、多数据复制
当需要从队列头部获取多个数据，但又不希望数据从队列中删除时，可以使用 `Queue_Peek_Array` 函数来实现，该函数的参数与返回值与 `Queue_Pop_Array` 完全相同。

使用 `Queue_Peek_Array` 和 `Queue_Pop_Array` 函数的区别在于：
* `Queue_Pop_Array` 得到队列中的数据后会删除队列中的数据。
* `Queue_Peek_Array` 得到队列中的数据后会保留队列中的数据。


****
待更新...