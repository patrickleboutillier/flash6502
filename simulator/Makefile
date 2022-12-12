build: fake6502

fake6502: fake6502.c *.h
	g++ -Wall -g -O -I circuit/src -I circuit/complib -I pl6502/src fake6502.c -o fake6502

test: build 
	@./fake6502 testsuite

star: build
	@./fake6502 star

mc: microcode
microcode: microcode.c addrmodes.h ops.h
	g++ -Wall -g -O -I circuit/src -I circuit/complib -I pl6502/src microcode.c -o microcode
	./microcode > /tmp/mimcrocode.h && cp -f /tmp/microcode.h .

clean:
	rm -f fake6502 microcode