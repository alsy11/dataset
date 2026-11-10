#if !defined(__TMPROCESS_H__)
#define __TMPROCESS_H__

#include "../../IP.h"

void TMProcessFun(void *p);

/*  */
typedef struct __TMProcess
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 *pWorkMode;
    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} TMProcess;

#endif // __TMPROCESS_H__
