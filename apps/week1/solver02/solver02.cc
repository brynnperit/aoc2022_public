#include <rock_paper_scissors_guide.h>

#include <vector>
#include <string>
#include <span>
#include <filesystem>

using namespace rock_paper_scissors_guide;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::vector<std::string> arguments(argv, argv + argc);
    RPSGuide guide;

    for (std::string arg : std::span{arguments}.subspan(1))
    {
        guide.PrintScoresForGamesInFile(std::filesystem::path{arg});
    }
}
