import ngterm;
import std;
import cmdline;
import io;
import types;
import tty;
import fb;
import debug;

int main(int argc, char *argv[]) {
  if (cmdline_quick_check(argc, argv) == 1) {
    return 0;
  }
  init();
  framebuffer fb;
  dbg.print("^._.^\n");
  fb.init("/dev/fb0");
  fb.load_font();
  while (true) {
    char buf = ttyio.readas<char>();
    if(buf != 0){
      dbg.log("read char {:?}\n", buf);
    }
    if (buf == 3) { // ctrl-c
      break;
    }
  }
  cleanup();
  return 0;
}
