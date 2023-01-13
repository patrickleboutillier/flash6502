# https://cc65.github.io/doc/customizing.html


runtime:
	cp none.lib flash6502.lib
	ca65 --cpu 6502 crt0.s
	ca65 --cpu 6502 read.s
	ca65 --cpu 6502 write.s
	cc65 -t none -O -T --cpu 6502 flash6502.c
	ca65 --cpu 6502 flash6502.s
	ar65 d flash6502.lib crt0.o
	ar65 r flash6502.lib crt0.o read.o write.o flash6502.o 
	ca65 --cpu 6502 interrupt.s
	ca65 --cpu 6502 vectors.s

clean:
	rm -f *.o flash6502.lib


#$ cc65 -t none -O --cpu 6502 main.c
#$ ca65 --cpu 6502 main.s
#$ ca65 --cpu 6502 interrupt.s
#$ ca65 --cpu 6502 vectors.s
#$ ca65 --cpu 6502 wait.s
#$ ld65 -C sbc.cfg -m main.map interrupt.o vectors.o wait.o main.o sbc.lib
