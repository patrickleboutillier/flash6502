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
