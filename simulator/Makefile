.PHONY: build
build: 
	make -C src build

.PHONY: test
test: build 
	@./src/fake6502 testsuite

.PHONY: star
star: build
	@./src/fake6502 star

.PHONY: clean
clean:
	make -C src clean
