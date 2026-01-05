import ngterm;
import std;
import cmdline;
import io;
import types;
import fb;
import debug;
import tty;
import consts;

int main(int argc, char *argv[]) {
  if (cmdline_quick_check(argc, argv) == 1) {
    return 0;
  }
  init();
  dbg.print("{:}", welcome_str());
  while (true) {
    char buf = ttyio.readas<char>();
    if (buf != 0) {
      dbg.log("got char {:?}\n", buf);
    }
    if (buf == CTRL_C) {
      break;
    }
  }
  cleanup();
  return 0;
}
