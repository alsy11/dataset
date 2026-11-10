#if !defined(__IP_H__)
#define __IP_H__

#include "std_utils.h"
#ifdef __GCC_COMPILED__
#include "DRV_UART.h"
#include "UartRs422.h"
#endif

typedef void            (*Fun)(void *);

#define IPCALL(IP)		(IP.fun(&IP))

#define IPCREATE(IpName, InstName, ...) IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };

#define TRUE            			0x01
#define FALSE           			0x00

// #define FLT32_ZERO                 1.0E-6

#define ABS(a)                  	(((a) > 0) ? (a) : -(a))
#define MIN(a, b)                   (((a) > (b)) ? (b) : (a))

#define SAM_DAMP            		0x00	/* SAM速率阻尼方式 */
#define SAM_PITCH           		0x11	/* SAM俯仰搜索方式 */
#define SAM_ROLL            		0x22	/* SAM滚动搜索方式 */
#define SAM_CRUISE          		0x33	/* SAM巡航方式 */
#define NOCTRL						0x44	/* 不控 */

#define MASK_LOLO_08                0xFF

/* --------三取二分区定义-------- */
#define FST_FLGMODE					((volatile unint08 *)0x7D00)
#define FST_BIAS_WXRO       		((volatile float32 *)0x7D18)
#define FST_BIAS_WYPI       		((volatile float32 *)0x7D1C)
#define FST_FT_HEALTHWORD      	    ((volatile unint32 *)0x7D24)

#define SND_FLGMODE					((volatile unint08 *)0x7E54)
#define SND_BIAS_WXRO       		((volatile float32 *)0x7E6C)
#define SND_BIAS_WYPI       		((volatile float32 *)0x7E70)
#define SND_FT_HEALTHWORD       	((volatile unint32 *)0x7E78)

#define TRD_FLGMODE					((volatile unint08 *)0x7FA8)
#define TRD_BIAS_WXRO       		((volatile float32 *)0x7FC0)
#define TRD_BIAS_WYPI       		((volatile float32 *)0x7FC4)
#define TRD_FT_HEALTHWORD       	((volatile unint32 *)0x7FCC)

#define TR32_FLGMODE()				Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)
#define TR32_BIAS_WXRO()			Tr32Float(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO)
#define TR32_BIAS_WYPI()			Tr32Float(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI)
#define TR32_FT_HEALTHWORD()		Tr32Uint(FST_FT_HEALTHWORD, SND_FT_HEALTHWORD, TRD_FT_HEALTHWORD)

#define TR32_FLGMODE_VALUE(x)		TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#define TR32_BIAS_WXRO_VALUE(x)		TR32_VALUE(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO, (x))
#define TR32_BIAS_WYPI_VALUE(x)		TR32_VALUE(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI, (x))

#define TR16_VALUE(pA,pB,pC,nval)   {*(pA) = (nval);    *(pB) = (nval);    *(pC) = (nval);}
#define TR32_VALUE(pA,pB,pC,nval)   {*(pA) = (nval);    *(pB) = (nval);    *(pC) = (nval);}

/* 往硬件地址写32位数据宏函数 */
// #define ADDR_WRITE(addr, value)     {(*((volatile unint32 *)(addr))) = (value);}
#define ADDR_WRITE(addr, value)     ((addr))

/* 往硬件地址写32位数据宏函数 */
#define ADDR_WRITE16(addr, val16)   {(*((volatile unint16 *)(addr))) = (val16);}

/* 从硬件地址读32位数据宏函数 */
// #define ADDR_READ(addr)             (*((volatile unint32 *)(addr)))
#define ADDR_READ(addr)             ((addr))

/* 从硬件地址读16位数据宏函数 */
#define ADDR_READ16(addr)           (ADDR_READ((addr)) & 0xFFFF)

/* 从硬件地址读8位数据宏函数 */
#define ADDR_READ08(addr)           (ADDR_READ((addr)) & 0xFF)

