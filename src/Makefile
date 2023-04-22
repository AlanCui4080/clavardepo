export _ROOT = ../$(ROOT)
export ROOT := $(_ROOT)

OBJS = io_base.o io_group.o io_pin.o startup.o init.o

src : dep.mk $(OBJS)
	@find . -name "*.o" | xargs $(ARCH_PREFIX)g++ -T system.lds $(CXXFLAGS) -Wl,--print-memory-usage -o a.out
	@$(ARCH_PREFIX)objcopy -O binary a.out a.bin
	@$(ARCH_PREFIX)objcopy -O ihex a.out a.hex
	@$(ARCH_PREFIX)objdump -sSD a.out > a.dump

dep.mk: $(shell ls *.cpp)
	$(ARCH_PREFIX)$(CXX) $(CXXFLAGS) -I $(ROOT)$(INC) -MM *.cpp > dep.mk

%.o : %.cpp
	@echo [CXX] $@
	@$(ARCH_PREFIX)$(CXX) -I $(ROOT)$(INC) -c $(CXXFLAGS) $< -o $@
%.o : %.s
	@echo [AS] $@
	@$(ARCH_PREFIX)$(AS) -c $(ASFLAGS) $< -o $@
	
include dep.mk
