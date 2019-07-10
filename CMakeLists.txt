cmake_minimum_required(VERSION 3.12)
project(trade_manager_system C)

set(CMAKE_C_STANDARD 11)

add_executable(trade_manager_system main.c lib.h run.h lib/initialize.h lib/basic_def.h lib/functions.h lib/basic_io.h lib/checker.h lib/wel_log_reg.h lib/MD5.h lib/file_op.h lib/surface.h lib/search.h lib/info_op.h lib/type_io.h lib/link_op.h)