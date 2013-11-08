#
# Makefile
# Andrew DeMaria (muff1nman), 2013-09-22 14:08
#

all: cp_execute

.PHONY: cp_execute

cp_execute: build
	cp build/lib/dns/dug .

.PHONY: build

build: clean
	mkdir -p build
	cmake -H. -Bbuild
	$(MAKE) -C build

.PHONY: clean

clean:
	rm -rf build
	rm -f dug

# vim:ft=make
#

