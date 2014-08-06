CC:=clang
FFI_VERSION:=$(shell brew list libffi | head -1 | cut -d '/' -f 6)
FFI_FLAGS:=-I/usr/local/Cellar/libffi/${FFI_VERSION}/lib/libffi-${FFI_VERSION}/include -lffi
LIGHTNING_FLAGS:=-llightning
LIBJIT_FLAGS:=-Lprefix/lib/x86_64 -Iprefix/include -ljit
OBJECTS:=lightning1 lightning2 ffi1 ffi2 libjit1

.PHONY: clean

all: ${OBJECTS}

clean:
	rm -f ${OBJECTS}

lightning1: lightning1.c
	${CC} lightning1.c ${LIGHTNING_FLAGS} -o lightning1

lightning2: lightning2.c
	${CC} lightning2.c ${LIGHTNING_FLAGS} -o lightning2

ffi1: ffi1.c
	${CC} ffi1.c ${FFI_FLAGS} -o ffi1

ffi2: ffi2.c
	${CC} ffi2.c ${FFI_FLAGS} -o ffi2

libjit1: libjit1.c
	${CC} libjit1.c ${LIBJIT_FLAGS} -o libjit1
