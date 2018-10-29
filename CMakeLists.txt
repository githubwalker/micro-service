cmake_minimum_required(VERSION 3.7)

project(micro-service)


find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
find_package(Threads REQUIRED)
find_package(OpenSSL 1.0.1 REQUIRED)
set(OPENSSL_VERSION "1.0.1")
find_package(cpprestsdk REQUIRED)

# Project construction ...

# source files ...
add_executable(${PROJECT_NAME} ./source/main.cpp
                               ./source/microsvc_controller.cpp
                               ./source/foundation/network_utils.cpp
                               ./source/foundation/basic_controller.cpp)

set(MICROSERVICE_INCLUDE_DIR "./source/foundation/include")
message(MICROSERVICE " ${MICROSERVICE_INCLUDE_DIR}")

set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${MICROSERVICE_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

include_directories(${HEADER_SEARCH_PATHS})

target_link_libraries(
   ${PROJECT_NAME} 
    Boost::system
    Boost::thread
    Boost::log
    Boost::program_options
    Boost::chrono
    cpprestsdk::cpprest
)
