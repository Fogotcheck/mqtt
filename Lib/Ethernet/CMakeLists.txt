cmake_minimum_required(VERSION 3.22)

set(LWIP_DIR ${CMAKE_SOURCE_DIR}/build/_deps/lwip_kernel-src)
set(LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    "${LWIP_DIR}/contrib"
)

add_library(ETHERNET_INTERFACE INTERFACE)

# MEMP_OVERFLOW_CHECK must be defined FetchContent_MakeAvailable
# or LWIP_STATS_DISPLAY || LWIP_DEBUG
# lwip_kernel -> set (LWIP_DEFINITIONS LWIP_DEBUG=1)
# else mempool will be
target_compile_definitions(
    ETHERNET_INTERFACE
    INTERFACE
    MEMP_OVERFLOW_CHECK=1
)

target_sources(
    ETHERNET_INTERFACE
    INTERFACE
    target/ports/freertos/sys_arch.c
)

target_include_directories(
    ETHERNET_INTERFACE
    INTERFACE
    AppEthernet
    AppLWIP
    OptsLWIP
    target
    target/phy
    target/ports/freertos/include
    ${LWIP_INCLUDE_DIRS}
)

target_link_libraries(
    ETHERNET_INTERFACE
    INTERFACE
    freertos_kernel
)

FetchContent_Declare(lwip_kernel
    GIT_REPOSITORY https://github.com/lwip-tcpip/lwip.git
    GIT_TAG master
)

FetchContent_MakeAvailable(lwip_kernel)

add_library(
    ETHERNET
    AppEthernet/AppEthernet.cpp
    AppLWIP/lwip.c
    target/phy/lan8742.c
    target/ethernetif.c
)

target_link_libraries(
    lwipcore
    ETHERNET_INTERFACE
)
target_link_libraries(
    lwipallapps
    ETHERNET_INTERFACE
)
target_link_libraries(
    lwipmbedtls
    ETHERNET_INTERFACE
)

target_link_libraries(
    ETHERNET
    ETHERNET_INTERFACE
    lwipcore
    lwipallapps
    lwipmbedtls
)
