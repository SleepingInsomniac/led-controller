# Attempting to control ws2812b led strips using an FT232RL cable

- Install libftdi: `brew install libftdi`
- Get c flags and ld flags: `pkg-config --libs --cflags /usr/local/Cellar/libftdi/*/lib/pkgconfig/libftdi1.pc`
  (added to makefile)
