#if !defined(__UART_INIT__)
#define __UART_INIT__

#include "../../IP.h"

void UartInitFun(void *p);

/* 串口初始化 */
typedef struct __UartInit
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 uartno;         /* 串口号 */
    unint32 stop;           /* 停止位配置：1为2位停止位，0为1位停止位 */
    unint32 even;           /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    unint32 baud;           /* 波特率配置（bps） */
    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} UartInit;

#endif // __UART_INIT__
