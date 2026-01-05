module;
#include <freetype/freetype.h>
export module font;
import types;
import std;
import debug;
import :fterror;
static FT_Library freetype = nullptr;

export void init_freetype() {
  dbg_fterr("FT_Init_FreeType", FT_Init_FreeType(&freetype));
}

export void cleanup_freetype() {
  if (freetype != nullptr) {
    FT_Done_FreeType(freetype);
    freetype = nullptr;
  }
}
export class font_face {
public:
  void load();
  matrix<uint8_t> get_glyph(uint32_t index);

private:
  std::map<uint32_t, unsigned int> charmap; // some caching
  std::map<uint32_t, matrix<uint8_t>> glyphs;
  FT_Face handle;
};

void font_face::load() {
  dbg_fterr("FT_New_Face", FT_New_Face(freetype, FONT_FILE, 0, &handle));
  FT_Size_RequestRec req_size{FT_SIZE_REQUEST_TYPE_CELL, (1 << 6) * 480 / 80, 0,
                              0, 0};
  dbg_fterr("FT_Request_Size", FT_Request_Size(handle, &req_size));
  for (uint32_t i = 32; i < 127; ++i) { // cache ascii
    unsigned int res = FT_Get_Char_Index(handle, i);
    if (res != 0) {
      charmap[i] = res;
      get_glyph(i);
    } else {
      dbg.print("warn Character code '{}' is not defined in charmap", res);
    }
  }
}

matrix<uint8_t> font_face::get_glyph(uint32_t code) {
  if (glyphs.contains(code)) {
    return glyphs[code];
  }
  dbg_fterr("FT_Load_Glyph", FT_Load_Glyph(handle, charmap[code], FT_LOAD_RENDER));
  FT_Bitmap *bmap = &(handle->glyph->bitmap);
  glyphs[code].resize(bmap->width,bmap->rows);
  unsigned char *cur = bmap->buffer;
  for(unsigned int row = 0; row < bmap->rows; ++row){
    for(unsigned int col = 0; col < bmap->width; ++col){
      glyphs[code][row,col] = cur[col];
    }
    cur += bmap->pitch;
  }
  return glyphs[code];
}
