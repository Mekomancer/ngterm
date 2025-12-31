module;
export module cmdline;
import std;

export bool cmdline_quick_check(int argc, char *argv[]);

void print_help();
void print_version();

bool cmdline_quick_check(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-h") == 0 ||
        std::strcmp(argv[i], "--help") == 0) {
      print_help();
      return true;
    } else if (std::strcmp(argv[i], "-V") == 0 ||
               std::strcmp(argv[i], "--version") == 0) {
      print_version();
      return true;
    }
  }
  return false;
}

void print_help() {
  std::print("USAGE: ngterm\n\n");
  std::print("Options:\n");
  std::print("-h, --help\tPrint help\n");
  std::print("-V, --version\tPrint version\n");
}

void print_version() {
  std::print("ngTerm {}", VERSION); // VERSION is defined by cmake
}
