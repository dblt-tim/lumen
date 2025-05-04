MAKEFLAGS += -rR
.SUFFIXES:

IMAGE_NAME = lumen
QEMU_FLAGS = -m 2G -no-reboot -no-shutdown

.PHONY: all
all: $(IMAGE_NAME).iso

TOOLS = tools/bin
ARCH = x86_64

.PHONY: kernel
kernel:
	$(MAKE) -C kernel
limine/limine:
	$(MAKE) -C limine
sysroot:
	mkdir -p sysroot/boot
	mkdir -p sysroot/boot/limine
	cp -v limine.conf sysroot/boot/limine/
	mkdir -p sysroot/EFI/BOOT
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin sysroot/boot/limine/
	cp -v limine/BOOTX64.EFI sysroot/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI sysroot/EFI/BOOT/


$(IMAGE_NAME).iso: limine/limine kernel sysroot
	cp -v kernel/bin/lumen sysroot/boot/
	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		sysroot -o $(IMAGE_NAME).iso
	./limine/limine bios-install $(IMAGE_NAME).iso


.PHONY: run
run: ovmf/ovmf-code-$(ARCH).fd $(IMAGE_NAME).iso
	qemu-system-$(ARCH) \
		-M q35 \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-$(ARCH).fd,readonly=on \
		-cdrom $(IMAGE_NAME).iso \
		$(QEMU_FLAGS)

.PHONY: clean
clean:
	rm -rf $(IMAGE_NAME).iso
