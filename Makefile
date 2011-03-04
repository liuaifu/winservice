include ../../../src/Make.inc

TARG=winservice

CGOFILES=winservice.go

CGO_OFILES=c-winservice.o

CLEANFILES+=winservice

include ../../../src/Make.pkg

test: install test.go
	$(GC) test.go
	$(LD) -o $@.exe test.$O
