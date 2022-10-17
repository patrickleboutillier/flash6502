build: fake6502.c
	g++ -g -O -I../circuit/src -I../circuit/complib -Ipl6502 fake6502.c -o fake6502


asm: 6502_functional_test.a65
	./6502_65C02_functional_tests/as65/as65 -l -m -w -h0 6502_functional_test.a65
	@grep ">.*;test passed, no errors" 6502_functional_test.lst | cut -d' ' -f1 > success.addr


test: asm build
	@date
	./fake6502 `cat success.addr`


clean:
	rm -f 6502_functional_test.bin 6502_functional_test.lst fake6502