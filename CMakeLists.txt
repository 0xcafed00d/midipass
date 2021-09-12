cmake_minimum_required(VERSION 3.16.0)

project (midipass)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_THREAD_PREFER_PTHREAD On)
find_package(Threads REQUIRED)
find_package(ALSA REQUIRED)

add_compile_definitions(
	__LINUX_ALSA__
)

add_executable(
	${CMAKE_PROJECT_NAME}
	src/midipass.cpp
	src/RtMidi.cpp
)

target_link_libraries (
	${CMAKE_PROJECT_NAME}
	${ALSA_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)  