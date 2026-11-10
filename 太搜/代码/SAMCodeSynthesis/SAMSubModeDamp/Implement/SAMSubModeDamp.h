#if !defined(__SAMSUBMODEDAMP_H__)
#define __SAMSUBMODEDAMP_H__

#include "../../IP.h"

void SAMSubModeDampFun(void *p);

/* SAM速率阻尼方式 */
typedef struct __SAMSubModeDamp
{
    /* 接口函数 */
    Fun         fun;
    /* 输入端口 */
    unint32     *m_curMode;                     /* 当前工作模式 */
    float32     *pRate;                         /* 卫星三轴角速度数组指针 */
    /* 输出端口 */
    unint32     m_workMode;                     /* 工作模式 */
    /* 输入输出端口 */
    /* 状态变量 */
    unint32     m_countMode;                    /* 子模式计数器 */
    unint32     m_countPublic;                  /* 公共模式计数器 */
    /* 参数变量 */
    unint32     time_D2P;                       /* 速率阻尼连续稳定转俯仰搜索时间（控制周期） */
    unint32     time_D2P_overtime;              /* 速率阻尼不能稳定转俯仰搜索时间（控制周期） */

} SAMSubModeDamp;

#endif // __SAMSUBMODEDAMP_H__
