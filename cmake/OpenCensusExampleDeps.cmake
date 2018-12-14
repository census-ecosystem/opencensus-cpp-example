# Copyright 2018, OpenCensus Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

message(STATUS "Dependency: abseil")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/abseil.CMakeLists.txt
	${CMAKE_BINARY_DIR}/abseil-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-download)
if(result)
  message(FATAL_ERROR "CMake step failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-download)
if(result)
  message(FATAL_ERROR "Build step failed: ${result}")
endif()

add_subdirectory(
	${CMAKE_BINARY_DIR}/abseil-src
	${CMAKE_BINARY_DIR}/abseil-build
	EXCLUDE_FROM_ALL)

# ----------------------------------------------------------------------

message(STATUS "Dependency: opencensus-cpp")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/opencensus-cpp.CMakeLists.txt
	${CMAKE_BINARY_DIR}/opencensus-cpp-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opencensus-cpp-download)
if(result)
  message(FATAL_ERROR "CMake step failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opencensus-cpp-download)
if(result)
  message(FATAL_ERROR "Build step failed: ${result}")
endif()

add_subdirectory(
	${CMAKE_BINARY_DIR}/opencensus-cpp-src
	${CMAKE_BINARY_DIR}/opencensus-cpp-build
	EXCLUDE_FROM_ALL)
