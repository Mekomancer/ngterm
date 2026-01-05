module;
export module types;
import std;

export using std::string;
export using std::string_view;
export namespace fs = std::filesystem;
export template <typename T> using sptr = std::shared_ptr<T>;
export using std::vector;
export using std::array;
export using std::uint8_t;
export using std::uint16_t;
export using std::uint32_t;
export using std::uint64_t;
export using std::int8_t;
export using std::int16_t;
export using std::int32_t;
export using std::int64_t;
export using std::size_t;
export typedef std::ptrdiff_t ssize_t;
export template <typename V> struct matrix {
  size_t width;
  size_t height;
  void resize(size_t w, size_t h);
  V &operator[](size_t r, size_t c) { return data[c + r * width]; };

private:
  vector<V> data;
};

template <typename V> void matrix<V>::resize(size_t w, size_t h) {
  width = w;
  height = h;
  data.resize(w * h);
}
