LIBS = /usr/lib/x86_64-linux-gnu/libgtest_main.a /usr/lib/x86_64-linux-gnu/libgtest.a -l pthread -L ../src
CIRCUIT = ../src/*.h
COMPONENTS = ../complib/*.h

TESTS = 01_circuit_unittests.cpp 02_complib_unittests.cpp


circuit_unittests: $(TESTS) $(CIRCUIT) $(COMPONENTS) 
	g++ -I ../src -I ../complib *.cpp -o circuit_unittests $(LIBS)


test: circuit_unittests
	./circuit_unittests


clean:
	rm -f circuit_unittests
