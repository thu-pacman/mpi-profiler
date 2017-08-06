CC = mpiicc
OPT= 
CFLAGS = -O2
DEF= -DPERF_PROFILE 
# -DMPI_TIME
AR = ar
ARTAG = rcv

libmpit	: profile.o timer.o mpiwrapper.o mpiwrapper_f.o
	$(AR) $(ARTAG) libmpit.a mpiwrapper.o mpiwrapper_f.o timer.o profile.o
	$(RM) -f *.o
profile.o : profile.c	
	$(CC) $(CFLAGS) $(DEF) -c profile.c
mpiwrapper.o: mpiwrapper.c
	$(CC) $(CFLAGS) $(DEF) -c mpiwrapper.c
mpiwrapper_f.o: mpiwrapper_f.c
	$(CC) $(CFLAGS) $(DEF) -c mpiwrapper_f.c 
timer.o : timer.c	
	$(CC) $(CFLAGS) -c timer.c
clean :
	rm -f *.o	rm -f libmpit.a
