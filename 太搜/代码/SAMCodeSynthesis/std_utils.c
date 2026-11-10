
/* std_utils.c - 基础公共功能实现源文件 */
/* 版权 2013-2025 北京控制工程研究所软件中心 */
/* 基础公共运算函数的使用:参见CMtool上《基础公共运算构件使用说明》 */

#include "std_utils.h"

/* 功能描述：偏移二进制码转换为单精度浮点数
 *
 * 输入参数：input ：被转换数
 *           mask  ：掩码
 *           offset：偏移量
 *           LSB   ：最小当量
 *
 * 输出参数：无
 * 返 回 值：转化结果浮单精度点数
 */
float32 DiviationToFloat(unint16 input, unint16 mask, unint16 offset, float32 LSB)
{
    float32 fresult;		                                /* 局部变量 */

    fresult = ((siint16)((input & mask) - offset)) * LSB;	/* LSB为最小当量 */

    return fresult;
}

/* 功能:求三个单精度浮点数中绝对值最大的数 */
float32 TripleFabsMaxF(float32 fx1, float32 fy2, float32 fz3)
{
    float32 fabsfx1;            /* 参数1的绝对值 */
    float32 fabsfy2;            /* 参数2的绝对值 */
    float32 fabsfz3;            /* 参数3的绝对值 */
    float32 tmax;               /* 最大值 */

    /* 默认为正 */
    fabsfx1 = fx1;                                          /* 赋初值1 */
    fabsfy2 = fy2;                                          /* 赋初值2 */
    fabsfz3 = fz3;                                          /* 赋初值3 */

    /* 取绝对值1 */
    if (fx1 < 0.0f)
    {
        fabsfx1 = -fx1;                                     /* 参数1为负 */
    }

    /* 取绝对值2 */
    if (fy2 < 0.0f)
    {
        fabsfy2 = -fy2;                                     /* 参数2为负 */
    }

    /* 取绝对值3 */
    if (fz3 < 0.0f)
    {
        fabsfz3 = -fz3;                                     /* 参数3为负 */
    }

    /* 求数1与数2绝对值的最大值 */
    if (fabsfx1 > fabsfy2)
    {
        tmax = fabsfx1;                                /* 1绝对值大 */
    }
    else
    {
        tmax = fabsfy2;                                /* 2绝对值大 */
    }

    /* 求数1数2最大值与数3绝对值的最大值 */
    if (fabsfz3 > tmax)
    {
        tmax = fabsfz3;                                /* 3绝对值大 */
    }

    return tmax;
}

/* 功能:单精度浮点数限幅,要求限幅的阀值fbound大于0 */
float32 LimitFloat(float32 fin, float32 fbound)
{
    float32 fvalue;

    if (fin > fbound)
    {
        fvalue = fbound;
    }
    else if (fin < -fbound)
    {
        fvalue = -fbound;
    }
    else
    {
        fvalue = fin;
    }

    return fvalue;
}

/* 功能:无符号8位整形数的三取二,并回写 */
unint08 Tr32Uint08(volatile unint08* pA, volatile unint08* pB, volatile unint08* pC)
{
    unint08 uitemp1;
    unint08 uitemp2;
    unint08 uitemp3;
    unint08 uiresult;

    if (((*pA) == (*pB)) && ((*pA) == (*pC)))
    {
        uiresult = (*pA);
    }
    else
    {
        uitemp1 = (*pA) & (*pB);
        uitemp2 = (*pA) & (*pC);
        uitemp3 = (*pB) & (*pC);
        uiresult = uitemp1 | uitemp2 | uitemp3;

        *pA = uiresult;
        *pB = uiresult;
        *pC = uiresult;
    }

    return uiresult;
}


/* 功能： 矩阵/向量的转置,注意源和目标矩阵/向量不能是同一个 */
void MatrixTranF(float32* tran, const float32* mat, unint08 nrow, unint08 ncol)
{
    /* 注意源和目标矩阵/向量不能是同一个 */
    unint08 i;      /* 矩阵行循环变量 */
    unint08 j;      /* 矩阵列循环变量 */

    /* tran:目标矩阵 */
    /* mat: 源矩阵 */
    /* nrow:矩阵行数 */
    /* ncol:矩阵列数 */

    for (i = 0; i < nrow; i++)                              /* 行循环 */
    {
        for (j = 0; j < ncol; j++)                          /* 列循环 */
        {
            *(tran + j * nrow + i) = *(mat + i * ncol + j);
        }
    }

    return;
}

/* 功能：两个矩阵/向量相乘 */
void MatrixMultiF(float32* product, const float32* faciend, const float32* multiplier, unint08 nrow, unint08 nrc, unint08 ncol)
{
    unint08 ir;         /* 行循环变量 */
    unint08 jc;         /* 列循环变量 */
    unint08 nk;         /* 求积后做加个数 */
    unint08 index;      /* 矩阵计算结果位置 */

    /* product:求和结果矩阵指针 */
    /* faciend:求和矩阵 */
    /* multiplier:被求和矩阵 */
    /* nrow:矩阵行数 */
    /* nrc:求积后做加个数 */
    /* ncol:矩阵列数 */

    for (ir = 0; ir < nrow; ir++)                       /* 行循环 */
    {
        for (jc = 0; jc < ncol; jc++)                   /* 列循环 */
        {
            index = ir * ncol + jc;                     /* 矩阵计算结果位置 */

            product[index] = 0.0f;                      /* 乘积结果默认取0 */

            for (nk = 0; nk < nrc; nk++)                /* 求积后做加个数循环 */
            {
                product[index] = product[index] + faciend[ir * nrc + nk] * multiplier[nk * ncol + jc];
            }
        }
    }

    return;
}

