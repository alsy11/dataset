#if !defined(__SOFTFAULTJUDGESP_H__)
#define __SOFTFAULTJUDGESP_H__

#include "../../IP.h"

void SoftFaultJudgeSPFun(void *p);

/* SP信号故障诊断 */
typedef struct __SoftFaultJudgeSP
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 flgSp;          /* 见太阳标志 */
    /* 输出端口 */
    unint16 Wsp;
    /* 输入输出端口 */
    unint32 *countSPset;    /* 清切换太敏计数器 */
    /* 状态变量 */
    unint32 countSPLost;    /* 太敏丢失计数器 */
    unint32 countSPSeen;    /* 太敏可见计数器 */
    /* 参数变量 */
    unint32 lostThr;        /* 太敏丢失持续阈值数（周期） */
} SoftFaultJudgeSP;

#endif // __SOFTFAULTJUDGESP_H__
