cmake_minimum_required (VERSION 2.6)
project (libstermio C)

INCLUDE (CheckLibraryExists)
INCLUDE(CheckIncludeFiles)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

set(LIBSTERMIO_SOURCE
	stermio.c
	buspirate.c
)

set(LIBSTERMIO_SOURCE
	${LIBSTERMIO_SOURCE}
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

add_library(libstermio ${LIBSTERMIO_SOURCE})

