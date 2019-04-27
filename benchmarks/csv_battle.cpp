#include "csv.hpp"
#include "ben-strasser/csv.h"

int main() {
    constexpr char * data_file = "../tests/data/real_data/2015_StateDepartment.csv";

    io::CSVReader<28> in(data_file);
    in.read_header(io::ignore_extra_column, "Year");
    std::string vendor; int size; double speed;
    while (in.read_row(vendor, size, speed)) {
        // do stuff with the data
    }
}