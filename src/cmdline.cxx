module;
export module cmdline;
import std;

export void print_help(){
  std::print("USAGE: ngterm\n\n");
  std::print("Options:\n");
  std::print("-h, --help\tPrint help\n");
  std::print("-V, --version\tPrint version\n");
}

export void print_version(){
  std::print("ngTerm {}",VERSION);//VERSION is defined by cmake
}
