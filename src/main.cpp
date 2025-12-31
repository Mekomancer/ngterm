import ngterm;
import std;
import cmdline;
int main(int argc, char* argv[]){
  for(int i = 1; i < argc; ++i){
    if(std::strcmp(argv[i],"-h")==0 || std::strcmp(argv[i],"--help")==0){
      print_help();
    } else if(std::strcmp(argv[i],"-V")==0||std::strcmp(argv[i],"--version")==0){
      print_version();
    }
  }
  return 0;
}
