
cmake_minimum_required(VERSION 4.2)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY) 
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_ASM_COMPILER x86_64-elf-as)
set(CMAKE_C_COMPILER x86_64-elf-gcc)

project(Lumen C ASM)

include(FetchContent)
FetchContent_Declare(limine
  GIT_REPOSITORY https://github.com/Limine-Bootloader/Limine
  GIT_TAG v11.4.1-binary
)
FetchContent_MakeAvailable(limine)
add_custom_command( # run make to build limine executable if needed
  OUTPUT ${limine_SOURCE_DIR}/limine
  COMMAND make -C ${limine_SOURCE_DIR}
  COMMENT "Building limine deploy tool"
)

FetchContent_Declare(limine_protocol
  GIT_REPOSITORY https://github.com/Limine-Bootloader/limine-protocol
  GIT_TAG trunk
)
FetchContent_MakeAvailable(limine_protocol)

FetchContent_Declare(flanterm
  GIT_REPOSITORY https://github.com/Mintsuki/Flanterm
  GIT_TAG trunk
)
FetchContent_MakeAvailable(flanterm)

file(GLOB_RECURSE K_C_SRCS kernel/source/*.c ${flanterm_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE K_ASM_SRCS kernel/source/*.s)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
  -ffreestanding \
  -fno-stack-protector \
  -fno-stack-check \
  -fno-lto \
  -fno-PIC \
  -mno-80387 \
  -mno-mmx \
  -mno-sse \
  -mno-sse2 \
  -mno-red-zone \
  -mcmodel=kernel"
)

add_executable(kernel.elf
  ${K_C_SRCS}
  ${K_ASM_SRCS}
)
target_link_options(kernel.elf PRIVATE
  -T${CMAKE_SOURCE_DIR}/kernel/link.ld
  -nostdlib
  -static
  -no-pie
)
target_include_directories(kernel.elf PRIVATE ${limine_protocol_SOURCE_DIR}/include ${flanterm_SOURCE_DIR}/src)

set(ISO_ROOT ${CMAKE_BINARY_DIR}/iso_root)

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/lumen.iso
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_ROOT}/boot/limine
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_ROOT}/EFI/boot

  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:kernel.elf> ${ISO_ROOT}/boot/kernel.elf
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/kernel/limine.conf ${ISO_ROOT}/boot/limine/limine.conf

  COMMAND ${CMAKE_COMMAND} -E copy ${limine_SOURCE_DIR}/limine-bios.sys ${ISO_ROOT}/boot/limine/
  COMMAND ${CMAKE_COMMAND} -E copy ${limine_SOURCE_DIR}/limine-bios-cd.bin ${ISO_ROOT}/boot/limine/
  COMMAND ${CMAKE_COMMAND} -E copy ${limine_SOURCE_DIR}/limine-uefi-cd.bin ${ISO_ROOT}/boot/limine/
  COMMAND ${CMAKE_COMMAND} -E copy ${limine_SOURCE_DIR}/BOOTX64.EFI ${ISO_ROOT}/EFI/BOOT/

  COMMAND xorriso -as mkisofs
    -b boot/limine/limine-bios-cd.bin
    -no-emul-boot -boot-load-size 4 -boot-info-table
    --efi-boot boot/limine/limine-uefi-cd.bin
    -efi-boot-part --efi-boot-image --protective-msdos-label
    ${ISO_ROOT} -o ${CMAKE_BINARY_DIR}/lumen.iso

  COMMAND ${limine_SOURCE_DIR}/limine bios-install ${CMAKE_BINARY_DIR}/lumen.iso

  DEPENDS kernel.elf ${CMAKE_SOURCE_DIR}/kernel/limine.conf ${limine_SOURCE_DIR}/limine
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Building bootable ISO..."
  VERBATIM
)

add_custom_target(lumen.iso ALL DEPENDS ${CMAKE_BINARY_DIR}/lumen.iso)