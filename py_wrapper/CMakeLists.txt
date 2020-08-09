INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

PYTHON_ADD_MODULE(StratumLib stratum_py_wrapper)

# Suppress prefix "lib" because Python does not allow this prefix
set_target_properties(StratumLib PROPERTIES PREFIX "")

target_link_libraries(StratumLib PUBLIC pthread minerlib hashes ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

# install(TARGETS StratumLib DESTINATION "${PYTHON_INSTALL_PATH}")
# install(FILES __init__.py DESTINATION "${PYTHON_INSTALL_PATH}")

