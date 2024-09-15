#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#define CURSOR_SIZE 5
#define CURSOR_COLOR 0x00FFFFFF

int main(int argc, char **argv) {
  int fb, mouse;
  struct fb_var_screeninfo fb_info;
  uint32_t *fb_buf;
  int x, y, i, j;
  uint8_t mouse_ev[3];
  uint32_t behind_cursor[CURSOR_SIZE * CURSOR_SIZE];

  if (argc != 3) {
    fprintf(stderr, "usage: %s /dev/fbX /dev/input/mouseX\n", argv[0]);
    return 1;
  }

  fb = open(argv[1], O_RDWR);
  if (fb < 0) {
    perror(argv[1]);
    return 1;
  }

  if (ioctl(fb, FBIOGET_VSCREENINFO, &fb_info) < 0) {
    perror("iotctl(FBIOGET_VSCREENINFO)");
    return 1;
  }

  fb_buf = mmap(NULL, fb_info.xres * fb_info.yres * sizeof(uint32_t),
                PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
  if (fb_buf == MAP_FAILED) {
    perror("mmap()");
    return 1;
  }

  mouse = open(argv[2], O_RDONLY);
  if (mouse < 0) {
    perror(argv[2]);
    return 1;
  }

  x = 0;
  y = 0;
  for (i = 0; i < CURSOR_SIZE; i++) {
    for (j = 0; j < CURSOR_SIZE; j++) {
      if (x + i >= (int)fb_info.xres)
        continue;
      if (y + j >= (int)fb_info.yres)
        continue;
      behind_cursor[j * CURSOR_SIZE + i] =
          fb_buf[(y + j) * fb_info.xres + (x + i)];
      fb_buf[(y + j) * fb_info.xres + (x + i)] = CURSOR_COLOR;
    }
  }

  while (read(mouse, &mouse_ev, 3) == 3) {
    if (mouse_ev[1] == 0 && mouse_ev[2] == 0)
      continue;

    for (i = 0; i < CURSOR_SIZE; i++) {
      for (j = 0; j < CURSOR_SIZE; j++) {
        if (x + i >= (int)fb_info.xres)
          continue;
        if (y + j >= (int)fb_info.yres)
          continue;
        fb_buf[(y + j) * fb_info.xres + (x + i)] =
            behind_cursor[j * CURSOR_SIZE + i];
      }
    }

    x += (int8_t)mouse_ev[1];
    y -= (int8_t)mouse_ev[2];

    if (x < 0)
      x = 0;
    if (x >= (int)fb_info.xres)
      x = fb_info.xres - 1;
    if (y < 0)
      y = 0;
    if (y >= (int)fb_info.yres)
      y = fb_info.yres - 1;

    for (i = 0; i < CURSOR_SIZE; i++) {
      for (j = 0; j < CURSOR_SIZE; j++) {
        if (x + i >= (int)fb_info.xres)
          continue;
        if (y + j >= (int)fb_info.yres)
          continue;
        behind_cursor[j * CURSOR_SIZE + i] =
            fb_buf[(y + j) * fb_info.xres + (x + i)];
        fb_buf[(y + j) * fb_info.xres + (x + i)] = CURSOR_COLOR;
      }
    }
  }
  perror("read()");
  return 1;
}
