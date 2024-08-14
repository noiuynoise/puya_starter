CPU = -mcpu=cortex-m0plus
MCU = $(CPU) -mthumb
LIBS = -lc -lm -lstdc++ -nostartfiles
OPT = -g -O3

LFILE = startup/linker.ld

CPP_INCLUDES =  \
-I. \
-Iutils \
-ICMSIS/Include \
-ICMSIS/Device/PY32F0xx/Include

CPP_SRCS := $(shell find startup -name '*.cc') \
$(shell find src -name '*.cc')

BUILD_DIR = build

CXX = arm-none-eabi-g++
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
CP = arm-none-eabi-objcopy

CPPFLAGS = $(MCU) $(OPT) $(LIBS) $(CPP_INCLUDES) -std=c11
CXXFLAGS = $(MCU) $(OPT) $(LIBS) $(CPP_INCLUDES) -std=c++11 -fno-exceptions -fno-rtti
LDFLAGS = $(MCU) -T$(LFILE) $(LIBS) -Wl,--print-memory-usage -specs=nano.specs -specs=nosys.specs

.PHONY: all
all: $(BUILD_DIR)/main.hex

$(BUILD_DIR)/main.hex: $(BUILD_DIR)/main.elf
	$(CP) -O ihex $< $@

$(BUILD_DIR)/main.elf: $(addprefix $(BUILD_DIR)/, $(CPP_SRCS:.cc=.o))
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir $@	

.PHONY: clean
clean:
	rm -rf build