module;
#include <curses.h>
#include <fcntl.h>
#include <unistd.h>
export module tty;
import io;
import types;

export void init_tty();
export void cleanup_tty();

export class tty : public reader, public writer {
protected:
  ssize_t read_bytes(uint8_t *buffer, size_t num_bytes) override;
  ssize_t write_bytes(uint8_t *buffer, size_t num_bytes) override;
} ttyio;

ssize_t tty::read_bytes(uint8_t *buffer, size_t num_bytes) {
  return ::read(0, buffer, num_bytes);
}
ssize_t tty::write_bytes(uint8_t *buffer, size_t num_bytes) {
  return ::write(1, buffer, num_bytes);
}

void init_tty() {
  initscr();
  timeout(0);
  curs_set(0);
  raw();
  fcntl(0, F_SETFL, O_NONBLOCK);
}

void cleanup_tty() { endwin(); }
