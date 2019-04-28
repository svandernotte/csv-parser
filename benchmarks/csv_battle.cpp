#include "csv.hpp"
#include "ben-strasser/csv.h"

int main() {
    constexpr char * data_file = "../tests/data/real_data/2015_StateDepartment.csv";

    std::vector<double> vince_times = {};
    std::vector<double> strasser_times = {};
    const size_t trials = 5;

    try {
        for (int i = 0; i < trials; i++) {
            auto start = std::chrono::system_clock::now();

            csv::CSVReader reader(data_file);
            int entries = 0;
            for (auto& row : reader) {
                row["Year"].get<int>();
                row["Regular Pay"].get<double>();
                row["Overtime Pay"].get<double>();
                row["Total Wages"].get<double>();
                entries++;
            }

            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            vince_times.push_back(diff.count());

            std::cout << "Vincent La's CSV parser read " << entries << " rows" << std::endl;
        }

        for (int i = 0; i < trials; i++) {
            auto start = std::chrono::system_clock::now();

            io::CSVReader<4,
                io::trim_chars<' ', '\t'>,
                io::double_quote_escape<',', '"'>,
                io::throw_on_overflow,
                io::no_comment
            > in(data_file);
            in.read_header(io::ignore_extra_column, "Year", "Regular Pay", "Overtime Pay", "Total Wages");
            int year, entries = 0;
            double reg_pay = 0, overtime_pay = 0, total_wages = 0;
            while (in.read_row(year, reg_pay, overtime_pay, total_wages)) {
                entries++;
            }

            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            strasser_times.push_back(diff.count());

            std::cout << "Ben Strasser's CSV parser read " << entries << " rows" << std::endl;
        }
    }
    catch (std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }

    double s_avg = 0;
    for (double time : strasser_times) {
        s_avg += time * 1 / trials;
    }

    double v_avg = 0;
    for (double time : vince_times) {
        v_avg += time * 1 / trials;
    }
    
    std::cout << std::endl << "Average Times (over 5 trials)" << std::endl;
    std::cout << "Ben Strasser: " << s_avg << std::endl;
    std::cout << "Vincent La: " << v_avg << std::endl;
}