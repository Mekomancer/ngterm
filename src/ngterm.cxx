module;
export module ngterm;
import std;
import pty;
import tty;
import font;

export void cleanup();
export void init();

void init() {
  std::atexit(cleanup);
  init_slave("/bin/bash");
  init_tty();
  init_freetype();
}

void cleanup() {
  cleanup_tty();
  cleanup_freetype();
}
