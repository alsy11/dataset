#if !defined(__TCDATACHECK_H__)
#define __TCDATACHECK_H__

#include "../../IP.h"

void TcDataCheckFun(void *p);

/* 串口接收数据 */
typedef struct __TcDataCheck
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint08 *data;              /* 读取数据存放位置 */
    /* 输出端口 */
    unint32 ret;                /* 指令校验是否通过 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} TcDataCheck;

#endif // __TCDATACHECK_H__
