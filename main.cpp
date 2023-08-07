#include "pico/stdlib.h"

/* This rewrite from Python has, as of 23/08/07, not been tested on bare metal.
If you try this and it works, please let me know! */



const uint LED_PIN = 14;       // Relay pin
const uint HALL_EFFECT_PIN = 15; // Hall effect sensor pin

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_init(HALL_EFFECT_PIN);

    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(HALL_EFFECT_PIN, GPIO_IN);

    bool isWaterFlowing = false;
    bool wasWaterFlowing = false;

    while (true) {
        isWaterFlowing = gpio_get(HALL_EFFECT_PIN);

        // Check if water flow status has changed
        if (isWaterFlowing != wasWaterFlowing) {
            if (isWaterFlowing) {
                gpio_put(LED_PIN, 1); // Activate relay
                printf("Water is flowing.\n");
            } else {
                gpio_put(LED_PIN, 0); // Deactivate relay
                printf("Water flow stopped.\n");
            }
            wasWaterFlowing = isWaterFlowing;
        }
    }

    return 0;
}

