/** @file
 *  Calculates statistics from CSV files
 */

#pragma once
#include <utility>
#include <unordered_map>
#include <vector>
#include "csv_reader.hpp"

namespace csv {
    class CSVStat;

    class Calculations {
    public:
        long double& operator[](size_t n) {
            return this->results[n];
        }

        void set_col_names(std::vector<std::string>& col_names) {
            for (auto& col : col_names) {
                this->results.push_back(NAN);
            }
        }
 
        friend CSVStat;
    private:
        std::vector<long double> results = {};
        std::vector<std::string> col_names = {};
    };

    using StatCallback = std::function<void(CSVField&, Calculations& collection, size_t)>;

    class StatsOptions : public CSVFormat {
    public:
        StatsOptions() = default;
        StatsOptions(CSVFormat& format) {};
        void add_callback(StatCallback callback, Calculations& collection) {
            this->stats_callbacks.push_back(
                std::pair(
                    callback,
                    std::ref(collection)
                )
            );
        }

        friend CSVStat;
    private:
        std::vector<std::pair<StatCallback, Calculations&>> stats_callbacks = {};
    };

    /** Class for calculating statistics from CSV files and in-memory sources
     *
     *  **Example**
     *  \include programs/csv_stats.cpp
     *
     */
    class CSVStat : public CSVReader {
    public:
        using FreqCount = std::unordered_map<std::string, RowCount>;
        using TypeCount = std::unordered_map<DataType, RowCount>;

        void end_feed();
        std::vector<long double> get_mean() const;
        std::vector<long double> get_variance() const;
        std::vector<long double> get_mins() const;
        std::vector<long double> get_maxes() const;
        std::vector<FreqCount> get_counts() const;
        std::vector<TypeCount> get_dtypes() const;

        CSVStat(csv::string_view filename, StatsOptions format = StatsOptions::guess_csv());

        CSVStat(StatsOptions format = StatsOptions()) : CSVReader(format) {
            this->callbacks = format.stats_callbacks;
        };
    private:
        std::vector<std::pair<StatCallback, Calculations&>> callbacks;

        // An array of rolling averages
        // Each index corresponds to the rolling mean for the column at said index
        std::vector<long double> rolling_means;
        std::vector<long double> rolling_vars;
        std::vector<long double> mins;
        std::vector<long double> maxes;
        std::vector<FreqCount> counts;
        std::vector<TypeCount> dtypes;
        std::vector<long double> n;

        // Statistic calculators
        void variance(const long double&, const size_t&);
        void count(CSVField&, const size_t&);
        void min_max(const long double&, const size_t&);
        void dtype(CSVField&, const size_t&);

        void calc();
        void calc_worker(const size_t&);
    };

    // CSV_INLINE
    inline void min_max(CSVField& field, Calculations& calc, const size_t& i) {
        /** Update current minimum and maximum
         *  @param[in]  x_n Data observation
         *  @param[out] i   The column index that should be updated
         */
        auto x_n = field.get<long double>();

        if (isnan(calc[i]))
            calc[i] = x_n;
        //if (isnan(this->maxes[i]))
        //    this->maxes[i] = x_n;

        if (x_n < calc[i])
            calc[i] = x_n;
        //else if (x_n > this->maxes[i])
        //    this->maxes[i] = x_n;
    }
}