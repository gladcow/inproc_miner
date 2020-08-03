add_executable(miner_test miner_test.cpp)
target_link_libraries (miner_test PUBLIC pthread minerlib hashes ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
