#if !defined(__DSSDATAGET_H__)
#define __DSSDATAGET_H__

#include "../../IP.h"

void DSSDataGetFun(void *p);

/* 太阳敏感器数据采集 */
typedef struct __DSSDataGet
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32     uartno;                 /* 串口号 */
    /* 输出端口 */
	float32 	royaw;                  /* 滚动太阳角度 */
	float32 	piyaw;                  /* 俯仰太阳角度 */
    unint32     flgSP;					/* 太阳可见标志 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */

} DSSDataGet;

extern DEBUGXXX debugDss;

#endif // __DSSDATAGET_H__
