.PHONY: build
build: 
	make -C src build

.PHONY: test
test: build 
	@./src/fake6502 testsuite

.PHONY: hello
hello: build
	@./src/fake6502 ./programs/hello/hello.bin

.PHONY: star
star: build
	@./src/fake6502 ./programs/star/star.bin

.PHONY: clean
clean:
	make -C src clean
