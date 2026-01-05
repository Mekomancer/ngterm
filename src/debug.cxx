module;
export module debug;
import io;
import std;
class debug_log : public file {
public:
  template <typename... Args>
  void log(std::format_string<Args...> fmt, Args &&...args);
  debug_log();
};

template <typename... Args>
void debug_log::log(std::format_string<Args...> fmt, Args &&...args) {
  print(fmt, std::forward<Args>(args)...);
}
debug_log::debug_log() { create("./log"); }
export debug_log dbg;
