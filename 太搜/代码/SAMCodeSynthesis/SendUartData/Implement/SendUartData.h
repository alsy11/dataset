#if !defined(__SENDUARTDATA_H__)
#define __SENDUARTDATA_H__

#include "../../IP.h"

void SendUartDataFun(void *p);

/* 串口数据发送 */
typedef struct __SendUartData
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 uartno;         /* 串口号 */
    unint08 *buf;           /* 待写入数据 */
    unint32 sendsize;       /* 待写入数据长度 */
    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} SendUartData;

#endif // __SENDUARTDATA_H__
