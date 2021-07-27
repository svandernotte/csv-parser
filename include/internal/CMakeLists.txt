add_library(csv STATIC "")

set(csv_SOURCES
    basic_csv_parser.cpp
    col_names.cpp
    common.hpp
    csv_format.cpp
    csv_reader.cpp
    csv_reader_iterator.cpp
    csv_row.cpp
    csv_row_json.cpp
    csv_stat.cpp
    csv_utility.cpp
)

target_sources(csv PRIVATE ${csv_SOURCES})
set_target_properties(csv PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(csv PRIVATE Threads::Threads)
target_include_directories(csv PUBLIC ${CSV_INCLUDE_DIR})
