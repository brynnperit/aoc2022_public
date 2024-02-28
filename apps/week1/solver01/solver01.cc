#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <filesystem>
#include <span>
#include <functional>
#include <algorithm>
#include <numeric>

namespace aoc2022_week1_solver01
{
    static void PrintCalorieTotals(std::istream &input_stream);
    static int GetCaloriesForElf(std::istream &input_stream)
    {
        static std::string_view terminator{""};
        int calorie_sum = 0;
        for (std::string calorie_string; getline(input_stream, calorie_string) && calorie_string != terminator; calorie_sum += stoi(calorie_string))
            ;
        return calorie_sum;
    }

    static void PrintTotalsFromFile(const std::filesystem::path &input_file_path)
    {
        std::ifstream input_file_stream(input_file_path);

        if (!input_file_stream.is_open())
            std::cerr << "failed to open " << input_file_path << '\n';
        else
        {
            PrintCalorieTotals(input_file_stream);
        }
    }

    static void PrintCalorieTotals(std::istream &input_stream)
    {
        std::vector<int> totals(4);
        int new_total = 0;
        do
        {
            new_total = GetCaloriesForElf(input_stream);
            totals.push_back(new_total);
            std::sort(totals.begin(), totals.end(), std::greater<int>());
            while (totals.size() > 3)
            {
                totals.pop_back();
            }
        } while (new_total != 0);

        std::cout << "The elf with the most calories is carrying " << totals.front() << " calories.\n";
        std::cout << "The top three elves are carrying " << std::accumulate(totals.begin(), totals.end(), 0) << " calories.\n";
    }
};

using namespace aoc2022_week1_solver01;
int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::vector<std::string> arguments(argv, argv + argc);

    for (std::string arg : std::span{arguments}.subspan(1))
    {
        PrintTotalsFromFile(std::filesystem::path{arg});
    }
}
