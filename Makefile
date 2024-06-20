LLVMPATH = /opt/homebrew/opt/llvm/bin
CLANGFLAGS = -Wall -O2 -ffreestanding -nostdlib -mcpu=cortex-a72+nosimd -Iinclude

BUILD_DIR = build
SRC_DIR = src

all: clean kernel8.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(LLVMPATH)/clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(LLVMPATH)/clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OFILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OFILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

kernel8.img: $(OFILES)
	$(LLVMPATH)/ld.lld -m aarch64elf -nostdlib $(OFILES) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf
	$(LLVMPATH)/llvm-objcopy -O binary $(BUILD_DIR)/kernel8.elf $(BUILD_DIR)/kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img 