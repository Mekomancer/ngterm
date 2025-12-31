module;
export module ngterm;
import std;
import pty;

export void init(){
  init_slave("/bin/bash");
}
