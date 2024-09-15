CFLAGS = -Wall -Wextra -Werror -pedantic

.PHONY: all
all: fbcur

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ %<

fbcur: fbcur.o
	$(CC) $(CFLAGS) -o $@ $<

fbcur_ev: fbcur_ev.o
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf fbcur fbcur_ev *.o
