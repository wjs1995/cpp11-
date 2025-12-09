cmake_minimum_required(VERSION 4.0)
project(cpp11)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp11 main.cpp
        main.cpp
        bind绑定器.cpp
        muduo.cpp
        muduo_youhua.cpp
        lambda表达式.cpp
        bind1first.cpp
        bind1first.cpp
        多线程.cpp
        多线程同步通信.cpp
        锁测试.cpp
        cas.cpp
        dep.h
        单例模式.cpp
        测试拷贝.cpp
        懒汉式单例模式.cpp)
