#if !defined(__JETDATAGET_H__)
#define __JETDATAGET_H__

#include "../../IP.h"

void JetDataGetFun(void *p);

/* 推力器数据采集 */
typedef struct __JetDataGet
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    /* 输出端口 */
    unint08 stateFlag[12];   /* 推力器加电状态, 对应12个喷管 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
    unint16 stateAddr;      /* 推力器加电状态读取地址寄存器 */
    unint32 bitA;           /* 推力器主份加电状态所处的位 */
    unint32 bitB;           /* 推力器备份加电状态所处的位 */
} JetDataGet;

#endif // __JETDATAGET_H__
