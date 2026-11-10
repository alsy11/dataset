#if !defined(__JETCTRLSEND_H__)
#define __JETCTRLSEND_H__

#include "../../IP.h"

void JetCtrlSendFun(void *p);

/* 推力器控制输出 */
typedef struct __JetCtrlSend
{
    /* 接口函数 */
    Fun     fun;
    /* 输入端口 */
    unint32 uartno;         /* 串口号 */
    unint32 *pulse;         /* 输入的推力器分配[12] */

    /* 输出端口 */
    /* 输入输出端口 */
    /* 状态变量 */
    /* 参数变量 */

} JetCtrlSend;

#endif // __JETCTRLSEND_H__
