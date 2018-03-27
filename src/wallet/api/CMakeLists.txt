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

# include (${PROJECT_SOURCE_DIR}/cmake/libutils.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(wallet_api_sources
  wallet.cpp
  wallet_manager.cpp
  transaction_info.cpp
  transaction_history.cpp
  pending_transaction.cpp
  utils.cpp
  address_book.cpp
  subaddress.cpp
  subaddress_account.cpp
  unsigned_transaction.cpp)

set(wallet_api_headers
    wallet2_api.h)

set(wallet_api_private_headers
  wallet.h
  wallet_manager.h
  transaction_info.h
  transaction_history.h
  pending_transaction.h
  common_defines.h
  address_book.h
  subaddress.h
  subaddress_account.h
  unsigned_transaction.h)

monero_private_headers(wallet_api
  ${wallet_api_private_headers})
monero_add_library(wallet_api
  ${wallet_api_sources}
  ${wallet_api_headers}
  ${wallet_api_private_headers})
target_link_libraries(wallet_api
  PUBLIC
    wallet
    common
    cryptonote_core
    mnemonics
    ${Boost_CHRONO_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

pybind11_add_module(pywallet_api MODULE python/pywallet_api.cpp)

target_link_libraries(pywallet_api
      PUBLIC
        wallet_api
      PRIVATE
        pybind11::module)

set_target_properties(pywallet_api PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                             SUFFIX "${PYTHON_MODULE_EXTENSION}")

FIND_PACKAGE(PythonInterp 3)
FIND_PACKAGE(PythonLibs 3)
find_path( PYTHON_SITE_PACKAGES site-packages ${PYTHON_INCLUDE_PATH}/.. )

execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "import site; print(site.getsitepackages()[0])" OUTPUT_VARIABLE PACKAGE_PATH)

string(STRIP ${PACKAGE_PATH} PACKAGE_PATH)
message(STATUS "PYTHON PACKAGE_PATH : ${PACKAGE_PATH}")

string(STRIP "${PACKAGE_PATH}" INSTALL_FOLDER)
message(STATUS "to install at : ${INSTALL_FOLDER}")

INSTALL(TARGETS pywallet_api DESTINATION "${INSTALL_FOLDER}")
#FILE(COPY ${module_files_to_install} DESTINATION ${PACKAGE_PATH})

set_property(TARGET wallet_api PROPERTY EXCLUDE_FROM_ALL TRUE)
set_property(TARGET obj_wallet_api PROPERTY EXCLUDE_FROM_ALL TRUE)

if(IOS)
    set(lib_folder lib-${ARCH})
else()
    set(lib_folder lib)
endif()

install(FILES ${wallet_api_headers}
    DESTINATION include/wallet/api)
