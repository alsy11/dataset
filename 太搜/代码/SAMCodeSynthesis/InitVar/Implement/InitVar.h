#if !defined(__INITVAR_H__)
#define __INITVAR_H__

#include "../../IP.h"

void InitVarFun(void *p);

/*  */
typedef struct __InitVar
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */
} InitVar;

#endif // __INITVAR_H__
