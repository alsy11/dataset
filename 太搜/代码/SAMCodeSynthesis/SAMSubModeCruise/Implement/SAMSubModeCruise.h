#if !defined(__SAMSUBMODECRUISE_H__)
#define __SAMSUBMODECRUISE_H__

#include "../../IP.h"

void SAMSubModeCruiseFun(void *p);

/* 太搜巡航模式处理 */
typedef struct __SAMSubModeCruise
{
    /* 接口函数 */
    Fun         fun;
    /* 输入端口 */
    unint32     *m_countMode;
    /* 输出端口 */
    unint32     CWsp;               /* 允许SP报警标志 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} SAMSubModeCruise;

#endif // __SAMSUBMODECRUISE_H__
