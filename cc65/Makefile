# https://cc65.github.io/doc/customizing.html

lib:
	cp supervision.lib flash6502.lib
	ca65 crt0.s
	ar65 d flash6502.lib crt0.o supervision-stdjoy-joy.o joy_stat_stddrv.o libref.o
	ar65 a flash6502.lib crt0.o

clean:
	rm -f *.o flash6502.lib


#$ cc65 -t none -O --cpu 65sc02 main.c
#$ ca65 --cpu 65sc02 main.s
#$ ca65 --cpu 65sc02 rs232_tx.s
#$ ca65 --cpu 65sc02 interrupt.s
#$ ca65 --cpu 65sc02 vectors.s
#$ ca65 --cpu 65sc02 wait.s
#$ ld65 -C sbc.cfg -m main.map interrupt.o vectors.o wait.o rs232_tx.o main.o sbc.lib