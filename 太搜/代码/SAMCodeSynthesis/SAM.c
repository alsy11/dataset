
#include "SAM.h"

/********************************* 全局变量声明 *********************************/
unint32 cntSate;
unint32 cntMode;                /* 当前模式计数器 */
float32 starTime;
unint32 currentmode = SAM_DAMP; /* 工作模式 */
unint32 nextmode;               /* 下一周期工作模式 */
float32 GyroMatrix[9][3] = {{ 0.7672553f, -0.2792581f,  0.5773510f},    /* 陀螺安装阵 */
                            {-0.1417830f, -0.8040916f,  0.5773510f},
                            {-0.1417830f,  0.8040916f,  0.5773510f},
                            { 0.7672553f,  0.2792581f,  0.5773510f},
                            {-0.6254722f, -0.5248335f,  0.5773510f},
                            {-0.6254722f,  0.5248335f,  0.5773510f},
                            {-0.4082480f, -0.7071063f, -0.5773510f},
                            {-0.4082480f,  0.7071063f, -0.5773510f},
                            { 0.8164960f,        0.0f, -0.5773510f}};
float32 angle[3];       /* 三轴姿态角 */
float32 rate[3];        /* 三轴角速度 */
float32 attirateT[3];   /* 三轴目标角速度 */
float32 Up[3];          /* 控制量 *///cpu给电机的指令（地面给飞机的指令），还需要的电流控制 如：把这个“15度的差距”，控制量是“该用多大的力气去推”。
unint08 tmDataBuf[100]; /* 遥测数据包 *///（飞机给地面的指令）告诉其当前姿态和角速度
float32 Gi[3];          /* 陀螺角度积分 */

float32 jetWidT[6];

/********************************* AppTask IP解析 *********************************/
//串口：数据流动的通道
UartInit ipUartInitGyro;
UartInit ipUartInitDss;
UartInit ipUartInitJet;
UartInit ipUartInitTC;
UartInit ipUartInitTM;

/********************************* AppTask IP解析 *********************************/
// ProTC obdh1 {recvFlag,workmode} ReqCapByTable ProTable.TC;/*从obdh1中获得遥控数据：通过UARTport2,按照协议表ProTable中的TC条目的格式获得工作模式,并根据包头、长度和校验和的判断设置recvFlag */
//obdh: On-Board Data Handling（星载数据处理）指卫星上负责管理所有数据流
unint08 obdhBuf[4];//收件箱（原始数据缓存）
GetUartData ipGetUartDataObdh;//取件员（串口读取接口）
TcDataCheck ipTcDataCheckObdh;//验货员（遥控指令校验）
B_TcProcess ipB_TcProcessObdh;//翻译官（遥控指令解析执行）

// GetData gyro1 {deltG[9],GyroPowerState[9]};/* 9陀螺数据采集：通过UARTport1按照gyro_proTable1格式发送取数指令,等待大于其响应时间后,按照gyro_proTable3格式获得陀螺角速度和加电状态*/    
GyroStateGet ipGyroStateGet;

// GetData dss1 {viewCode,AttigDss[2],DssPowerState[2]};/*2太阳敏感器数据采集：通过ADport5和ADport6,获得太阳敏感器的可见标志和加电状态,通过ADport7,按照12位偏移二进制到浮点数的转换获太阳方位角*/
DSSDataGet ipDSSDataGet;

// ProVld { deltG[9],deltG1[9]} {deltG[9],deltG1[9]} ReqCapByTable FormulaTable.B1;/*陀螺数据剔野：根据公式表B1条目进行陀螺角速度的剔野处理*/
GyroPick ipGyroPick;

// DetAtt {wG,attiangG} {deltG[9]} ReqCapByTable FormulaTable.B2;/*陀螺姿态确定：根据公式表B2条目,通过陀螺数据计算得到三轴陀螺惯性角速度和积分角度*/
GyroAttiDetermine ipGyroAttiDetermine;

// DetAtt {attiang,attirate,attiangG } { currentmode,attiangG,wG,viewCode,AttigDss} ReqCapByTable FormulaTable.B3;/*陀螺与太阳敏感器姿态确定：根据公式表B3条目,利用模式字、陀螺计算得到的姿态角和太阳方位角,确定用于控制的三轴姿态角和角速度 */

// Composite modeProcess{/*模式处理 */

