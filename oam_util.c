#include "oam_util.h"

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, int count)
{

// NOTE: while struct-copying is the Right Thing to do here, 
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
    while(count--)
        *dst++ = *src++;
#else
    u32 *dstw= (u32*)dst, *srcw= (u32*)src;
    while(count--)
    {
        *dstw++ = *srcw++;
        *dstw++ = *srcw++;
    }
#endif

}

void oam_init(OBJ_ATTR *obj, int count)
{
    u32 nn= (u32)count;
    u32 *dst= (u32*)obj;

    // Hide each object
    while(nn--)
    {
        *dst++= ATTR0_HIDE;
        *dst++= 0;
    }
    // init oam
    oam_copy(oam_mem, obj, count);
}

u32 se_index(u32 tx, u32 ty, u32 pitch)
{   
    u32 sbb= ((tx>>5)+(ty>>5)*(pitch>>5));
    return sbb*1024 + ((tx&31)+(ty&31)*32);
}