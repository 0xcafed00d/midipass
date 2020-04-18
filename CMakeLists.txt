cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project (midipass)

set(CMAKE_THREAD_PREFER_PTHREAD On)
find_package(Threads REQUIRED)
find_package(ALSA REQUIRED)

add_compile_definitions(
	__LINUX_ALSA__
)

add_executable(
	midipass
	src/midipass.cpp
	src/RtMidi.cpp
)

target_link_libraries (
	midipass 
	${ALSA_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)  