module;
#include <pty.h>
#include <unistd.h>
#include <errno.h>
export module pty;
import std;
import types;

export void init_slave(string prog);

void init_slave(string program){
  int master_fd = -1;
  pid_t open_pty_ret =  forkpty(&master_fd,NULL,NULL,NULL);
  if(open_pty_ret < 0){
    // fatal error occured, exit
    std::print("Failed to fork pty (errno: {})",errno);
    std::exit(-1);
  } else if(open_pty_ret == 0){
    // We are the child process, exec shell
    string dash_i = "-i";
    array<char*,3> shell_args = {program.data(),dash_i.data(),NULL};
    execve(program.c_str(), shell_args.data(),NULL);

  }
}