// SwitchMode {nextmode} {currentmode,viewCode, cntMode,attirate} ReqCapByTable FormulaTable.B5;/*模式切换 ：根据根据公式表B5条目,进行模式切换条件的判断和处理*/
SAMSubModeDamp ipSAMSubModeDamp;
SAMSubModePitch ipSAMSubModePitch;
SAMSubModeRoll ipSAMSubModeRoll;

// If (currentmode!= nextmode){
//     Set currentmode nextmode;/*模式初始化 */
//     Set cntMode 0; }

// Switch(nextmode):{
//     Case(RDSM): { Set attirateT {0.0,0.0,0.0};/* RDSM目标姿态计算：设置三轴目标角速度为{0.0,0.0,0.0}*/}
//     Case(PASM): { Set attirateT {0.0,0.5,0.0};/* PASM目标姿态计算：设置三轴目标角速度为{0.0,0.5,0.0}*/}
//     Case(RASM): { Set attirateT {0.5,0.0,0.0};/* RASM目标姿态计算：设置三轴目标角速度为{0.5,0.0,0.0}*/}
//     Case(CSM) : { Set attirateT {0.0,0.0,0.0};/* CSM目标姿态计算：设置三轴目标角速度为{0.0,0.0,0.0} */}}

// CalCtrl pulseWidth {attiang,attirate,attiangT,attirateT} ReqCapByTable FormulaTable.B4;/*推力器数据控制计算：根据公式表B4条目进行计算,此功能包括三个顺序的处理过程*/
ThreeAxisController ipThreeAxisController;
PseudoRate ipPseudoRate;
ThrusterCtrlLogic ipThrusterCtrlLogic;
JetCtrlSend ipJetCtrlSend;

// ProTM obdh1 {workmode,attiang,attirate,cntSate} ReqCapByTable ProTable.TM;/*遥测处理：通过UARTport2按照proTable表TM条目格式进行遥测数据的打包发送 */
CheckCal08 ipCheckCal08TM;
SendUartData ipSendUartDataTM;

