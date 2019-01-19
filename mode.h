#ifndef MODE_H
#define MODE_H

#define MODE_NONE 0
#define MODE_OPTION 1
#define MODE_EXPLORE 2
#define MODE_BUILD 3
#define MODE_SELECT 4

typedef void (*fptr)();

extern int mode_current;
extern fptr mode_tick;

//void mode_init();
void mode_set(int mode);
//void mode_tick();
//void mode_get();
void mode_save();

#endif