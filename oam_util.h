#ifndef OAM_UTIL_H
#define OAM_UTIL_H

#include "toolbox.h"

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, int count);

void oam_init(OBJ_ATTR *obj, int count);

u32 se_index(u32 tx, u32 ty, u32 pitch);

#endif
