/* std_utils.h - 基础公共功能实现头文件 */
/* 版权 2013-2025 北京控制工程研究所软件中心 */
/* 基础公共运算函数的使用:参见CMtool上《基础公共运算构件使用说明》 */

#ifndef STD_UTILS_H
#define STD_UTILS_H

#include "std_basal.h"


/* 按字操作缓冲区地址对齐掩码 */
#define GFH_ALIGNMENT   0x03

/* numerical\LimitFloat.c               功能描述：单精度浮点数限幅，[-fbound，fbound]
 *
 * 输入参数：fin   ：待判断的值
 *           fbound：限幅阈值
 *
 * 输出参数：无
 * 返 回 值：限幅处理后的值
*/
float32 LimitFloat(float32 fin, float32 fbound);

/* trivalue\Tr32Float.c                 功能描述：单精度浮点数的三取二读操作；
 * 输入参数：pA一区指针, pB二区指针, pC三区指针；
 * 输出参数：无；
 * 返 回 值：三取二的值；
*/
float32 Tr32Float(volatile float32 *pA, volatile float32 *pB, volatile float32 *pC);

/* trivalue\Tr32FloatValue.c            功能描述：单精度浮点数的三取二写操作；
 * 输入参数：f32Value，待写单精度值；
 * 输出参数：pA一区指针, pB二区指针, pC三区指针；
 * 返 回 值：无；
*/
void Tr32FloatValue(volatile float32 *pA, volatile float32 *pB, volatile float32 *pC, float32 f32Value);

/* trivalue\Tr32Uint.c                  功能描述：无符号32位整型数的三取二读操作；
 * 输入参数：pA一区指针, pB二区指针, pC三区指针；
 * 输出参数：无；
 * 返 回 值：三取二的值；
*/
unint32 Tr32Uint(volatile unint32 *pA, volatile unint32 *pB, volatile unint32 *pC);

/* trivalue\Tr32UintValue.c             功能描述：无符号32位整型数的三取二写操作；
 * 输入参数：uivalue，待写无符号32位整型数；
 * 输出参数：pA一区指针, pB二区指针, pC三区指针；
 * 返 回 值：无；
*/
void Tr32UintValue(volatile unint32 *pA, volatile unint32 *pB, volatile unint32 *pC, unint32 uivalue);



extern float32 DiviationToFloat(unint16 input, unint16 mask, unint16 offset, float32 LSB);

/* 功能:求三个单精度浮点数中绝对值最大的数 */
extern float32 TripleFabsMaxF(float32 fx1, float32 fy2, float32 fz3);

/* 功能:单精度浮点数限幅,要求限幅的阀值fbound大于0 */
extern float32 LimitFloat(float32 fin, float32 fbound);

/* 功能:无符号8位整形数的三取二,并回写 */
extern unint08 Tr32Uint08(volatile unint08* pA, volatile unint08* pB, volatile unint08* pC);

/* 功能： 矩阵/向量的转置,注意源和目标矩阵/向量不能是同一个 */
extern void MatrixTranF(float32* tran, const float32* mat, unint08 nrow, unint08 ncol);

/* 功能：两个矩阵/向量相乘 */
extern void MatrixMultiF(float32* product, const float32* faciend, const float32* multiplier, unint08 nrow, unint08 nrc, unint08 ncol);

/***********************************************************************************************
功能：单精度3×3矩阵求逆
***********************************************************************************************/
extern unint32 MatrixInv33F(float32* inv, const float32* src);

extern float32 ModPNHP(float32 x, float32 halfperiod);

extern void Memcpyx(unint08 *destination, const unint08 *source, unint32 nbytes);


#endif