void VarAssignInit(void)    /* 变量对接函数, 初始化调用一次 */
{
    ipUartInitGyro.fun = UartInitFun;       /* 陀螺串口初始化 */
    ipUartInitGyro.uartno = 8;              /* 串口号 */
    ipUartInitGyro.stop = 0;                /* 停止位配置：1为2位停止位，0为1位停止位 */
    ipUartInitGyro.even = 0;                /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    ipUartInitGyro.baud = 250000;           /* 波特率配置（bps） */

    ipUartInitDss.fun = UartInitFun;        /* 太敏串口初始化 */
    ipUartInitDss.uartno = 7;               /* 串口号 */
    ipUartInitDss.stop = 0;                 /* 停止位配置：1为2位停止位，0为1位停止位 */
    ipUartInitDss.even = 0;                 /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    ipUartInitDss.baud = 250000;            /* 波特率配置（bps） */

    ipUartInitJet.fun = UartInitFun;        /* 推力器串口初始化 */
    ipUartInitJet.uartno = 10;              /* 串口号 */
    ipUartInitJet.stop = 0;                 /* 停止位配置：1为2位停止位，0为1位停止位 */
    ipUartInitJet.even = 0;                 /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    ipUartInitJet.baud = 250000;            /* 波特率配置（bps） */

    ipUartInitTC.fun = UartInitFun;         /* 遥控串口初始化 */
    ipUartInitTC.uartno = 11;               /* 串口号 */
    ipUartInitTC.stop = 0;                  /* 停止位配置：1为2位停止位，0为1位停止位 */
    ipUartInitTC.even = 0;                  /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    ipUartInitTC.baud = 250000;             /* 波特率配置（bps） */

    ipUartInitTM.fun = UartInitFun;         /* 遥测串口初始化 */
    ipUartInitTM.uartno = 12;               /* 串口号 */
    ipUartInitTM.stop = 0;                  /* 停止位配置：1为2位停止位，0为1位停止位 */
    ipUartInitTM.even = 0;                  /* 奇偶校验配置：2为无校验，1为奇校验，0为偶校验 */
    ipUartInitTM.baud = 250000;             /* 波特率配置（bps） */

    ipGetUartDataObdh.fun = GetUartDataFun; /* 遥控指令接收 */
    ipGetUartDataObdh.uartno = ipUartInitTC.uartno;
    ipGetUartDataObdh.len = 4;
    ipGetUartDataObdh.data = &obdhBuf[0];

    ipTcDataCheckObdh.fun = TcDataCheckFun;
    ipTcDataCheckObdh.data = &obdhBuf[0];

    ipB_TcProcessObdh.fun = B_TcProcessFun;
    ipB_TcProcessObdh.tcaData = &obdhBuf[0];

    ipGyroStateGet.fun = GyroStateGetFun;
    ipGyroStateGet.uartno = ipUartInitGyro.uartno;
    ipGyroStateGet.NumGyro = 9;

    ipDSSDataGet.fun = DSSDataGetFun;
    ipDSSDataGet.uartno = ipUartInitDss.uartno;

    ipGyroPick.fun = GyroPickFun;
    ipGyroPick.wa = &ipGyroStateGet.wa[0];
    ipGyroPick.waThr = 0.08f;
    ipGyroPick.pickThr = 6u;

    ipGyroAttiDetermine.fun = GyroAttiDetermineFun;
    ipGyroAttiDetermine.StateFlag = &ipGyroStateGet.stateFlag[0];
    ipGyroAttiDetermine.wa = &ipGyroPick.wa_out[0];
    ipGyroAttiDetermine.Gi = &Gi[0];
    ipGyroAttiDetermine.VGyro = &GyroMatrix[0][0];

    ipSAMSubModeDamp.fun = SAMSubModeDampFun;
    ipSAMSubModeDamp.m_curMode = &currentmode;
    ipSAMSubModeDamp.pRate = &rate[0];
    ipSAMSubModeDamp.time_D2P = 350;            /* 44.8s / 128ms = 350 */
    ipSAMSubModeDamp.time_D2P_overtime = 1000;  /* 128s  / 128ms = 1000 */

    ipSAMSubModePitch.fun = SAMSubModePitchFun;
    ipSAMSubModePitch.m_curMode = &currentmode;
    ipSAMSubModePitch.flgSP = &ipDSSDataGet.flgSP;
    ipSAMSubModePitch.piyaw = &ipDSSDataGet.piyaw;

    ipSAMSubModeRoll.fun = SAMSubModeRollFun;
    ipSAMSubModeRoll.m_curMode = &currentmode;
    ipSAMSubModeRoll.flgSP = &ipDSSDataGet.flgSP;
    ipSAMSubModeRoll.royaw = &ipDSSDataGet.royaw;

    ipThreeAxisController.fun = ThreeAxisControllerFun;
    ipThreeAxisController.pAngle = &angle[0];
    ipThreeAxisController.pRate = &rate[0];
    ipThreeAxisController.destRate = &attirateT[0];
    ipThreeAxisController.CTRL_PARAM_SAM[0].Kp = 0.567232f;
    ipThreeAxisController.CTRL_PARAM_SAM[1].Kp = 0.342085f;
    ipThreeAxisController.CTRL_PARAM_SAM[2].Kp = 0.0f;
    ipThreeAxisController.CTRL_PARAM_SAM[0].Kd = 6.387905f;
    ipThreeAxisController.CTRL_PARAM_SAM[1].Kd = 3.850196f;
    ipThreeAxisController.CTRL_PARAM_SAM[2].Kd = 3.813545f;
    //伪速率（Pseudo Rate）计算
    ipPseudoRate.fun = PseudoRateFun;
    ipPseudoRate.pu = &ipThreeAxisController.u[0];
    ipPseudoRate.h1[0] = 0.568f;
    ipPseudoRate.h1[1] = 0.342f;
    ipPseudoRate.h1[2] = 0.339f;
    //推力器（Thruster）控制逻辑
    ipThrusterCtrlLogic.fun = ThrusterCtrlLogicFun;
    ipThrusterCtrlLogic.Yp = &ipPseudoRate.Yp[0];
    ipThrusterCtrlLogic.Yn = &ipPseudoRate.Yn[0];
    
    ipJetCtrlSend.fun = JetCtrlSendFun;
    ipJetCtrlSend.uartno = ipUartInitJet.uartno;
    ipJetCtrlSend.pulse = &ipThrusterCtrlLogic.wPulse[0];

    ipCheckCal08TM.fun = CheckCal08Fun;
    ipCheckCal08TM.pkv = &tmDataBuf[0];
    ipCheckCal08TM.len = 99;

    ipSendUartDataTM.fun = SendUartDataFun;
    ipSendUartDataTM.uartno = ipUartInitTM.uartno;
    ipSendUartDataTM.buf = &tmDataBuf[0];
    ipSendUartDataTM.sendsize = 100;

    return;
}

