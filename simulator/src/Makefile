.PHONY: build
build: microcode fake6502 

fake6502: fake6502.c *.h
	g++ -Wall -g -O -I ../circuit/src -I ../circuit/complib -I ../pl6502/src fake6502.c -o fake6502

.PHONY: mc
mc: microcode

microcode: microcode.c addrmodes.h ops.h ../pl6502/src/CONTROL_ROMS.h
	g++ -Wall -g -O -I ../circuit/src -I ../circuit/complib -I ../pl6502/src microcode.c -o microcode
	./microcode > /tmp/microcode.h && cp -f /tmp/microcode.h .

.PHONY: clean
clean:
	rm -f fake6502 microcode


FLASH=SST39SF020A
flash_CTRL1:
	minipro -p $(FLASH) -w CONTROL_1_ROM.bin

flash_CTRL2:
	minipro -p $(FLASH) -w CONTROL_2_ROM.bin

flash_CTRL3:
	minipro -p $(FLASH) -w CONTROL_3_ROM.bin

flash_CTRL4:
	minipro -p $(FLASH) -w CONTROL_4_ROM.bin

flash_CTRL5:
	minipro -p $(FLASH) -w CONTROL_5_ROM.bin
	