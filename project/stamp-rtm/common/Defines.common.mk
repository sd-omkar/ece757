# ==============================================================================
#
# Defines.common.mk
#
# ==============================================================================


CC       := gcc
#LIB1	 := /scratch/arindam/glibc-install/lib/libpthread.a
#LIB2	 := /scratch/arindam/glibc-install/lib/libc.a
#CFLAGS   += -g -Wall -static $(LIB1) $(LIB2)
CFLAGS   += -g -Wall 
CFLAGS   += -O3
CFLAGS   += -I$(LIB)
CPP      := g++
CPPFLAGS += $(CFLAGS)
LD       := g++
LIBS     += -lpthread

# Remove these files when doing clean
OUTPUT +=

LIB := ../lib

STM := ../../tl2

LOSTM := ../../OpenTM/lostm


# ==============================================================================
#
# End of Defines.common.mk
#
# ==============================================================================
