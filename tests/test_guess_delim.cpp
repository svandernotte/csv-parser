/** @file
*  Tests for CSV parsing
*/

#include "catch.hpp"
#include "csv_parser.hpp"

using namespace csv;
using std::vector;
using std::string;

//
// guess_delim()
//
TEST_CASE("col_pos() Test", "[test_col_pos]") {
    int pos = get_col_pos(
        "./tests/data/real_data/2015_StateDepartment.csv",
        "Entity Type");
    REQUIRE(pos == 1);
}

TEST_CASE("guess_delim() Test - Pipe", "[test_guess_pipe]") {
    CSVFormat format = guess_format(
        "./tests/data/real_data/2009PowerStatus.txt");
    REQUIRE(format.delim == '|');
    REQUIRE(format.header == 0);
}

TEST_CASE("guess_delim() Test - Semi-Colon", "[test_guess_scolon]") {
    CSVFormat format = guess_format(
        "./tests/data/real_data/YEAR07_CBSA_NAC3.txt");
    REQUIRE(format.delim == ';');
    REQUIRE(format.header == 0);
}

TEST_CASE("guess_delim() Test - CSV with Comments", "[test_guess_comment]") {
    CSVFormat format = guess_format(
        "./tests/data/fake_data/ints_comments.csv");
    REQUIRE(format.delim == ',');
    REQUIRE(format.header == 5);
}

// get_file_info()
TEST_CASE("get_file_info() Test", "[test_file_info]") {
    CSVFileInfo info = get_file_info(
        "./tests/data/real_data/2009PowerStatus.txt");

    REQUIRE(info.delim == '|');
    REQUIRE(info.n_rows == 37960); // Can confirm with Excel
    REQUIRE(info.n_cols == 3);
    REQUIRE(info.col_names == vector<string>({ "ReportDt", "Unit", "Power" }));
}