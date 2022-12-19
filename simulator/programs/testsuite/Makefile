6502_functional_test.bin: 6502_functional_test.a65
	./6502_65C02_functional_tests/as65/as65 -l -m -w -h0 6502_functional_test.a65
	../bin2prog.pl 6502_functional_test.bin > 6502_functional_test.c
	@echo "IRQ trap (int_addr) is 0x`grep -P ':\s+irq_trap' 6502_functional_test.lst | cut -d' ' -f1`"
	@echo "NMI trap (nmi_addr) is 0x`grep -P ':\s+nmi_trap' 6502_functional_test.lst | cut -d' ' -f1`"
	@echo "Success address (done_addr) is 0x`grep '>.*;test passed, no errors' 6502_functional_test.lst | cut -d' ' -f1`"

clean:
	rm -f 6502_functional_test.bin 6502_functional_test.lst 6502_functional_test.c 
