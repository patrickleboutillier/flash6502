CFG=../../flash6502.cfg
RUNTIME=../../flash6502.lib
OBJECTS=../../interrupt.o ../../vectors.o


build:
	cc65 -t none -O -T --cpu 6502 hello.c
	ca65 --cpu 6502 hello.s
	ld65 -C $(CFG) -m hello.map hello.o $(OBJECTS) $(RUNTIME)

test: build
	cd ../../../simulator/ && src/fake6502 ../cc65/programs/hello/a.out

clean:
	rm -f *.o *.map