/* 遥测打包函数 */
//把杂乱的内存数据（字节流）拼装成 CPU 能看懂的复杂变量（结构体）
void TMDataPack(void)
{
    unint32 i;

    /* 帧头	高字节在前	1~2	0xD0C1 */
    tmDataBuf[0] = 0xD0;
    tmDataBuf[1] = 0xC1;

    /* 星时	高字节在前	3~6	4字节单精度浮点 */
    starTime = (siint32)cntSate * 0.128f;
    Memcpyx((unint08 *)&tmDataBuf[2], (unint08 *)&starTime, 4);

    /* 模式字	高字节在前	7 */
    tmDataBuf[6] = currentmode;

    /* 滚动姿态角	高字节在前	8-11	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[7], (unint08 *)&angle[0], 4);

    /* 俯仰姿态角	高字节在前	12-15	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[11], (unint08 *)&angle[1], 4);

    /* 偏航姿态角	高字节在前	16-19	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[15], (unint08 *)&angle[2], 4);

    /* 滚动角速度	高字节在前	20-23	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[19], (unint08 *)&rate[0], 4);

    /* 俯仰角速度	高字节在前	24-27	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[23], (unint08 *)&rate[1], 4);

    /* 偏航角速度	高字节在前	28-31	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[27], (unint08 *)&rate[2], 4);

    /* 见太阳标志	高字节在前	32 */
    tmDataBuf[31] = ipDSSDataGet.flgSP;

    /* 陀螺选择标志	高字节在前	33 */
    tmDataBuf[32] = ipGyroAttiDetermine.gyroStatus0;
    
    for (i = 0; i < 6; i++)
	{
		if ((ipThrusterCtrlLogic.wPulse[2*i] == 0x1) || (ipThrusterCtrlLogic.wPulse[2*i+1] == 0x1))
        {
            jetWidT[i] += 0.128f;
        }
	}
    /* J1累计喷气量	高字节在前	34-37	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[33], (unint08 *)&jetWidT[0], 4);
    /* J2累计喷气量	高字节在前	38-41	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[37], (unint08 *)&jetWidT[1], 4);
    /* J3累计喷气量	高字节在前	42-45	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[41], (unint08 *)&jetWidT[2], 4);
    /* J4累计喷气量	高字节在前	46-49	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[45], (unint08 *)&jetWidT[3], 4);
    /* J5累计喷气量	高字节在前	50-53	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[49], (unint08 *)&jetWidT[4], 4);
    /* J6累计喷气量	高字节在前	54-57	4字节单精度浮点 */
    Memcpyx((unint08 *)&tmDataBuf[53], (unint08 *)&jetWidT[5], 4);

    /* 预留	高字节在前	58-99 */
    Memcpyx((unint08 *)&tmDataBuf[57], (unint08 *)&debugGyro.ErrCode, 4);
    Memcpyx((unint08 *)&tmDataBuf[61], (unint08 *)&debugGyro.ErrCnt, 4);
    Memcpyx((unint08 *)&tmDataBuf[65], (unint08 *)&debugDss.ErrCode, 4);
    Memcpyx((unint08 *)&tmDataBuf[69], (unint08 *)&debugDss.ErrCnt, 4);

    /* 累加和	高字节在前	100	前99字节累加和低8位 */

    return;
}

/* 初始化任务 */
void AppInit1(void)
{
    VarAssignInit();            /* 变量对接函数, 初始化调用一次 */

    IPCALL(ipUartInitGyro);     /* 初始化与陀螺通信端口 */
    IPCALL(ipUartInitDss);      /* 初始化与太敏通信端口 */
    IPCALL(ipUartInitJet);      /* 初始化与推力器通信端口 */
    IPCALL(ipUartInitTC);       /* 初始化与遥控指令通信端口 */
    IPCALL(ipUartInitTM);       /* 初始化与遥测通信端口 */

    return;
}

