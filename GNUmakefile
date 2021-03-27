CSTD=c99
WARN=-Wall -Wextra -Wno-unknown-pragmas
#USE_LINENOISE=yes

CFLAGS?=-g -O0 -pipe
CFLAGS+=-std=$(CSTD)
CFLAGS+=$(WARN)
CFLAGS2?=$(CFLAGS)
CFLAGS+=-Istlink/inc
CFLAGS+=-Istlink/build/Release/inc
CFLAGS+=-Istlink/src/stlink-lib
CFLAGS+=-D_XOPEN_SOURCE=500
CFLAGS+=$(shell pkg-config --cflags libusb-1.0)
LDFLAGS+=stlink/build/Release/lib/libstlink.a $(shell pkg-config --libs libusb-1.0)
ifdef USE_LINENOISE
CFLAGS+=-DUSE_LINENOISE
LDFLAGS+=-Llinenoise -l:linenoise.a 
endif

all: swd2

stlink/build/Release/lib/libstlink.a:
	[ -d stlink/.git ] || git submodule update --init
	make -C stlink

ifdef USE_LINENOISE
linenoise/linenoise.a: linenoise/linenoise.c linenoise/linenoise.h
	$(CC) $(CFLAGS2) -c -o linenoise/linenoise.o linenoise/linenoise.c
	ar ruv linenoise/linenoise.a linenoise/linenoise.o 
	ranlib linenoise/linenoise.a
endif

ifdef USE_LINENOISE
swd2: swd2.c stlink/build/Release/lib/libstlink.a linenoise/linenoise.a lineinput.c lineinput.h
	$(CC) $(CFLAGS) -o $@ swd2.c lineinput.c $(LDFLAGS)
else
swd2: swd2.c stlink/build/Release/lib/libstlink.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
endif
.PHONY: clean
clean:
	rm -f swd2
	make -C stlink clean
