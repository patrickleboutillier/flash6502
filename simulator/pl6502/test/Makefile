LIBS = /usr/lib/x86_64-linux-gnu/libgtest_main.a /usr/lib/x86_64-linux-gnu/libgtest.a -l pthread


test: test_ALU test_STATUS test_CONTROL


ALU_unittests: test_*ALU*.cpp ../src/*ALU*.h
	g++ -g -I ../../circuit/src -I ../../circuit/complib -I ../src *ALU*.cpp -o ALU_unittests $(LIBS)

test_ALU: ALU_unittests
	./ALU_unittests


STATUS_unittests: test_*STATUS*.cpp ../src/*STATUS*.h
	g++ -g -I ../../circuit/src -I ../../circuit/complib  -I ../src *STATUS*.cpp -o STATUS_unittests $(LIBS)

test_STATUS: STATUS_unittests
	./STATUS_unittests


CONTROL_unittests: test_*CONTROL*.cpp ../src/*CONTROL*.h
	g++ -g -I ../../circuit/src -I ../../circuit/complib  -I ../src *CONTROL*.cpp -o CONTROL_unittests $(LIBS)

test_CONTROL: CONTROL_unittests
	./CONTROL_unittests


clean:
	rm -f ALU_unittests STATUS_unittests CONTROL_unittests


FLASH=SST39SF020A
flash_ALUL:
	minipro -p $(FLASH) -w ALUL_ROM.bin	

flash_ALUH:
	minipro -p $(FLASH) -w ALUH_ROM.bin	

flash_STATUS:
	minipro -p $(FLASH) -w STATUS_ROM.bin	
