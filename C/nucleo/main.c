#define SRAM_BASE       0x20000000U
#define PERIPH_BASE     0x40000000U
 
#define SRAM_SIZE       512*1024 
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
 
#define RCC_BASE        (PERIPH_BASE + 0x23800)
#define RCC_AHB1ENR      (*(volatile unsigned long*)(RCC_BASE + 0x30))

#define GPIOB_BASE      (PERIPH_BASE + 0x20400)
#define GPIOB_MODER     (*(volatile unsigned long*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOB_BASE + 0x14))

#define RED_LED_PIN     14
#define GREEN_LED_PIN   0
#define BLUE_LED_PIN    7

#define DELAY 1000000

void sleep(unsigned long sleep_time)
{
    while(sleep_time--);
}
 
int main()
{
    // Enable clock on GPIOB peripheral
    RCC_AHB1ENR = 1 << 1;

    // Put GPIOB0 into output mode
    GPIOB_MODER |= 0x01 << GREEN_LED_PIN * 2;
    // Put GPIOB7 into output mode
    GPIOB_MODER |= 0x01 << BLUE_LED_PIN * 2;
    // Put GPIOB14 into output mode
    GPIOB_MODER |= 0x01 << RED_LED_PIN * 2;

    while(1)
    {
        GPIOB_ODR = 1 << RED_LED_PIN; // set RED_LED pin high
        sleep(DELAY);
        GPIOB_ODR = 1 << BLUE_LED_PIN; // set BLUE_LED pin high
        sleep(DELAY);
        GPIOB_ODR = 1 << GREEN_LED_PIN; // set GREEN_LED pin high
        sleep(DELAY);

        GPIOB_ODR = 0 << RED_LED_PIN; // set RED_LED pin high
        sleep(DELAY);
        GPIOB_ODR = 0 << BLUE_LED_PIN; // set BLUE_LED pin high
        sleep(DELAY);
        GPIOB_ODR = 0 << GREEN_LED_PIN; // set GREEN_LED pin high
        sleep(DELAY);
    }
}

unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)SRAM_END,   // place stack pointer at the end of SRAM 
                                 // (stack grows down)
    (unsigned long *)main        // reset handler, jump directly to main
};
