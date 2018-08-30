cmake_minimum_required (VERSION 2.6)
project (libstermio C)

set (LIBSTERMIO_VERSION_MAJOR 0)
set (LIBSTERMIO_VERSION_MINOR 0)
set (LIBSTERMIO_VERSION_PATCH 2)

INCLUDE (CheckLibraryExists)
INCLUDE(CheckIncludeFiles)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include")

set(STERMIO_SOURCE
	stermio.c
	buspirate.c
)

option(EHWE_DEBUGS_SERIAL
	"Debug source serial.c with logs as warnings" OFF)

################################################################################
# System & host-libraries detection
################################################################################
CHECK_INCLUDE_FILES(termio.h HAVE_POSIX_TERMIO)
if (CYGWIN)
	set(HAVE_CYGWIN "1")
endif (CYGWIN)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

add_library(stermio        SHARED ${STERMIO_SOURCE})
add_library(stermio_static STATIC ${STERMIO_SOURCE})

set_target_properties(
  stermio PROPERTIES PUBLIC_HEADER
  "include/libstermio/stermio.h;include/libstermio/assure.h")

# Installation
# ------------

# Shells (ignore for now)
#install(PROGRAMS ${PROJECT_BINARY_DIR}/blaha.sh DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Targets:
install(TARGETS stermio stermio_static
        RUNTIME       DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY       DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE       DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

