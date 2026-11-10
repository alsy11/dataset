#if !defined(__CHECKCAL08_H__)
#define __CHECKCAL08_H__

#include "../../IP.h"

void CheckCal08Fun(void *p);

/* 8位累加和计算 */
typedef struct __CheckCal08
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint08 *pkv;       /* 数组首地址指针 */
    unint32 len;        /* 计算长度 */
    /* 输出端口 */
    unint08 chksum;     /* 计算结果 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} CheckCal08;

#endif // __CHECKCAL08_H__
