#For convience 
.PHONY: b build r run
prog=../ngterm
nin=ninja -C .. -j3
b: build
r: run
run: $(prog)
	$(prog)
$(prog): build
build: ../build.ninja
	$(nin)
../build.ninja: 
	env -C .. cmake .
