hello.bin: hello.s
	vasm -Fbin -dotdir -o hello.bin hello.s
	perl ../bin2prog.pl hello.bin > hello.prog

clean:
	rm -f fake6502 hello.bin