void AppTask(void)
{
    // Set cntSate  cntSate + 1;
    cntSate = cntSate + 1;

    // Set cntMode  cntMode + 1;
    cntMode = cntMode + 1;

    /* 从串口获取obdh数据 */
    IPCALL(ipGetUartDataObdh);

    if (ipGetUartDataObdh.bSucc == 0x1)     /* OBDH收到数据 */
    {
        /* 遥控指令格式校验 */
        IPCALL(ipTcDataCheckObdh);

        if (ipTcDataCheckObdh.ret == 0x1)   /* 遥控指令格式校验通过 */
        {
            /* 遥控数据解包处理 */
            IPCALL(ipB_TcProcessObdh);

            // Set nextmode workmode;
            nextmode = *ipB_TcProcessObdh.workMode;
        }
    }

    /* 9陀螺数据采集 */
    IPCALL(ipGyroStateGet);

    /* 2太阳敏感器数据采集 */
    IPCALL(ipDSSDataGet);

    /* 陀螺剔野处理 */
    IPCALL(ipGyroPick);

    /* 陀螺姿态确定 */
    IPCALL(ipGyroAttiDetermine);

    /* 陀螺与太阳敏感器姿态确定 */
    if (currentmode == SAM_CRUISE)          /* 巡航方式 */
    {
        if (ipDSSDataGet.flgSP == 1)        /* 太阳可见 */
        {
            angle[0] = ipDSSDataGet.royaw;  /* 滚动角用太敏 */
            angle[1] = ipDSSDataGet.piyaw;  /* 俯仰角用太敏 */

            /* 将太敏读数替换当前积分值 */
            Gi[0] = ipDSSDataGet.royaw;     /* 滚动角陀螺积分  */
            Gi[1] = ipDSSDataGet.piyaw;     /* 俯仰角陀螺积分  */
        }
        else                                /* 太阳不可见 */
        {
            angle[0] = Gi[0];               /* 滚动角用陀螺积分 */
            angle[1] = Gi[1];               /* 俯仰角用陀螺积分 */
        }
    }
    else    /* 其他模式 */
    {
        angle[0] = 0.0f;                    /* 滚动角清零 */
        angle[1] = 0.0f;                    /* 俯仰角清零 */
    }

    rate[0] = ipGyroAttiDetermine.W[0];     /* 滚动角速度用陀螺算出的滚动角速度 */
    rate[1] = ipGyroAttiDetermine.W[1];     /* 俯仰角速度用陀螺算出的俯仰角速度 */
    rate[2] = ipGyroAttiDetermine.W[2];     /* 偏航角速度用陀螺算出的偏航角速度 */

    switch (currentmode)
    {
        case SAM_DAMP:
            IPCALL(ipSAMSubModeDamp);
            nextmode = ipSAMSubModeDamp.m_workMode;
            break;
        case SAM_PITCH:
            IPCALL(ipSAMSubModePitch);
            nextmode = ipSAMSubModePitch.m_workMode;
            break;
        case SAM_ROLL:
            IPCALL(ipSAMSubModeRoll);
            nextmode = ipSAMSubModeRoll.m_workMode;
            break;
        case SAM_CRUISE:
            nextmode = SAM_CRUISE;
            break;
        default:
            nextmode = SAM_DAMP;
            break;
    }

    if ( currentmode != nextmode )
    {
        /* 模式初始化 */
        currentmode = nextmode;
        cntMode = 0;

        switch (nextmode)
        {
            /* 设置三轴目标角速度 */
            case SAM_DAMP:
                attirateT[0] = 0.0;
                attirateT[1] = 0.0;
                attirateT[2] = 0.0;
                break;
            case SAM_PITCH:
                attirateT[0] = 0.0;
                attirateT[1] = 0.5;
                attirateT[2] = 0.0;
                break;
            case SAM_ROLL:
                attirateT[0] = 0.5;
                attirateT[1] = 0.0;
                attirateT[2] = 0.0;
                break;
            case SAM_CRUISE:
                attirateT[0] = 0.0;
                attirateT[1] = 0.0;
                attirateT[2] = 0.0;
                break;
            default:
                break;
        }
    }

    /* 推力器数据控制计算 */
    IPCALL(ipThreeAxisController);
    IPCALL(ipPseudoRate);
    IPCALL(ipThrusterCtrlLogic);

    /* 控制量输出 */
    IPCALL(ipJetCtrlSend);

    /* 遥测打包 */
    TMDataPack();
    /* 校验和计算 */
    IPCALL(ipCheckCal08TM);
    tmDataBuf[99] = ipCheckCal08TM.chksum & 0xFFu;
    /* 遥测数据发送 */
    IPCALL(ipSendUartDataTM);

    return;
}

void InterruptTask(void)
{
    /*在周期的128ms，发送推力器数据，100us内完成 */
    // At(128ms, Period) labelSD1 SendData pulseWidth Finished Within 100us;

    return;
}

/* 主函数 */
#ifndef __GCC_COMPILED__
int main()
{
    AppInit1();

    do
    {
        AppTask();

    } while(1) ;

    return 0;
}
#endif

/* end of file */