/***********************************************************************************************
功能：单精度3×3矩阵求逆
***********************************************************************************************/
unint32 MatrixInv33F(float32* inv, const float32* src)
{
    siint08 i;
    float32 rank;
    unint32 bAbleInv;   /* TRUE32:矩阵可逆 */

    /* inv:输出结果矩阵指针 */
    /* src:输如计算矩阵指针 */

    /* 默认不可逆 */
    bAbleInv = FALSE32;

    inv[0] = src[4] * src[8] - src[5] * src[7];             /* 第1行第1列 */
    inv[1] = src[2] * src[7] - src[1] * src[8];             /* 第1行第2列 */
    inv[2] = src[1] * src[5] - src[2] * src[4];             /* 第1行第3列 */
    inv[3] = src[5] * src[6] - src[3] * src[8];             /* 第2行第1列 */
    inv[4] = src[0] * src[8] - src[2] * src[6];             /* 第2行第2列 */
    inv[5] = src[2] * src[3] - src[0] * src[5];             /* 第2行第3列 */
    inv[6] = src[3] * src[7] - src[4] * src[6];             /* 第3行第1列 */
    inv[7] = src[1] * src[6] - src[0] * src[7];             /* 第3行第2列 */
    inv[8] = src[0] * src[4] - src[1] * src[3];             /* 第3行第3列 */

    /* 求矩阵的行列式值 */
    rank = src[0] * inv[0] + src[1] * inv[3] + src[2] * inv[6];


    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO))         /* 不等于浮点数0 */
    {

        bAbleInv = TRUE32;                                   /* 矩阵可逆 */

        for (i = 0; i < 9; i++)                                  /* 行列式 */
        {
            inv[i] = inv[i] / rank;
        }
    }
    else
    {
        /* 矩阵不可逆时与原矩阵一致 */
        for (i = 0; i < 9; i++)
        {
            inv[i] = src[i];
        }
    }

    return bAbleInv;
}

/* 功能:限在(-divisor, divisor)之间 */
float32 ModPNHP(float32 x, float32 halfperiod)
{
    float32 period;                                         /* 周期 */
    float32 npp2;                                           /* 限幅后的返回值 */

    /* 计算周期值 */
    period = 2.0f * halfperiod;

    npp2 = x - floor((x + halfperiod) / period) * period;   /* 限幅并返回 */

    return npp2;
}

/* 按字节拷贝缓冲区 */
void Memcpyx(unint08 *destination, const unint08 *source, unint32 nbytes)
{
    /* destination: 目标缓冲指针 */
    /* source:      源缓冲指针 */
    /* nbytes:      拷贝字节个数 */

    unint08 *dstend;    /* 目标结束地址 */
    unint32 *dst;       /* 字拷贝操作目标地址 */
    unint32 *src;       /* 字拷贝操作源地址 */
    siint32 tmp;        /* 目标开始地址与源开始地址长度差 */

    /* 计算目标地址与源地址长度差 */
    tmp = (siint32)((unint32)destination - (unint32)source);

    /* 目标缓冲在前 或者 目标缓冲在后且拷贝未重叠 */
    if ((tmp <= 0) || (tmp >= (siint32)nbytes))
    {
        /* forward copy */
        dstend = destination + nbytes;

        /* do byte copy if less than ten or GFH_ALIGNMENT mismatch */
        if ((nbytes < 10) ||
            ((((unint32)destination ^ (unint32)source) & GFH_ALIGNMENT) != 0))
        {
            tmp = 0;     /* 空语句占位代码 */
        }
        else
        {
            /* if odd-aligned copy byte */
            while (((unint32)destination & GFH_ALIGNMENT) != 0)
            {
                *destination++ = *source++;
            }

            /* 地址对齐后,提高效率 */
            src = (unint32 *)source;            /* 计算字拷贝操作源地址 */
            dst = (unint32 *)destination;       /* 计算字拷贝操作目标地址 */

            do
            {
                *dst++ = *src++;

            } while (((unint08 *)dst + sizeof(unint32)) <= dstend);

            destination = (unint08 *)dst;       /* 计算字节拷贝操作目标地址 */
            source      = (unint08 *)src;       /* 计算字节拷贝操作源地址 */
        }

        /* 按字节拷贝数据 */
        while (destination < dstend)
        {
            *destination++ = *source++;
        }
    }
    else    /* 目标缓冲在后且拷贝重叠 */
    {
        /* backward copy */
        dstend      = destination;
        destination = destination + (nbytes - 1);   /* 计算目标地址 */
        source      = source      + (nbytes - 1);   /* 计算源地址 */

        /* do byte copy if less than ten or GFH_ALIGNMENT mismatch */
        if ((nbytes < 10) ||
            ((((unint32)destination ^ (unint32)source) & GFH_ALIGNMENT) != 0))
        {
            tmp = 0;    /* 空语句占位代码 */
        }
        else
        {
            /* if odd-aligned copy byte */
            while (((unint32)destination & GFH_ALIGNMENT) != 3)
            {
                *destination-- = *source--;
            }

            src = (unint32 *)(source - 3);      /* 计算字拷贝操作源地址 */
            dst = (unint32 *)(destination - 3); /* 计算字拷贝操作目标地址 */

            do
            {
                *dst-- = *src--;

            } while ((unint08 *)dst >= dstend);

            /* 在字拷贝完成之后, 字节拷贝的起始地址为字拷贝后的地址+3 */
            destination = (unint08 *)dst + 3;   /* 计算字节拷贝操作目标地址 */
            source      = (unint08 *)src + 3;   /* 计算字节拷贝操作源地址 */
        }

        /* 按字节拷贝数据 */
        while (destination >= dstend)
        {
            *destination-- = *source--;
        }
    }

    return;
}

/* end of file */
