#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hyper.pio.h"
#include <cstdio>
#include "lcd/pin_magic.h"
#include "lcd/Adafruit_TFTLCD.h"
#include "hyper/hyper.h"

void waitForDebug() {
    while (true) {
        if (stdio_usb_connected()) {
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            sleep_ms(1000);
            return;
        } else {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
        }
    }
}

int main() {
    set_sys_clock_48mhz();
    stdio_init_all();

    Adafruit_TFTLCD tft;
    char ch;
    int input;

    // Initialize HyperRam
    PIO pio = pio0;
    uint sm = pio_claim_unused_sm(pio, true); // state machine
    clock_gpio_init(HYPER_CLK_PIN, clk_sys, 2);
    uint offset = pio_add_program(pio, &hyper_program);
    hyper_program_init(pio, sm, offset, HYPER_DATA_PIN, 1);
    pio_sm_set_enabled(pio, sm, true);

    // LED STUFF
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Connect to USB
    waitForDebug();
    printf("Connected, initializing display\n");

    // Initialize display
    tft.reset();
    uint16_t identifier = tft.readID();

    if (identifier != 0x8357) {
        printf("Error: unknown lcd: %i\n", identifier);
        return 0;
    }

    tft.begin(0x8357);

    printf("Screen is ready!\n");

    tft.fillScreen(BLUE);
    tft.fillRect(10, 10, 100, 100, GREEN);
    tft.drawLine(0, 0, 480, 320, RED);
    tft.drawCircle(160, 160, 30, MAGENTA);
    tft.drawChar(0, 0, 'R', RED, BLACK, 2);
    tft.drawChar(0, 16, 'G', GREEN, BLACK, 2);
    tft.drawChar(0, 32, 'B', BLUE, BLACK, 2);


//    tft.setCursor(0, 0);
//    tft.setTextColor(WHITE);  tft.setTextSize(1);
//    tft.println("Hello World!");
//    tft.setTextColor(YELLOW); tft.setTextSize(2);
//    tft.println(1234.56);
//    tft.setTextColor(RED);    tft.setTextSize(3);
//    tft.println(0xDEADBEEF, HEX);
//    tft.println();
//    tft.setTextColor(GREEN);
//    tft.setTextSize(5);
//    tft.println("Groop");
//    tft.setTextSize(2);
//    tft.println("I implore thee,");
//    tft.setTextSize(1);
//    tft.println("my foonting turlingdromes.");
//    tft.println("And hooptiously drangle me");
//    tft.println("with crinkly bindlewurdles,");
//    tft.println("Or I will rend thee");
//    tft.println("in the gobberwarts");
//    tft.println("with my blurglecruncheon,");
//    tft.println("see if I don't!");
    return 1;
}