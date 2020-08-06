add_library(minerlib 
    cpu_load.cpp
    cryptonight.cpp
    hash_counter.cpp
    hex_string.cpp
    reply_parser.cpp
    miner_pool.cpp
    mining_algorithm.cpp
    stratum_client.cpp)
target_include_directories(minerlib PUBLIC ./)
target_include_directories(minerlib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:include>
)

