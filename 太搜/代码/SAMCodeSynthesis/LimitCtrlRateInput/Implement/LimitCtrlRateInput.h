#if !defined(__LIMITCTRLRATEINPUT_H__)
#define __LIMITCTRLRATEINPUT_H__

#include "../../IP.h"

void LimitCtrlRateInputFun(void *p);

/* 角速度限幅 */
typedef struct __LimitCtrlRateInput
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    float32 *rate;      /* 三轴姿态角数组指针 */
    float32 biasX;      /* X轴角速度偏置量 */
    float32 biasY;      /* Y轴角速度偏置量 */
    float32 max;        /* 角速度限幅阈值 */
    /* 输出端口 */
    float32 *Ud;        /* 限幅后的三轴角速度 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} LimitCtrlRateInput;

#endif // __LIMITCTRLRATEINPUT_H__
