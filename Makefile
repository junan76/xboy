VERSION := 0.0.1

export srctree := $(shell pwd)
export objtree := $(srctree)/build

subdir-y := cpu init
builtins := $(addprefix $(objtree)/, $(addsuffix /builtin.a, $(subdir-y)))

.PHONY: __all
__all: $(builtins)
	$(CC) $(CFLAGS) $^ -o $(objtree)/xboy

$(objtree)/%/builtin.a: %
	$(MAKE) -f $(srctree)/scripts/Makefile.build obj=$<

.PHONY: $(subdir-y)

.PHONY: clean
clean:
	rm -rf $(objtree)