#include <sstream>

#include "csv_utility.hpp"
#include "csv_sql.hpp"

namespace csv {
    namespace sql {
        std::string create_table_pg(csv::string_view filename, CSVFormat format)
        {
            auto dtypes = csv_data_types(filename, format);
            std::string table_name = std::string(filename);

            std::stringstream create_table;
            create_table << "CREATE TABLE IF NOT EXISTS " << table_name;

            /**
            size_t i = 0;
            for (auto& name : stats.get_col_names()) {
                std::string type_name;



                out << "\t\"" << name << "\" " << type_name;


                if (i + 1 < dtypes.size()) out << ",";
                out << std::endl;


                i++;
            }

            out << ");" << std::endl;
            */
            return create_table.str();
        }
    }
}
