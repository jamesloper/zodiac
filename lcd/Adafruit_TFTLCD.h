#include <../gfx/Adafruit_GFX.h>

class Adafruit_TFTLCD : public Adafruit_GFX {

public:
    Adafruit_TFTLCD();

    void begin(uint16_t id = 0x9325);

    void drawPixel(int16_t x, int16_t y, uint16_t color);

    void drawFastHLine(int16_t x0, int16_t y0, int16_t w, uint16_t color);

    void drawFastVLine(int16_t x0, int16_t y0, int16_t h, uint16_t color);

    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);

    void fillScreen(uint16_t color);

    void reset(void);

    void setRegisters8(uint8_t *ptr, uint8_t n);

    void setRegisters16(uint16_t *ptr, uint8_t n);

    void setRotation(uint8_t x);

    // These methods are public in order for BMP examples to work:
    void setAddrWindow(int x1, int y1, int x2, int y2);

    void pushColors(uint16_t *data, uint8_t len, bool first);

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b),
            readPixel(int16_t x, int16_t y), readID(void);

    uint32_t readReg(uint8_t r);

private:
    void init(),
    // These items may have previously been defined as macros
    // in pin_magic.h.  If not, function versions are declared:
#ifndef write8
            write8(uint8_t value),
#endif
#ifndef setWriteDir
            setWriteDir(void),
#endif
#ifndef setReadDir
            setReadDir(void),
#endif
#ifndef writeRegister8
            writeRegister8(uint8_t a, uint8_t d),
#endif
#ifndef writeRegister16
            writeRegister16(uint16_t a, uint16_t d),
#endif
            writeRegister24(uint8_t a, uint32_t d),
            writeRegister32(uint8_t a, uint32_t d),

#ifndef writeRegisterPair
            writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d),
#endif
            setLR(void), flood(uint16_t color, uint32_t len);

    uint8_t driver;

#ifndef read8

    uint8_t read8fn(void);

#define read8isFunctionalized
#endif
};
