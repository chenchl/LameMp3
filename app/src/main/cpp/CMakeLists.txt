# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#设置变量SRC_DIR为lamemp3的所在路径
set(SRC_DIR ${CMAKE_SOURCE_DIR}/libmp3lame)

#指定头文件所在，可以多次调用，指定多个路径
include_directories(${CMAKE_SOURCE_DIR}/libmp3lame)

#设定一个目录
aux_source_directory(${CMAKE_SOURCE_DIR}/libmp3lame SRC_LIST)

file(GLOB lame_source ${CMAKE_SOURCE_DIR}/libmp3lame/*.c)
#将前面目录下所有的文件都添加进去
add_library( # Sets the name of the library.
        lamemp3

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        lame-lib.cpp
        #${lame_source}
        ${SRC_LIST})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        lamemp3

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})