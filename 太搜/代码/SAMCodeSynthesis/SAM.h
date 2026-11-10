#ifndef SAM_H
#define SAM_H

#include "stdio.h"
#ifdef __GCC_COMPILED__
#include "Fyq.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "B_TcProcess.h"
#include "CheckCal08.h"
#include "DSSDataGet.h"
#include "GetUartData.h"
#include "GyroAttiDetermine.h"
#include "GyroPick.h"
#include "GyroStateGet.h"
#include "JetDataGet.h"
#include "PseudoRate.h"
#include "SAMSubModeDamp.h"
#include "SAMSubModePitch.h"
#include "SAMSubModeRoll.h"
#include "SendUartData.h"
#include "TcDataCheck.h"
#include "ThreeAxisController.h"
#include "ThrusterCtrlLogic.h"
#include "UartInit.h"
#include "JetCtrlSend.h"

extern unint32 cntSate;
extern unint32 cntMode;
extern float32 starTime;
extern unint32 currentmode;
extern float32 angle[3];       /* 三轴姿态角 */
extern float32 rate[3];        /* 三轴角速度 */
extern float32 attirateT[3];   /* 三轴目标角速度 */
extern float32 jetWidT[6];
extern UartInit ipUartInitGyro;
extern UartInit ipUartInitDss;
extern UartInit ipUartInitJet;
extern UartInit ipUartInitTC;
extern UartInit ipUartInitTM;
extern GetUartData ipGetUartDataObdh;
extern TcDataCheck ipTcDataCheckObdh;
extern B_TcProcess ipB_TcProcessObdh;
extern GyroStateGet ipGyroStateGet;
extern DSSDataGet ipDSSDataGet;
extern GyroPick ipGyroPick;
extern GyroAttiDetermine ipGyroAttiDetermine;
extern SAMSubModeDamp ipSAMSubModeDamp;
extern SAMSubModePitch ipSAMSubModePitch;
extern SAMSubModeRoll ipSAMSubModeRoll;
extern ThreeAxisController ipThreeAxisController;
extern PseudoRate ipPseudoRate;
extern ThrusterCtrlLogic ipThrusterCtrlLogic;
extern JetCtrlSend ipJetCtrlSend;
extern CheckCal08 ipCheckCal08TM;
extern SendUartData ipSendUartDataTM;

// 初始化阶段
extern void AppInit1(void);

// 主循环
extern void AppTask(void);

/* CONVENIENT_FOR_LOOKUP
void add_decl_tail(){DON'T MODIFY} */
#ifdef __cplusplus
}
#endif

#endif
