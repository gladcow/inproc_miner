cmake_minimum_required (VERSION 3.2)

project (inproc_miner VERSION 1.0 LANGUAGES C CXX)

# OpenSSL dependency
find_package( OpenSSL )
include_directories(${OPENSSL_INCLUDE_DIR})

# BOOST depenency
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost 1.52 REQUIRED COMPONENTS system filesystem)

add_subdirectory(hashes)
add_subdirectory(minerlib)
add_subdirectory(miner_test)
