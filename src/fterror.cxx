module;
#undef FTERRORS_H_
const char *ft_error_str_(int errno) {
  switch (errno) {
#define FT_ERRORDEF_(e, v, s)                                                  \
  case v:                                                                      \
    return s;
#define FT_NOERRORDEF_(e, v, s)                                                \
  case v:                                                                      \
    return s;
#include <freetype/fterrdef.h>
  }
  return "Unknown error";
}
export module font:fterror;
import types;
import debug;
const char *ft_error_str(int errno) { return ft_error_str_(errno); }
void dbg_fterr(string_view func_name, int errno) {
  dbg.print("debug {} returned {}, {}\n", func_name, errno,
            ft_error_str(errno));
};
