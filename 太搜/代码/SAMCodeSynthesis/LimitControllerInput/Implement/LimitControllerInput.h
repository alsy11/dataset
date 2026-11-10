#if !defined(__LIMITCONTROLLERINPUT_H__)
#define __LIMITCONTROLLERINPUT_H__

#include "../../IP.h"

void LimitControllerInputFun(void *p);

/* 控制器输入限幅 */
typedef struct __LimitControllerInput
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    float32     *angle;             /* 三轴姿态角数组指针 */
    float32     *rate;              /* 三轴姿态角速度数组指针 */
    float32     *bias;              /* 角速度偏置量 */
    /* 输出端口 */
    float32     Up[3];              /* 限幅后的三轴角度 */
    float32     Ud[3];              /* 限幅后的三轴角速度 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
    float32     angLimit;           /* 角度限幅值 */
    float32     veloLimit;          /* 角速度限幅值 */
} LimitControllerInput;

#endif // __LIMITCONTROLLERINPUT_H__
