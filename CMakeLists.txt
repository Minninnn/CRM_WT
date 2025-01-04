cmake_minimum_required(VERSION 3.10)
project(WT_CRM_v0.1)

set (VCPKG_ROOT "D:/WT_CRM_v0.1/lib/vcpkg")
set (CMAKE_TOOLCHAIN_FILE "D:/WT_CRM_v0.1/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package (wt CONFIG REQUIRED)

add_executable(CRM src/main.cpp)

target_link_libraries(CRM PRIVATE Wt::Wt Wt::Dbo Wt::HTTP)