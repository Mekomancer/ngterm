module;
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
export module fb;
import display;
import std;
import types;

export constexpr auto bitscale(auto val, int cur, int target) -> decltype(val) {
  return (((2 * val * ((1 << target) - 1)) / ((1 << cur) - 1)) + 1) / 2;
}
export class framebuffer : public display<uint16_t> {
public:
  void init(std::filesystem::path fb_device = "/dev/fb0");
  size_t height() override;
  size_t width() override;
  pixel to_pixel(uint8_t red, uint8_t blu, uint8_t grn) override;
  pixel &at(size_t r, size_t c) override;

private:
  fb_var_screeninfo vinfo;
  fb_fix_screeninfo finfo;
  pixel *addr = nullptr;
};
framebuffer::pixel &framebuffer::at(size_t r, size_t c) {
  return addr[r + (479 - c) * 320];
}
size_t framebuffer::height() { return static_cast<size_t>(vinfo.xres); }
size_t framebuffer::width() { return static_cast<size_t>(vinfo.yres); }
framebuffer::pixel framebuffer::to_pixel(uint8_t red, uint8_t blu,
                                         uint8_t grn) {
  return (bitscale<pixel>(red, 8, vinfo.red.length) << vinfo.red.offset) |
         (bitscale<pixel>(grn, 8, vinfo.green.length) << vinfo.green.offset) |
         (bitscale<pixel>(blu, 8, vinfo.blue.length) << vinfo.blue.offset);
}

void framebuffer::init(std::filesystem::path fb_dev) {
  int fd = open(fb_dev.c_str(), O_RDWR);
  ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
  ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
  addr = reinterpret_cast<pixel *>(
      mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  close(fd);
}
