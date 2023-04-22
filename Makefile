export ARCH_PREFIX = arm-none-eabi-
export MCPU = cortex-m0plus
export NOLIBS = -nostdlib -lnosys -nodefaultlibs
export EXCEPTION = -fno-exceptions
export RTTI = -fno-rtti
export OPTIMIZE = -O0

export CXX = g++
export AS = as
export WARNINGS = -Wall -Wextra -Wshadow
export CXXFLAGS = $(OPTIMIZE) $(WARNINGS) $(RTTI) $(NOLIBS) $(EXCEPTION) -mcpu=$(MCPU) -static -fno-pic  -Wl,-gc-sections -std=c++23 -g -fdata-sections -ffunction-sections
export ASFLAGS = -mcpu=$(MCPU)

export INC = /include

export ROOT = ./src
clava :
	@$(MAKE) -C src
clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*.a" | xargs rm -f
	find . -name "*.bin" | xargs rm -f
	find . -name "*.hex" | xargs rm -f
	find . -name "*.out" | xargs rm -f
	find . -name "*.dump" | xargs rm -f
	find . -name "*.mk" | xargs rm -f
debug: clava
	openocd -f etc/openocd.cfg
gdb:
	gdb-multiarch -x etc/.gdbinit
telnet:
	telnet localhost 4444
