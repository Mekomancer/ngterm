module;
#include <fcntl.h>
#include <unistd.h>
export module io;
import types;
import std;
export class reader {
public:
  template <typename buf_t> buf_t readas();

protected:
  virtual ssize_t read_bytes(uint8_t *buffer, size_t num_bytes) = 0;
};

template <typename buf_t> buf_t reader::readas() {
  buf_t ret;
  read_bytes(reinterpret_cast<uint8_t *>(&ret), sizeof(buf_t));
  return ret;
}

export class writer {
public:
  void write(auto data);
  template <typename... Args>
  void print(std::format_string<Args...> fmt, Args &&...args);

protected:
  virtual ssize_t write_bytes(uint8_t *buffer, size_t num_bytes) = 0;
};

void writer::write(auto data) {
  write_bytes(reinterpret_cast<uint8_t *>(&data), sizeof(decltype(data)));
}

template <typename... Args>
void writer::print(std::format_string<Args...> fmt, Args &&...args) {
  string buf = std::format(fmt, std::forward<Args>(args)...);
  write_bytes(reinterpret_cast<uint8_t *>(buf.data()), buf.length());
}
export class file : public writer {
public:
  void create(fs::path path);
  void open(fs::path pathname);

protected:
  ssize_t write_bytes(uint8_t *buffer, size_t num_bytes) override;

private:
  int fd;
};

ssize_t file::write_bytes(uint8_t *buffer, size_t num_bytes) {
  return ::write(fd, buffer, num_bytes);
}
void file::open(fs::path pathname) {
  fd = ::open(pathname.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, 00666);
}
void file::create(fs::path pathname) { fd = ::creat(pathname.c_str(), 00666); }
