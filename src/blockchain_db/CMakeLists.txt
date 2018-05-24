# Copyright (c) 2014-2018, The Monero Project
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other
#    materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be
#    used to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
# THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

set(blockchain_db_sources
  blockchain_db.cpp
  lmdb/db_lmdb.cpp
  )

if (BERKELEY_DB)
  set(blockchain_db_sources
  ${blockchain_db_sources}
  berkeleydb/db_bdb.cpp
  )
endif()


set(blockchain_db_headers)

set(blockchain_db_private_headers
  blockchain_db.h
  lmdb/db_lmdb.h
  )

if (BERKELEY_DB)
  set(blockchain_db_private_headers
  ${blockchain_db_private_headers}
  berkeleydb/db_bdb.h
  )
endif()

monero_private_headers(blockchain_db
  ${crypto_private_headers})
monero_add_library(blockchain_db
  ${blockchain_db_sources}
  ${blockchain_db_headers}
  ${blockchain_db_private_headers})
target_link_libraries(blockchain_db
  PUBLIC
    common
    cncrypto
    ringct
    ${LMDB_LIBRARY}
    ${BDB_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

    pybind11_add_module(pyblockchain_db_api MODULE python/pyblockchain_db_api.cpp)

    target_link_libraries(pyblockchain_db_api
          PUBLIC
              blockchain_db
          PRIVATE
            pybind11::module)

    set_target_properties(pyblockchain_db_api PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                                 SUFFIX "${PYTHON_MODULE_EXTENSION}")

    FIND_PACKAGE(PythonInterp 3)
    FIND_PACKAGE(PythonLibs 3)
    find_path( PYTHON_SITE_PACKAGES site-packages ${PYTHON_INCLUDE_PATH}/.. )

    execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "import site; print(site.getsitepackages()[0])" OUTPUT_VARIABLE PACKAGE_PATH)

    string(STRIP ${PACKAGE_PATH} PACKAGE_PATH)
    message(STATUS "PYTHON PACKAGE_PATH : ${PACKAGE_PATH}")

    string(STRIP "${PACKAGE_PATH}" INSTALL_FOLDER)
    message(STATUS "to install at : ${INSTALL_FOLDER}")

    INSTALL(TARGETS pyblockchain_db_api DESTINATION "${INSTALL_FOLDER}")
    #FILE(COPY ${module_files_to_install} DESTINATION ${PACKAGE_PATH})

    #COPY PYTHON TESTS & RUN
    enable_testing()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/python/tests/test_pyblockchain_db_api.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_test(NAME test_pyblockchain_db_api COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/test_pyblockchain_db_api.py)
