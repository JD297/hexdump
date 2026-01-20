.POSIX:

CC            = cc
CFLAGS        = -std=c89 -Wall -Wextra -Wpedantic -g -I src
LDFLAGS       = 

TARGET        = hexdump
PREFIX        = /usr/local
BINDIR        = $(PREFIX)/bin
MANDIR        = $(PREFIX)/share/man
SRCDIR        = src
BUILDDIR      = build

$(BUILDDIR)/$(TARGET): $(SRCDIR)/hexdump.c
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/hexdump.c $(LDFLAGS)

clean:
	rm -f $(BUILDDIR)/*

install: $(BUILDDIR)/$(TARGET)
	cp $(BUILDDIR)/$(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
