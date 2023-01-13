CFG=../../flash6502.cfg
RUNTIME=../../flash6502.lib
OBJECTS=../../interrupt.o ../../vectors.o

PROG=collatz

build:
	cc65 -t none -O -T --cpu 6502 $(PROG).c
	ca65 --cpu 6502 $(PROG).s
	ld65 -C $(CFG) -m $(PROG).map $(PROG).o $(OBJECTS) $(RUNTIME)

test: build
	cd ../../../simulator/ && src/fake6502 ../cc65/programs/$(PROG)/a.out

clean:
	rm -f *.o *.map
