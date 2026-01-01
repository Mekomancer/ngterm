module;
#include <fcntl.h>
#include <unistd.h>
export module io;
import types;

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

protected:
  virtual ssize_t write_bytes(uint8_t *buffer, size_t num_bytes) = 0;
};

void writer::write(auto data) {
  write_bytes(reinterpret_cast<uint8_t *>(&data), sizeof(decltype(data)));
};

export class file : public writer {
public:
  file(string pathname);

protected:
  ssize_t write_bytes(uint8_t *buffer, size_t num_bytes) override;

private:
  int fd;
};
ssize_t file::write_bytes(uint8_t *buffer, size_t num_bytes) {
  return ::write(fd, buffer, num_bytes);
};
file::file(string pathname) { fd = open(pathname.c_str(), O_RDWR | O_CREAT, 00666); }
