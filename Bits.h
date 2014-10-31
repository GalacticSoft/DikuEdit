#ifndef _BITS_H_
#define _BITS_H_ 1

struct BITVECT_DATA
{
    int group;
    int vector;
};

#define		BVNO			(0)			/*			0 */
#define		BV00			(1 <<  0)	/*          1 */
#define		BV01			(1 <<  1)	/*          2 */
#define		BV02			(1 <<  2)	/*          4 */
#define		BV03			(1 <<  3)	/*          8 */
#define		BV04			(1 <<  4)	/*         16 */
#define		BV05			(1 <<  5)	/*         32 */
#define		BV06			(1 <<  6)	/*         64 */
#define		BV07			(1 <<  7)	/*        128 */
#define		BV08			(1 <<  8)	/*        256 */
#define		BV09			(1 <<  9)	/*        512 */
#define		BV10			(1 << 10)	/*       1024 */
#define		BV11			(1 << 11)	/*       2048 */
#define		BV12			(1 << 12)	/*       4096 */
#define		BV13			(1 << 13)	/*       8192 */
#define		BV14			(1 << 14)	/*      16384 */
#define		BV15			(1 << 15)	/*      32768 */
#define		BV16			(1 << 16)	/*      65536 */
#define		BV17			(1 << 17)	/*     131072 */
#define		BV18			(1 << 18)	/*     262144 */
#define		BV19			(1 << 19)	/*     524288 */
#define		BV20			(1 << 20)	/*    1048576 */
#define		BV21			(1 << 21)	/*    2097152 */
#define		BV22			(1 << 22)	/*    4194304 */
#define		BV23			(1 << 23)	/*    8388608 */
#define		BV24			(1 << 24)	/*   16777216 */
#define		BV25			(1 << 25)	/*   33554432 */
#define		BV26			(1 << 26)	/*   67108864 */
#define		BV27			(1 << 27)	/*  134217728 */
#define		BV28			(1 << 28)	/*  268435456 */
#define		BV29			(1 << 29)	/*  536870912 */
#define		BV30			(1 << 30)	/* 1073741824 */
#define		BV31			(1 << 31)	/* dont use unless unsigned! */

#define IS_SET(flag, bit) (flag & bit)
#define REMOVE_BIT(flag, bit) (flag &= ~bit)
#define SET_BIT(flag, bit) (flag |= bit)

class bit
{
public:
	char *name;
	int val;
};

int GetBitCount();

extern const bit bits[];
#endif