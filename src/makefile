# wrapper script for qol while developing (nvim's :make command)
.PHONY: b d r fmt build debug run format

build_dir = ../build
run_cmd = $(build_dir)/target/*
nin = ninja -j3 -C $(build_dir)

b: build
d: debug
r: run
fmt: format

build: $(build_dir)/build.ninja
	$(nin)
run: build
	$(run_cmd)
format: $(build_dir)/build.ninja
	$(nin) format

$(build_dir)/build.ninja: | $(build_dir)
	env -C $(build_dir) cmake .. --preset=default 

$(build_dir):
	mkdir $(build_dir)

clean:
	rm -rf $(build_dir)

debug:
	gdbtui $(run_cmd)
