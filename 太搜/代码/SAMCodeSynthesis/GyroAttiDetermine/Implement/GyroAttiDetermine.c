#include "GyroAttiDetermine.h"

void GyroAttiDetermineFun(void *p)
{
    GyroAttiDetermine *pIp = (GyroAttiDetermine*)p;

    unint32 i, j, k ;
    float32 Rgtrans[3][5] ;
    float32 Rs[3][3] ;
    float32 RsInv[3][3] ;
    float32 Rgtemp[5][3] ;
    float32 tmpwa[5] ;
    float32 dgi[2] ;

    /* 确定参加工作陀螺的个数 */
    pIp->JoinTotal = 0 ;                /* 参加定姿的陀螺个数清零 */
    pIp->gyroStatus0 = 0 ;

    for ( i = 0 ; i < 9 ; i++ )         /* 9个陀螺进行判断 */
    {
        if (pIp->StateFlag[i] == TRUE)              /* 如果陀螺状态正常 */
        {
            pIp->SignFlag[pIp->JoinTotal] = i ;     /* 统计参加定姿的陀螺螺序号 */
            pIp->JoinTotal++ ;                      /* 统计参加定姿的陀螺个数 */
            pIp->gyroStatus0 = pIp->gyroStatus0 | (1 << i) ;
        }
    }

    pIp->JoinTotal = MIN(pIp->JoinTotal, 5) ;

    if (pIp->gyroStatus0 != pIp->gyroStatus1)       /* 有陀螺切换 */
    {
        for ( j = 0 ; j < pIp->JoinTotal ; j++ )    /* 参加定姿的陀螺个数 */
        {
            k = pIp->SignFlag[j] ;  /* 按从小到大排列依次选5个，不足5个选余下的 */

            for ( i = 0 ; i < 3 ; i++ )
            {
                Rgtemp[j][i] = pIp->VGyro[k*3+i] ;  /* n*3的安装阵R */
            }
        }

        for ( i = pIp->JoinTotal ; i < 5 ; i++ )    /* 不用的（5-JoinTotal）维，清零 */
        {
            for ( j = 0 ; j < 3 ; j++ )
            {
                Rgtemp[i][j] = 0.0f;
            }
        }

        if (pIp->JoinTotal >= 3)    /* 若大于三个陀螺工作可以计算角速度 */
        {
            MatrixTranF(&Rgtrans[0][0], &Rgtemp[0][0], 5, 3) ;/* Rg->Rgtrans    */
            MatrixMultiF(&Rs[0][0], &Rgtrans[0][0], &Rgtemp[0][0], 3, 5, 3) ;/* R*RT->RS */
            MatrixInv33F(&RsInv[0][0], &Rs[0][0]) ;/* INV(RS)->RsInv */
            MatrixMultiF(&pIp->Rtemp[0][0], &RsInv[0][0], &Rgtrans[0][0], 3, 3, 5) ;/* RsInv*Rgtrans->Rtemp */
        }
        pIp->gyroStatus1 = pIp->gyroStatus0 ;
    }

    for (j = 0; j < 5; j++) /* 给临时数组赋值 */
    {
        tmpwa[j] = 0.0f;    /* 赋值为0，使用时修改 */
    }
    for (j = 0; j < pIp->JoinTotal; j++)
    {
        k = pIp->SignFlag[j];  /* 所有参加定姿陀螺的序号 */
        tmpwa[j] = pIp->wa[k]; /* 取对应序号的模拟量测量值 */
    }

    if (pIp->JoinTotal >= 3) /* 若大于三个陀螺工作可定姿 */
    {
        /* 算角速度 */
        MatrixMultiF(&pIp->W[0], &pIp->Rtemp[0][0], &tmpwa[0], 3, 5, 1);
    }
    else
    {
        pIp->W[0] = 0.0f; /* 参加定姿的陀螺太少 */
        pIp->W[1] = 0.0f;
        pIp->W[2] = 0.0f;
    }

    /* SAM不进行陀螺漂移补偿 */
    dgi[0] = (pIp->Gi[0]) + pIp->W[0] * 0.128f; /* 控制周期0.128 */
    dgi[1] = (pIp->Gi[1]) + pIp->W[1] * 0.128f; /* 控制周期0.128 */

    /* 陀螺角度积分,限在(-180, 180)之间 */
    // (pIp->Gi[0]) = ModPNHP(dgi[0], 180.0f) ;     /* 滚动角积分 = 上周期积分总值 + 本周期积分改变值 */
    // (pIp->Gi[1]) = ModPNHP(dgi[1], 180.0f) ;     /* 滚动角积分 = 上周期积分总值 + 本周期积分改变值 */
    (pIp->Gi[0]) = dgi[0] - floor((dgi[0] + 180.0f) / 360.0f) * 360.0f;
    (pIp->Gi[1]) = dgi[1] - floor((dgi[0] + 180.0f) / 360.0f) * 360.0f;

    return;
}
