#if !defined(__CHECKCAL16_H__)
#define __CHECKCAL16_H__

#include "../../IP.h"

void CheckCal16Fun(void *p);

/* 8位累加和计算（结果取低16位） */
typedef struct __CheckCal16
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint08 *pkv;       /* 数组首地址指针 */
    unint32 len;        /* 计算长度 */
    /* 输出端口 */
    unint16 chksum;     /* 计算结果 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} CheckCal16;

#endif // __CHECKCAL16_H__
