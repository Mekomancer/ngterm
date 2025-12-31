module;
export module ngterm;
import std;
import pty;
import tty;

export void cleanup();
export void init();

void init() {
  std::atexit(cleanup);
  init_slave("/bin/bash");
  init_tty();
}

void cleanup() { cleanup_tty(); }
