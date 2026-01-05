module;
export module ngterm;
import std;
import pty;
import tty;
import font;
import fb;
import types;

export void cleanup();
export void init();
export string welcome_str();
// TODO make async, e.g. init_slave() and fb.init() can happen at the same time
void init() {
  std::atexit(cleanup);
  init_freetype();
  fb.init("/dev/fb0");
  fb.load_font();
  init_slave("/bin/bash");
  init_tty();
}

void cleanup() {
  cleanup_tty();
  cleanup_freetype();
}

string welcome_str() {
  const string msg = "Welcome to ngTerm";
  return std::format("\n {:~^{}}\n\n", ' ' + msg + ' ', msg.size() * 3 - 2);
}