/* ----------------------------------------------------------------------------------------- */
/* 位操作宏函数 */
/* u08 mask=0x000000FF, bp=0~7 */
/* u16 mask=0x0000FFFF, bp=0~15 */
/* u32 mask=0xFFFFFFFF, bp=0~31 */
#define BIT_GET(uv, bp)                 (((uv) >> (bp)) & 0x01u)
#define BIT_SET(uv, bp, mask)           ((uv) = (uv) | ((0x01u << (bp)) & (mask)))
#define BIT_CLR(uv, bp, mask)           ((uv) = (uv) & ((0x01u << (bp)) ^ (mask)))

/* u32为字节数据,bp=0~31 */
#define UI32_BIT_GET(uv, bp)            BIT_GET((uv), (bp))
#define UI32_BIT_SET(uv, bp)            BIT_SET((uv), (bp), MASK_ALL8F)
#define UI32_BIT_CLR(uv, bp)            BIT_CLR((uv), (bp), MASK_ALL8F)

#define UI16_HI8(ui16)                  (((ui16) >>  8) & MASK_LOLO_08)
#define UI16_LO8(ui16)                  (((ui16)      ) & MASK_LOLO_08)

typedef union
{
    unint32  Word;
    siint32  sWord;
    float32  Float;
    struct
    {
        unsigned High   : 16;           /* 高16位 */
        unsigned Low    : 16;           /* 低16位 */
    } Half;

    struct
    {
        unsigned High_h :8;             /* 高16位中的高8位 */
        unsigned High_l :8;             /* 高16位中的低8位 */
        unsigned Low_h  :8;             /* 低16位中的高8位 */
        unsigned Low_l  :8;             /* 低16位中的低8位 */
    } Byte;

    struct
    {
        unsigned HB1    : 4;             /* 高12－15 */
        unsigned HB2    : 4;             /* 高8－11 */
        unsigned HB3    : 4;             /* 高4－7 */
        unsigned HB4    : 4;             /* 高0－3 */
        unsigned LB1    : 4;             /* 低12－15 */
        unsigned LB2    : 4;             /* 低8－11 */
        unsigned LB3    : 4;             /* 低4－7 */
        unsigned LB4    : 4;             /* 低0－3 */
    } Bit4;

    struct
    {

        unsigned D31     : 1;            /* D31位 */
        unsigned D30     : 1;            /* D30位 */
        unsigned D29     : 1;            /* D29位 */
        unsigned D28     : 1;            /* D28位 */
        unsigned D27     : 1;            /* D27位 */
        unsigned D26     : 1;            /* D26位 */
        unsigned D25     : 1;            /* D25位 */
        unsigned D24     : 1;            /* D24位 */

        unsigned D23     : 1;            /* D23位 */
        unsigned D22     : 1;            /* D22位 */
        unsigned D21     : 1;            /* D21位 */
        unsigned D20     : 1;            /* D20位 */
        unsigned D19     : 1;            /* D19位 */
        unsigned D18     : 1;            /* D18位 */
        unsigned D17     : 1;            /* D17位 */
        unsigned D16     : 1;            /* D16位 */

        unsigned D15     : 1;            /* D15位 */
        unsigned D14     : 1;            /* D14位 */
        unsigned D13     : 1;            /* D13位 */
        unsigned D12     : 1;            /* D12位 */
        unsigned D11     : 1;            /* D11位 */
        unsigned D10     : 1;            /* D10位 */
        unsigned D9     : 1;             /* D9 位 */
        unsigned D8     : 1;             /* D8 位 */

        unsigned D7     : 1;             /* D7 位 */
        unsigned D6     : 1;             /* D6 位 */
        unsigned D5     : 1;             /* D5 位 */
        unsigned D4     : 1;             /* D4 位 */
        unsigned D3     : 1;             /* D3 位 */
        unsigned D2     : 1;             /* D2 位 */
        unsigned D1     : 1;             /* D1 位 */
        unsigned D0     : 1;             /* D0 位 */

    }Bit1;

}USED_WORD;

typedef struct _DEBUG_
{
    unint32 ErrCode;
    unint32 ErrCnt;
} DEBUGXXX;

#endif // __IP_H__
