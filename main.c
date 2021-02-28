#include <stdio.h>
#include <stdlib.h>
#include <ftdi.h>
#include <unistd.h>

#define LED_PIN 0x01 // 0x01 = TX

int main(void) {
  unsigned char c = 0x00;

  int ret;
  struct ftdi_context *ftdi;
  struct ftdi_version_info version;

  if ((ftdi = ftdi_new()) == 0) {
    fprintf(stderr, "ftdi_new failed\n");
    return EXIT_FAILURE;
  }

  version = ftdi_get_library_version();

  printf("Initialized libftdi %s (major: %d, minor: %d, micro: %d, snapshot ver: %s)\n",
    version.version_str,
    version.major,
    version.minor,
    version.micro,
    version.snapshot_str
  );

  if (ftdi_usb_open(ftdi, 0x0403, 0x6001) < 0) {
    fprintf(stderr, "Failed to open FTDI device: %s", ftdi_get_error_string(ftdi));
    return EXIT_FAILURE;
  }

  unsigned int chipid;
  printf("ftdi_read_chipid: %d\n", ftdi_read_chipid(ftdi, &chipid));
  printf("FTDI chipid: %X\n", chipid);

  if (ftdi_set_bitmode(ftdi, 0xff, BITMODE_BITBANG) < 0) {
    fprintf(stderr, "Failed to set bitbang mode: %s", ftdi_get_error_string(ftdi));
    return EXIT_FAILURE;
  }

  for(;;) {
    c ^= LED_PIN;
    fprintf(stdout, "Sending... 0x%02X\n", c);
    int s = ftdi_write_data(ftdi, &c, 1);
    fprintf(stdout, "Bytes: %d", s);
    sleep(1);
  }

  if ((ret = ftdi_usb_close(ftdi)) < 0) {
    fprintf(stderr, "unable to close ftdi device: %d (%s)\n", ret, ftdi_get_error_string(ftdi));
    ftdi_free(ftdi);
    return EXIT_FAILURE;
  }

  ftdi_free(ftdi);

  return EXIT_SUCCESS;
}
