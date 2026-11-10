#if !defined(__CALCULATEGYRODG_H__)
#define __CALCULATEGYRODG_H__

#include "../../IP.h"

void CalculateGyroDgFun(void *p);

/* 计算陀螺三轴角速度 */
typedef struct __CalculateGyroDg
{
    /* 接口函数 */
    Fun fun;
    /* 输入端口 */
    unint08 JoinTotal;  /* 参加定姿的陀螺个数 */
    unint08 *SignFlag;  /* 参加定姿的陀螺序号数组指针 */
    float32 *wa;        /* 陀螺角速度模拟量数组指针 */
    float32 *Rtemp;     /* 角速度转换矩阵指针 */
    /* 输出端口 */
    float32 W[3];       /* 陀螺算出的角速度 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} CalculateGyroDg;

#endif // __CALCULATEGYRODG_H__
