message(STATUS "Entering directory .")
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
#enable_testing()
project(root CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
project(root)

set(NASK "${root_BINARY_DIR}/../../opennask/build/src/opennask" CACHE INTERNAL "")
set(BIN2OBJ "${root_BINARY_DIR}/../../opennask/build/src/bin2obj" CACHE INTERNAL "")
set(MAKEFONT "${root_BINARY_DIR}/../../opennask/build/src/makefont" CACHE INTERNAL "")

set(QEMU "qemu-system-i386" CACHE INTERNAL "")
set(QEMUOPT "-m" "32" "-localtime" "-vga" "std" "-fda" CACHE INTERNAL "")
set(BINOPT "-fleading-underscore" "-m32" "-nostdlib" "-Wl,--oformat=binary" CACHE INTERNAL "")

# ipl.bin
set(ipl_src ${root_SOURCE_DIR}/ipl.nas)
set(ipl_bin ${root_BINARY_DIR}/ipl.bin)
# asmhead.bin
set(asmhead_src ${root_SOURCE_DIR}/asmhead.nas)
set(asmhead_bin ${root_BINARY_DIR}/asmhead.bin)
# hankaku.bin & hankaku.obj
set(hankaku_src ${root_SOURCE_DIR}/hankaku.txt)
set(hankaku_bin ${root_BINARY_DIR}/hankaku.bin)
set(hankaku_obj ${root_BINARY_DIR}/hankaku.obj)

add_custom_target(ipl_bin ALL
  COMMAND ${NASK} ${ipl_src} ${ipl_bin}
)
add_custom_target(asmhead_bin ALL
  COMMAND ${NASK} ${asmhead_src} ${asmhead_bin}
)
add_custom_target(hankaku.bin ALL
  COMMAND ${MAKEFONT} ${hankaku_src} ${hankaku_bin}
)
add_custom_target(hankaku.obj ALL
  COMMAND ${BIN2OBJ} ${hankaku_bin} ${hankaku_obj} _hankaku
)
