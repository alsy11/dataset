#if !defined(__LIMITCTRLANGLEINPUT_H__)
#define __LIMITCTRLANGLEINPUT_H__

#include "../../IP.h"

void LimitCtrlAngleInputFun(void *p);

/* 角度限幅 */
typedef struct __LimitCtrlAngleInput
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    float32 *angle;     /* 三轴姿态角数组指针 */
    float32 max;        /* 角度限幅阈值 */
    /* 输出端口 */
    float32 *Up;        /* 限幅后的三轴姿态角 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} LimitCtrlAngleInput;

#endif // __LIMITCTRLANGLEINPUT_H__
