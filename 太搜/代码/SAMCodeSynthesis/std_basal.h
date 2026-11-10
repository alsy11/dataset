/* std_basal.h - 规范化基本数据类型定义头文件 */
/* 版权归属北京控制工程研究所软件中心 */
/* 2013.11.29 */

#ifndef STD_BASAL_H
#define STD_BASAL_H

#include <math.h>
#include <float.h>
#include <limits.h>
#include <assert.h>

typedef signed   char       siint08;
typedef unsigned char       unint08;
typedef short               siint16;
typedef unsigned short      unint16;
typedef int                 siint32;
typedef unsigned int        unint32;
typedef float               float32;
typedef double              float64;

typedef unsigned int        boolu32;    /* 二态布尔型 */
typedef unsigned int        dimorph;    /* 二态型 */
typedef          int        polymor;    /* 多态量(可正可负) */

#ifdef __GCC_COMPILED__
typedef long long           llong64;
typedef unsigned long long  ulong64;
#else
typedef __int64             llong64;
typedef unsigned __int64    ulong64;
#endif

#define TRUE32              0xEB90146Fu /* 逻辑真 */
#define FALSE32             0x00000000u /* 逻辑假 */

/* 整型数据类型范围边界: 极大值与极小值 */
#define UNINT08_MAX         UCHAR_MAX   /*  255 */
#define UNINT08_MIN         0u          /*  0 */
#define SIINT08_MAX         SCHAR_MAX   /*  127 */
#define SIINT08_MIN         SCHAR_MIN   /* -128 */

#define UNINT16_MAX         USHRT_MAX   /*  65535 */
#define UNINT16_MIN         0u          /*  0 */
#define SIINT16_MAX         SHRT_MAX    /*  32767 */
#define SIINT16_MIN         SHRT_MIN    /* -32768 */

#define UNINT32_MAX         UINT_MAX    /*  4294967295 */
#define UNINT32_MIN         0u          /*  0 */
#define SIINT32_MAX         INT_MAX     /*  2147483647 */
#define SIINT32_MIN         INT_MIN     /* -2147483648 */

#define FLT32_ZERO                 1.0E-6

#ifdef __GCC_COMPILED__
    #define ULONG64_MAX     ULONG_MAX   /*  18446744073709551615 */
    #define ULONG64_MIN     0u          /*  0 */
    #define LLONG64_MAX     LONG_MAX    /*  9223372036854775807  */
    #define LLONG64_MIN     LONG_MIN    /* -9223372036854775808  */
#else

    #if _MSC_VER > 1200    /* VC6(C89)以上版本 */
        #define ULONG64_MAX     ULLONG_MAX  /*  18446744073709551615 */
        #define ULONG64_MIN     0u          /*  0 */
        #define LLONG64_MAX     LLONG_MAX   /*  9223372036854775807  */
        #define LLONG64_MIN     LLONG_MIN   /* -9223372036854775808  */
    #else                    /* VC6(C89)不支持如下定义 */
        #define ULONG64_MAX     0u            /* 无效定义 */
        #define ULONG64_MIN     0u          /* 无效定义 */
        #define LLONG64_MAX     0            /* 无效定义 */
        #define LLONG64_MIN     0            /* 无效定义 */
    #endif
#endif

/* 浮点数数据类型范围边界: 极大值与极小值 */
#define FLOAT32_MAX         FLT_MAX     /* 3.4028235e+038          */
#define FLOAT32_MIN         FLT_MIN     /* 1.1754944e-038          */
#define FLOAT64_MAX         DBL_MAX     /* 1.7976931348623157e+308 */
#define FLOAT64_MIN         DBL_MIN     /* 2.2250738585072014e-308 */

/* 基本库函数重定义 */
#define Sinx(x)         (sin((float64)(x))                )
#define Cosx(x)         (cos((float64)(x))                )
#define Tanx(x)         (tan((float64)(x))                )
#define Atanx(x)        (atan((float64)(x))               )
#define Atan2x(y, x)    (atan2((float64)(y), (float64)(x)))     /* 坐标y为第一参数, 坐标x为第二参数 */
#define Sqrtx(x)        (sqrt((float64)(x))               )
#define Ceilx(x)        (ceil((float64)(x))               )     /* 向上取整 +∞ */
#define Floorx(x)       (floor((float64)(x))              )     /* 向下取整 -∞ */
#define Fixx(x)         ((siint32)(x)                     )     /* 向零取整 */
#define Expx(x)         (exp((float64)(x))                )
#define Fabsx(x)        (fabs((float64)(x))               )
#define Powx(x, y)      (pow((float64)(x), (float64)(y))  )
#define Logx(x)         (log((float64)(x))                )
#define Log10x(x)       (log10((float64)(x))              )

/* 四舍五入取整 */
#ifdef __GCC_COMPILED__
#define Roundx(x)       (round((float64)(x))              )
#else
#define Roundx(x)       (((x)>0) ? Floorx((x)+0.5) : Ceilx((x)-0.5))    /* 等价于 (((x)>0) ? (siint32)((x)+0.5) : (siint32)((x)-0.5))  */
#endif

/* ----------------------------------------------------------------------------------------- */
/* 空语句占位代码 */
#define NULL_STATEMENT()    do{ }while(0)

/* 空指针 */
#define NULL_PTR            (0x00u)

/* ----------------------------------------------------------------------------------------- */
/* 断言定义 */
#ifdef __GCC_COMPILED__
    #ifdef __ASSERT_ENABLE__
        extern void print2(char fmt[],...);     /* 声明系统软件串口打印函数 */
        #define  ASSERT(x)      {if (!(x)) { do{ print2("\r\nAssert failed !!!"); } while(1); } }       /* V7编译器不支持换行操作 */
    #else
        #define  ASSERT(x)      ((void)0)
    #endif
#else
    #define      ASSERT(x)      assert((x))
#endif

#endif  /* STD_BASAL_H */
