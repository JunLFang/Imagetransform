cmake_minimum_required(VERSION 3.4)
project(imagetransform)

#-------------------------------------- 编译器设置 --------------------------------------
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -fPIC")
else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -fPIC -rdynamic")
endif()


#-------------------------------------- -添加项目- --------------------------------------
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
        ${Eigen3_LIBS})
