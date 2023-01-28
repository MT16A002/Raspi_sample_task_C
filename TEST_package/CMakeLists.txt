# CMakeList.txt : TEST_package の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

#add_executable(main main.c)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
find_package( Threads REQUIRED )
include_directories(task_sub1.h)
include_directories(task_sub2.h)
include_directories(main.h)
add_executable (TEST_package "task_sub1.c" "task_sub1.h" "task_sub2.c" "task_sub2.h" "main.c" "main.h" "task_sub.h")

target_compile_options(TEST_package PUBLIC -O2 -Wall)
target_link_libraries(TEST_package PUBLIC -pthread)
target_link_libraries(TEST_package PUBLIC -lwiringPi)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
#if(CMAKE_USE_PTHREADS_INIT)
#    target_link_libraries(Threads::Threads INTERFACE -lpthread)
#endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TEST_package PROPERTY CXX_STANDARD 20)
endif()

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
