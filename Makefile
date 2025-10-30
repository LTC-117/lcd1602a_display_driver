.PHONY : all
all:
	./build.sh

.PHONY : clean
clean:
	rm -rf build/*

.PHONY : upload
upload:
	sudo st-flash write build/lcd1602a_display_driver.bin 0x8000000

# para debug: openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/lcd1602a_display_driver.elf verify reset exit"

.PHONY : reset
reset:
	sudo st-flash erase
