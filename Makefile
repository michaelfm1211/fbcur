PREFIX ?= /usr/local

CFLAGS += -Wall -Wextra -Werror -pedantic

.PHONY: all
all: fbcur fbcur_ev

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

fbcur: fbcur.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

fbcur_ev: fbcur_ev.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

.PHONY: install
install: all
	install -Dm 755 fbcur $(PREFIX)/bin/fbcur
	install -Dm 755 fbcur_ev $(PREFIX)/bin/fbcur_ev

.PHONY: clean
clean:
	rm -rf fbcur fbcur_ev *.o
