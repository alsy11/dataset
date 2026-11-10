#if !defined(__GETUARTDATA_H__)
#define __GETUARTDATA_H__

#include "../../IP.h"

void GetUartDataFun(void *p);

/* 串口接收数据 */
typedef struct __GetUartData
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 uartno;             /* 串口号 */
    unint32 len;                /* 待接收数据长度； */
    unint08 *data;              /* 读取数据存放位置 */
    /* 输出端口 */
    unint32 bSucc;
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */

} GetUartData;

#endif // __GETUARTDATA_H__
