cmake_minimum_required(VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("BoostTest")

set(BOOST_ROOT "D:/Programming/Boost C++")

set(Boost_USE_STATIC_LIBS ON)      
set(Boost_USE_MULTITHREADED ON)    

find_package(Boost REQUIRED COMPONENTS program_options)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found! Check path: ${BOOST_ROOT}")
endif()

message(STATUS "Boost found at: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

add_executable(BoostTest "BoostTest.cpp"  "ParamsReader.h" "ParamsReader.cpp" "App.h" "App.cpp" "DatabaseManager.h" "DatabaseManager.cpp" "AppExceptions.h" "AppExceptions.cpp" "Log_t.h" "Log_t.cpp" "OwnDB.h" "OwnDB.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoostTest PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(BoostTest PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(BoostTest PRIVATE ${Boost_LIBRARIES})