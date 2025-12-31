module;
export module display;
import std;
import types;

export template<typename pixel> class display{
  public:
    virtual pixel& operator[](int r, int c) = 0;
    virtual pixel& at(int r, int c) = 0;
    virtual pixel to_pixel(uint8_t red, uint8_t blu, uint8_t grn);
    virtual init() = 0;
};

class framebuffer: public display<{
    
};
