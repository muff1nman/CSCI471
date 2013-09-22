#
# Makefile
# Andrew DeMaria (muff1nman), 2013-09-22 14:08
#

all: run

.PHONY: build

build: clean
	mkdir -p build
	cmake -H. -Bbuild
	$(MAKE) -C build

.PHONY: clean

clean:
	rm -rf build

.PHONY: run

run:  build
	build/lib/Main

# vim:ft=make
#

