module;
#include <freetype/freetype.h>
export module font;
import types;
import std;

static FT_Library freetype = nullptr;

export void init_freetype() { FT_Init_FreeType(&freetype); }

export void cleanup_freetype() {
  if (freetype != nullptr) {
    FT_Done_FreeType(freetype);
    freetype = nullptr;
  }
}
export class font_face {
public:
  void load();

private:
  FT_Face handle;
};
void font_face::load() {
  FT_New_Face(freetype, "/home/mark/ngterm/font/NotoSansMono.ttf", 0, &handle);
}
