#define SRAM_BASE       0x20000000U
#define PERIPH_BASE     0x40000000U
 
#define SRAM_SIZE       40*1024 
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
 
#define RCC_BASE        (PERIPH_BASE + 0x21000)
#define RCC_AHBENR      (*(volatile unsigned long*)(RCC_BASE + 0x14))

#define GPIOE_BASE      (PERIPH_BASE + 0x00001000 + 0x08000000)
#define GPIOE_MODER     (*(volatile unsigned long*)(GPIOE_BASE + 0x00))
#define GPIOE_ODR       (*(volatile unsigned long*)(GPIOE_BASE + 0x14))

#define LED_PIN_MIN     8
#define LED_PIN_MAX     16

#define DELAY           50000

void sleep(volatile unsigned long sleep_time)
{
    while(sleep_time--);
}
 
int main()
{
    // Enable clock on GPIOE peripheral
    RCC_AHBENR = 1 << 21;

    // Put GPIOE pins into output mode
    for (int i = LED_PIN_MIN; i < LED_PIN_MAX; i++) {
	    GPIOE_MODER |= 0x01 << i * 2;
    }

    while(1)
    {
	    for (int i = LED_PIN_MIN; i < LED_PIN_MAX; i++) {
		    GPIOE_ODR = 1 << i; // set LED pin high
		    sleep(DELAY);
	    }
    }
}

unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)SRAM_END,   // place stack pointer at the end of SRAM 
                                 // (stack grows down)
    (unsigned long *)main        // reset handler, jump directly to main
};
