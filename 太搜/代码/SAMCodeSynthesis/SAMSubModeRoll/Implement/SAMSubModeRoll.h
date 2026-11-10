#if !defined(__SAMSUBMODEROLL_H__)
#define __SAMSUBMODEROLL_H__

#include "../../IP.h"

void SAMSubModeRollFun(void *p);

/* SAM滚动搜索方式 */
typedef struct __SAMSubModeRoll
{
    /* 接口函数 */
    Fun         fun;
    /* 输入端口 */
    unint32     *m_curMode;                 /* 当前工作模式 */
    unint32     *flgSP;                     /* 见太阳标志 */
    float32     *royaw;                     /* 太阳输出的滚动太阳角度 */
    /* 输出端口 */
    unint32     m_workMode;                 /* 工作模式 */
    /* 输入输出端口 */
    float32     outUp[3];                   /* 输出的控制量 */
    /* 状态变量 */
    unint32     m_countMode;
    unint32     m_countPublic;
    /* 参数变量 */

} SAMSubModeRoll;

#endif // __SAMSUBMODEROLL_H__
