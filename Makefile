include $(GOROOT)/src/Make.inc

TARG=winservice

CGOFILES=winservice.go

CGO_OFILES=c-winservice.o

CLEANFILES+=winservice

include $(GOROOT)/src/Make.pkg
