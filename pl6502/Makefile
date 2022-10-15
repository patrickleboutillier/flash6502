LIBS = /usr/lib/x86_64-linux-gnu/libgtest_main.a /usr/lib/x86_64-linux-gnu/libgtest.a -l pthread
6502_MODULES = *.h

TESTS = test_01_ALUl.cpp test_02_ALUh.cpp test_03_ALU.cpp


pl6502_unittests: $(TESTS) $(6502_MODULES)
	g++ -I ../../circuit/src -I ../../circuit/complib *.cpp -o pl6502_unittests $(LIBS)


test: pl6502_unittests
	./pl6502_unittests


clean:
	rm -f pl6502_unittests