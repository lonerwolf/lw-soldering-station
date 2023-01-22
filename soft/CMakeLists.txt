set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
cmake_minimum_required(VERSION 3.20)

# 工具链设置
set(TOOLCHAIN_ROOT "D:\\MounRiver\\MounRiver_Studio\\toolchain\\RISC-V Embedded GCC")

if (WIN32)
    MESSAGE(STATUS "Now is windows!")
    find_program ( CMAKE_C_COMPILER  riscv-none-embed-gcc PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( CMAKE_CXX_COMPILER  riscv-none-embed-g++ PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( CMAKE_ASM_COMPILER  riscv-none-embed-gcc PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( CMAKE_AR  riscv-none-embed-ar PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( CMAKE_OBJCOPY  riscv-none-embed-objcopy PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( CMAKE_OBJDUMP  riscv-none-embed-objdump PATHS ${TOOLCHAIN_ROOT}/bin )
    find_program ( SIZE  riscv-none-embed-size PATHS ${TOOLCHAIN_ROOT}/bin )
else ()
    MESSAGE(STATUS "Unsupported system!")
endif ()

# 项目设置
project(lw-soldering-station C CXX ASM)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# 编译参数 一般不用改
add_compile_options(-march=rv32imacxw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore)
add_compile_options(-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()
# 编译等级
#add_compile_options(-O3)

# 编译信息等级
add_compile_options(-Wall)

# 头文件路径
include_directories(User
        Core
        Debug
        Peripheral/inc
        my-peripheral
        FreeRTOS/include
        FreeRTOS/portable/GCC/RISC-V
        FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions
        #fatfs
        lvgl/src
        lvgl-port
        lvglapp/custom
        lvglapp/generated
        lvglapp/generated/guider_fonts)

# 宏定义
add_definitions(-DLV_LVGL_H_INCLUDE_SIMPLE)

# 源码文件
file(GLOB_RECURSE SOURCES
        "User/*.c"
        "Core/core_riscv.c"
        "Debug/debug.c"
        "Peripheral/src/*.c"
        "Startup/startup_ch32v30x_D8C.S"
        FreeRTOS/*.c
        FreeRTOS/*.S
        my-peripheral/*.c
        #fatfs/*.c
        lvgl/src/*.c
        lvgl-port/*.c
        lvglapp/custom/*.c
        lvglapp/generated/*.c
        )

# 链接参数
set(LINKER_SCRIPT  ${CMAKE_SOURCE_DIR}/Ld/Link.ld)
add_link_options(-nostartfiles
        -Xlinker --gc-sections
        -Wl,--print-memory-usage
        -Wl,-Map,${PROJECT_NAME}.map
        --specs=nano.specs
        --specs=nosys.specs)
add_link_options(-T ${LINKER_SCRIPT})

# 编译可执行文件
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

# 链接静态库
target_link_libraries(${PROJECT_NAME}.elf printfloat)
target_link_libraries(${PROJECT_NAME}.elf m)

# 输出hex和bin
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(LST_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lst)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND ${CMAKE_OBJDUMP} --all-headers --demangle --disassemble $<TARGET_FILE:${PROJECT_NAME}.elf> > ${LST_FILE}
        COMMAND ${SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}.elf>
        )
