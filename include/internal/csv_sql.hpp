#pragma once
#include "csv_stat.hpp"

namespace csv {
    namespace sql {
        /** Generate a CREATE TABLE command for uploading file to Postgres */
        std::string create_table_pg(csv::string_view filename, CSVFormat format = CSVFormat::GUESS_CSV);
    }
}
