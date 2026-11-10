#if !defined(__DELAY_H__)
#define __DELAY_H__

#include "../../IP.h"

void DelayFun(void *p);

/* 延时 */
typedef struct __Delay
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint16 delaytime;      /* 延时时间，当量us */
    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} Delay;

#endif // __DELAY_H__
