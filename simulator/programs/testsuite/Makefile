6502_functional_test.bin: 6502_functional_test.a65
	./6502_65C02_functional_tests/as65/as65 -l -m -w -h0 6502_functional_test.a65
	../bin2prog.pl 6502_functional_test.bin > 6502_functional_test.c
	@echo "Succes address is 0x`grep '>.*;test passed, no errors' 6502_functional_test.lst | cut -d' ' -f1`"

clean:
	rm -f 6502_functional_test.bin 6502_functional_test.lst 6502_functional_test.c 
