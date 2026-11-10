#if !defined(__SAMSUBMODEPITCH_H__)
#define __SAMSUBMODEPITCH_H__

#include "../../IP.h"

void SAMSubModePitchFun(void *p);

/* SAM俯仰搜索方式 */
typedef struct __SAMSubModePitch
{
    /* 接口函数 */
    Fun         fun;
    /* 输入端口 */
    unint32     *m_curMode;                 /* 当前工作模式 */
    unint32     *flgSP;                     /* 见太阳标志 */
    float32     *piyaw;                     /* 太阳输出的俯仰太阳角度 */
    /* 输出端口 */
    unint32     m_workMode;                 /* 工作模式 */
    float32     outUp[3];                   /* 输出的控制量 */
    /* 输入输出端口 */
    /* 状态变量 */
    unint32     m_countMode;
    unint32     m_countPublic;
    /* 参数变量 */

} SAMSubModePitch;

#endif // __SAMSUBMODEPITCH_H__
