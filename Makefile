all: zxc

CMAKE_FLAGS := -DCMAKE_INSTALL_PREFIX=/tmp/usr/local
UNAME := $(shell uname -s)

install:
	cd build && make install

zxc:
	@mkdir -p build
	cd build && cmake $(CMAKE_FLAGS) ..
ifneq ($(MAKE),)
	cd build && $(MAKE)
else
	cd build && make
endif

.PHONY: clean
clean:
	rm -rf build
