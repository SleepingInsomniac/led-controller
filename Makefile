# Name: Makefile
# Author: Alex Clink
# Copyright: Alex Clink 2021

SOURCES    = main.c
# OBJECTS    = $(SOURCES:.c=.o)
CC         = clang
TARGET     = leds_macos
CFLAGS     = -Wall -I/usr/local/Cellar/libftdi/1.5_2/include/libftdi1 -I/usr/local/Cellar/libusb/1.0.24/include/libusb-1.0
LDFLAGS    = -L/usr/local/Cellar/libftdi/1.5_2/lib -L/usr/local/Cellar/libusb/1.0.24/lib -lftdi1 -lusb-1.0

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)
