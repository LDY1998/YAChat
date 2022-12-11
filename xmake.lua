add_rules("mode.debug", "mode.release")

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
    add_files("./server/*.cpp")