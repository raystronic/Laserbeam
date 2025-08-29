CC = gcc
CFLAGS = -Wall -O2 -fPIC
LDFLAGS = -ldl

LAUNCHER = PeWpEwwww
MISSILES = $(patsubst modules/%.c,ammo/%.so,$(wildcard modules/*.c))

all: $(LAUNCHER) $(MISSILES)

$(LAUNCHER): shoot.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

ammo/%.so: modules/%.c
	@mkdir -p ammo
	$(CC) $(CFLAGS) -shared -o $@ $<

clean:
	rm -f $(LAUNCHER)
	rm -rf ammo