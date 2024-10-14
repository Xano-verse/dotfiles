.POSIX:

PREFIX = /usr/local
CC = gcc

wiredwmblocks: dwmblocks.o
	$(CC) dwmblocks.o -lX11 -o wiredwmblocks
dwmblocks.o: dwmblocks.c config.h
	$(CC) -c dwmblocks.c
clean:
	rm -f *.o *.gch wiredwmblocks
install: wiredwmblocks
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f wiredwmblocks $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/wiredwmblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/wiredwmblocks

.PHONY: clean install uninstall
