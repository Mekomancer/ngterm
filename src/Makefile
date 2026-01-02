#For qol while developing 
.PHONY: b build r run fmt format 

prog=../ngterm
nin=ninja -C .. -j3

b: build
r: run
fmt: format

format: ../build.ninja
	$(nin) format
run: $(prog)
	$(prog)
$(prog): build
build: ../build.ninja
	$(nin)
../build.ninja: 
	env -C .. cmake . 

