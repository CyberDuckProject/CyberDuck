add_executable(
        HttpFileServer
        main.cpp
)

target_link_libraries(
        HttpFileServer PRIVATE
        Boost::boost
        Boost::filesystem
)