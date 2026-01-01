import ngterm;
import std;
import cmdline;
import io;
import types;
import tty;
int main(int argc, char *argv[]) {
  if (cmdline_quick_check(argc, argv) == 1) {
    return 0;
  }
  init();
  file log("./log");
  while (true) {
    uint8_t buf = ttyio.readas<uint8_t>();
    ttyio.write(buf);
    log.write(buf);
  }
  cleanup();
  return 0;
}
