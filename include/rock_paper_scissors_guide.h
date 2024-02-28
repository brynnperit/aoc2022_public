#ifndef AOC2022_WEEK1_SOLVER02
#define AOC2022_WEEK1_SOLVER02
#include <filesystem>
#include <iostream>
#include <map>
namespace rock_paper_scissors_guide
{
    class RPSGuide
    {
    public:
        RPSGuide();
        void PrintScoresForGamesInFile(const std::filesystem::path &input_file_path);
        void PrintScoresForGamesInFile(std::istream &input_stream);

        RPSGuide(const RPSGuide &other) = delete;
        RPSGuide &operator=(const RPSGuide &other) = delete;

    private:
        enum class RPS;
        struct GameResult
        {
            RPS opponent_result;
            RPS player_result;
        };
        enum class GameResultType;
        bool GetNextGameResult(RPSGuide::GameResult &result, std::istream &input_stream);
        GameResultType GetGameResultType(RPSGuide::GameResult &result);
        int GetSecondMethodScore(RPSGuide::GameResult &result);
        RPS GetSecondMethodPlayerResult(RPSGuide::GameResult &result, RPSGuide::GameResultType &required_result_type);
        static const std::map<std::string, RPS> kOpponentGuideMoveMap_;
        static const std::map<std::string, RPS> kPlayerGuideMoveMap_;
        static const std::map<RPSGuide::RPS, RPSGuide::RPS> kWinningMoveMap_;
        static const std::map<RPSGuide::RPS, RPSGuide::RPS> kLosingMoveMap_;
    };
};

#endif // AOC2022_WEEK1_SOLVER02
