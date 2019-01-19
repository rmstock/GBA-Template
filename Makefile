#
# sbb_reg.mak
#
# Shows how multiple screenblocks are used for larger sized
# regular backgrounds.
#
# NOTE: for educational purposes only. For real work, use
# devkitPro's templates ( $(DEVKITPRO)/examples/gba/template )
# or tonclib's templates ( $(TONCCODE)/lab/template )

PATH := $(DEVKITARM)/bin:$(PATH)
PATH := $(DEVKITPRO)/tools/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := sbb_reg
TITLE   := $(PROJ)
#things with c files.
COBJS   := $(PROJ).o toolbox.o tiles.o palette.o tonc_irq.o background.o display.o sprite.o panic.o explore.o option.o sprites.o movement.o mode.o oam_util.o
#things with c or s files.
OBJS	:= $(COBJS) tonc_memcpy.o tonc_bios.o tonc_memset.o tonc_isr_master.o

IMGS    := white.bmp green_single.bmp purple_left.bmp purple_right.bmp

SPRT    := ball.bmp
# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)

TARGET	:= $(PROJ).mb
SPECS	:= -specs=gba_mb.specs

else

TARGET	:= $(PROJ)
SPECS	:= -specs=gba.specs

endif

# --- Compiling -------------------------------------------------------

CROSS	?= arm-none-eabi-
AS		:= $(CROSS)gcc
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy


ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork -x assembler-with-cpp
CFLAGS	:= $(ARCH) -O2 -Wall -Werror -Wunused -Wconversion -fno-strict-aliasing
LDFLAGS	:= $(ARCH) $(SPECS)

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba image_converter.exe tiles.c


$(TARGET).gba : $(TARGET).elf 
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

tonc_memcpy.o: tonc_memcpy.S
	$(AS) $(ASFLAGS) $< -c -o $@
	
tonc_bios.o: tonc_bios.S
	$(AS) $(ASFLAGS) $< -c -o $@
	
tonc_memset.o: tonc_memset.S
	$(AS) $(ASFLAGS) $< -c -o $@

tonc_isr_master.o: tonc_isr_master.S
	$(AS) $(ASFLAGS) $< -c -o $@

$(COBJS) : %.o : %.c tiles.c sprites.c
	$(CC) $(CFLAGS) -c $< -o $@

tiles.c : my.pal image_converter.exe
	./image_converter.exe tiles 0 my.pal $(IMGS)
	
sprites.c : my.pal image_converter.exe
	./image_converter.exe sprites 0 my.pal $(SPRT)
	
image_converter.exe : my.pal 
	gcc -ggdb image_converter.c bmpread.c -lm -o image_converter.exe

my.pal : palette.exe
	./palette.exe

palette.exe : palette_gen.c
	gcc -ggdb palette_gen.c -o palette.exe


# --- Clean -----------------------------------------------------------

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o
	@rm -fv tiles.*
	@rm -fv sprites.c
	@rm -fv sprites.h
	@rm -fv my.pal
	@rm -fv *.exe

#EOF
