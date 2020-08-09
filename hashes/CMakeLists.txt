add_library(hashes aesb-x86-impl.c aesb.c cryptonight.c c_blake256.c c_groestl.c c_jh.c c_keccak.c c_skein.c hash.c ms_aesb.c oaes_lib.c)
set_target_properties(hashes PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(hashes PUBLIC ./)
target_include_directories(hashes INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:include>
)

