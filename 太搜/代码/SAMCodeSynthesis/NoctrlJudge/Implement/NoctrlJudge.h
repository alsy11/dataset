#if !defined(__NOCTRLJUDGE_H__)
#define __NOCTRLJUDGE_H__

#include "../../IP.h"

void NoctrlJudgeFun(void *p);

/* 停控条件判断 */
typedef struct __NoctrlJudge
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    float32 *rate;      /* 三轴角速度数组指针 */
    /* 输出端口 */
    unint08 Wav;        /* 停控标志 */
    /* 输入输出端口 */
    /* 状态变量 */
    unint16 countAV;    /* 三轴姿态角速度绝对值有一个大于maxRate的计数器 */
    /* 参数变量 */
    float32 maxRate;    /* 最大角速度 */
    unint32 countThr;   /* 连续超速次数阈值 */
} NoctrlJudge;

#endif // __NOCTRLJUDGE_H__
