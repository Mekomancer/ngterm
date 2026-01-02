module;
export module display;
import std;
import types;
import font;

export template <typename pixel_t> class display {
public:
  void load_font();
  typedef pixel_t pixel;
  pixel &operator[](size_t r, size_t c);
  virtual pixel &at(size_t r, size_t c) = 0;
  virtual size_t height() = 0;
  virtual size_t width() = 0;
  virtual pixel to_pixel(uint8_t red, uint8_t blu, uint8_t grn) = 0;

protected:
  font_face font;
};

template <typename T> void display<T>::load_font() { font.load(); };

template <typename T> T &display<T>::operator[](size_t r, size_t c) {
  return at(r, c);
}
