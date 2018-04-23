cmake_minimum_required(VERSION 3.4)
project(imagetransform)

set(CMAKE_CXX_STANDARD 11)
#头文件
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
#file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
#源文件
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
message("<<<<<<<<<")
message(${SOURCE_FILES})
#找到opencv库
find_package(OpenCV)
find_package(Eigen3)


include_directories(
        include
        ${OpenCV_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}

)
LINK_DIRECTORIES(/usr/local/lib)
add_executable(imagetransform

        ${HEADER_FILES}
        ${SOURCE_FILES}

        main.cpp)



#####链接到库
target_link_libraries(
        imagetransform
        #jsoncpp
        ${OpenCV_LIBS}
        ${Eigen3_LIBS}
)
