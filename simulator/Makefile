build: fake6502.c
	g++ -Wall -g -O -I circuit/src -I circuit/complib -I pl6502/src fake6502.c -o fake6502


asm: 6502_functional_test.bin

6502_functional_test.bin: 6502_functional_test.a65
	./6502_65C02_functional_tests/as65/as65 -l -m -w -h0 6502_functional_test.a65
	./bin2prog.pl 6502_functional_test.bin > 6502_functional_test.c
	@grep ">.*;test passed, no errors" 6502_functional_test.lst | cut -d' ' -f1 > success.addr
	echo "Succes address is 0x`cat success.addr`"


test: asm build
	@date
	./fake6502 `cat success.addr`

microcode: microcode.c
	g++ -Wall -g -O -I circuit/src -I circuit/complib -I pl6502/src microcode.c -o microcode
	./microcode > /tmp/mimcrocode.h && cp -f /tmp/microcode.h .

clean:
	rm -f 6502_functional_test.bin 6502_functional_test.lst fake6502 success.addr