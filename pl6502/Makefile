LIBS = /usr/lib/x86_64-linux-gnu/libgtest_main.a /usr/lib/x86_64-linux-gnu/libgtest.a -l pthread
6502_MODULES = *.h


test: test_ALU test_STATUS


ALU_unittests: *ALU*.cpp *ALU*.h
	g++ -g -I ../../circuit/src -I ../../circuit/complib *ALU*.cpp -o ALU_unittests $(LIBS)

test_ALU: ALU_unittests
	./ALU_unittests


STATUS_unittests: *STATUS*.cpp *STATUS*.h
	g++ -g -I ../../circuit/src -I ../../circuit/complib *STATUS*.cpp -o STATUS_unittests $(LIBS)

test_STATUS: STATUS_unittests
	./STATUS_unittests


clean:
	rm -f ALU_unittests STATUS_unittests