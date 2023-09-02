LINKER_SCRIPT = linker_script.ld
C_FLAGS  = -c -O2 -mcpu=cortex-m3 -mthumb
OPENOCD_FLAGS = -f interface/stlink.cfg -f target/stm32f3x.cfg
 
all: main.elf
 
%.o: %.c
	arm-none-eabi-gcc $(C_FLAGS) -o $@ $<

main.elf: main.o
	arm-none-eabi-ld -T$(LINKER_SCRIPT) -o main.elf main.o

clean:
	rm -rf *.o *.elf

flash: main.elf
	openocd $(OPENOCD_FLAGS) -c "program main.elf reset" -c "shutdown"
