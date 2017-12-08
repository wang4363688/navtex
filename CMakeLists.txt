cmake_minimum_required(VERSION 2.8.9)
project (navtex)

execute_process(COMMAND cat "${CMAKE_CURRENT_SOURCE_DIR}/version" OUTPUT_VARIABLE pkg_version OUTPUT_STRIP_TRAILING_WHITESPACE)

set(NAVTEX_PKG_VERSION "${pkg_version}")

set(NAVTEX_SRCS src/emission2.c)

add_executable(navtex-em ${NAVTEX_SRCS})
target_link_libraries(navtex-em wiringPi)

install(TARGETS navtex-em RUNTIME DESTINATION bin)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

### Debian Package generation
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION "${NAVTEX_PKG_VERSION}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Pascal Jean")

find_program(DPKG_PROGRAM dpkg DOC "dpkg program of Debian-based systems")
if(DPKG_PROGRAM)
  execute_process(
    COMMAND ${DPKG_PROGRAM} --print-architecture
    OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

else(DPKG_PROGRAM)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}_${CPACK_PACKAGE_VERSION}_${CMAKE_SYSTEM_NAME}")
endif(DPKG_PROGRAM)

set(CPACK_DEBIAN_PACKAGE_DEPENDS "wiringpi (>= 2.00)")

include(CPack)
