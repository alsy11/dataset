#if !defined(__GYROSTATEGET_H__)
#define __GYROSTATEGET_H__

#include "../../IP.h"

void GyroStateGetFun(void *p);

/* 陀螺数据采集 */
typedef struct __GyroStateGet
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 uartno;         /* 串口号 */
    unint32 NumGyro;        /* 陀螺个数 */
    /* 输出端口 */
    unint32 stateFlag[9];   /* 读取的陀螺加电状态数组 */
    float32 wa[9];          /* 陀螺脉冲计数数组 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */

} GyroStateGet;

extern DEBUGXXX debugGyro;

#endif // __GYROSTATEGET_H__
