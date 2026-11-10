#if !defined(__GYROATTIDETERMINE_H__)
#define __GYROATTIDETERMINE_H__

#include "../../IP.h"

void GyroAttiDetermineFun(void *p);

/* 陀螺姿态确定 */
typedef struct __GyroAttiDetermine
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 *StateFlag;         /* 陀螺可用标志数组指针 */
    float32 *wa;                /* 陀螺角速度模拟量数组指针 */
    /* 输出端口 */
    float32 W[3];               /* 陀螺算出的角速度 */
    /* 输入输出端口 */
    float32 *Gi;                /* 陀螺角度积分 */
    /* 状态变量 */
    unint08 JoinTotal;          /* 参加定姿的陀螺个数 */
    unint16 gyroStatus0;        /* 陀螺状态新 */
    unint16 gyroStatus1;        /* 陀螺状态旧 */
    unint08 SignFlag[9];        /* 参加定姿的陀螺序号 */
    float32 Rtemp[3][5];        /* 角速度转换矩阵计算结果 */
    /* 参数变量 */
    float32 *VGyro;             /* 9x3陀螺安装矩阵数组指针 */

} GyroAttiDetermine;

#endif // __GYROATTIDETERMINE_H__
