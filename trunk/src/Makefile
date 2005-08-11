CFLAGS=-g `gtk-config --cflags` -I/usr/include/gtkextra
LDFLAGS=`gtk-config --libs` -lgtkextra -lbluetooth

a: clean all

all: btmanager btscan

clean:
	-rm -f *.o btmanager btscan

btmanager: btmanager.o btlib.o

btscan: btscan.o btlib.o
	cc $(CFLAGS) $(LDFLAGS) -o btscan btscan.o btlib.o

sdpb:
	cc $(CFLAGS) $(LDFLAGS) -o sdpbrowse sdpbrowse.c
	
.PHONY: all clean
