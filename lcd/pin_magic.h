#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define DATA_PINS 0b00000000000000000000000011111111
#define CONTROL_PINS 0b00000000000000000000111100000000
#define csPort 8
#define cdPort 9
#define wrPort 10
#define rdPort 11

#define write8inline(d) { \
    gpio_put_masked(DATA_PINS, d); \
    WR_STROBE; \
}

#define read8inline(result) { \
    RD_ACTIVE; \
    sleep_us(500); \
    result = gpio_get_all() & DATA_PINS; \
    RD_IDLE; \
}

#define setWriteDirInline() { \
    gpio_set_dir_out_masked(DATA_PINS); \
}

#define setReadDirInline() { \
    gpio_set_dir_in_masked(DATA_PINS); \
}

#define write8 write8inline
#define read8 read8inline
#define setWriteDir setWriteDirInline
#define setReadDir setReadDirInline
#define writeRegister8 writeRegister8inline
#define writeRegister16 writeRegister16inline
#define writeRegisterPair writeRegisterPairInline

// Control pins are configurable
#define RD_ACTIVE gpio_put(rdPort, 0)
#define RD_IDLE gpio_put(rdPort, 1)
#define WR_ACTIVE gpio_put(wrPort, 0)
#define WR_IDLE gpio_put(wrPort, 1)
#define CD_COMMAND gpio_put(cdPort, 0)
#define CD_DATA gpio_put(cdPort, 1)
#define CS_ACTIVE gpio_put(csPort, 0)
#define CS_IDLE gpio_put(csPort, 1)

// Quickly flashes wrPort low then high
#define WR_STROBE { \
    WR_ACTIVE; \
    sleep_us(10); \
    WR_IDLE; \
}

// Set value of TFT register: 8-bit address, 8-bit value
#define writeRegister8inline(a, d) { \
    CD_COMMAND; \
    write8(a); \
    CD_DATA; \
    write8(d); \
}

// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars
#define writeRegister16inline(a, d) { \
    uint8_t hi, lo; \
    hi = (a) >> 8; \
    lo = (a); \
    CD_COMMAND; \
    write8(hi); \
    write8(lo); \
    hi = (d) >> 8; \
    lo = (d); \
    CD_DATA; \
    write8(hi); \
    write8(lo); \
}

// Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
#define writeRegisterPairInline(aH, aL, d) { \
    uint8_t hi = (d) >> 8, lo = (d); \
    CD_COMMAND; \
    write8(aH); \
    CD_DATA; \
    write8(hi); \
    CD_COMMAND; \
    write8(aL); \
    CD_DATA; \
    write8(lo); \
}


#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
