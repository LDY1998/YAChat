set_toolchains("clang")

add_rules("mode.debug", "mode.release")

-- add_requires("sqlpp11")
add_requires("conda::SQLiteCpp", {alias = "SQLiteCpp"})



target("hello")
    set_kind("binary")
    add_files("main.cpp") 

target("client")
    set_kind("binary")
    add_cxflags("-pthread")
    add_ldflags("-pthread", "-fopenmp")
    add_files("./client/*.cpp")


target("server")
    set_kind("binary")
    add_cxflags("-pthread")
    add_ldflags("-pthread", "-fopenmp")
    add_cxflags("-lboost_thread")
    add_ldflags("-lboost_thread")
    add_files("./server/*.cpp")
    add_packages("SQLiteCpp")