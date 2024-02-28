#include <vector>
#include <string>
#include <span>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <rock_paper_scissors_guide.h>

namespace rock_paper_scissors_guide
{
    using namespace std::literals;

    enum class RPSGuide::RPS
    {
        kRock = 1,
        kPaper = 2,
        kScissors = 3
    };

    enum class RPSGuide::GameResultType
    {
        kWin = 6,
        kDraw = 3,
        kLoss = 0
    };

    const std::map<std::string, RPSGuide::RPS> RPSGuide::kOpponentGuideMoveMap_{{"A"s, RPS::kRock}, {"B"s, RPS::kPaper}, {"C"s, RPS::kScissors}};
    const std::map<std::string, RPSGuide::RPS> RPSGuide::kPlayerGuideMoveMap_{{"X"s, RPS::kRock}, {"Y"s, RPS::kPaper}, {"Z"s, RPS::kScissors}};
    const std::map<RPSGuide::RPS, RPSGuide::RPS> RPSGuide::kWinningMoveMap_{{RPS::kRock, RPS::kPaper}, {RPS::kPaper, RPS::kScissors}, {RPS::kScissors, RPS::kRock}};
    const std::map<RPSGuide::RPS, RPSGuide::RPS> RPSGuide::kLosingMoveMap_{{RPS::kPaper, RPS::kRock}, {RPS::kScissors, RPS::kPaper}, {RPS::kRock, RPS::kScissors}};

    RPSGuide::RPSGuide(){};

    void RPSGuide::PrintScoresForGamesInFile(const std::filesystem::path &input_file_path)
    {
        std::ifstream input_file_stream(input_file_path);

        if (!input_file_stream.is_open())
            std::cerr << "failed to open " << input_file_path << '\n';
        else
        {
            PrintScoresForGamesInFile(input_file_stream);
        }
    }

    void RPSGuide::PrintScoresForGamesInFile(std::istream &input_stream)
    {
        int first_score = 0;
        int second_score = 0;
        GameResult result;
        while (GetNextGameResult(result, input_stream))
        {
            first_score += static_cast<int>(result.player_result);
            GameResultType player_result_type = GetGameResultType(result);
            first_score += static_cast<int>(player_result_type);

            second_score += GetSecondMethodScore(result);
        }
        std::cout << "The total score for the games played by first part method is "s << first_score << "\n"s;
        std::cout << "The total score for the games played by second part method is "s << second_score << "\n"s;
    }

    int RPSGuide::GetSecondMethodScore(RPSGuide::GameResult &result)
    {
        GameResultType second_method_result_type;
        switch (result.player_result)
        {
        case RPS::kRock:
            second_method_result_type = GameResultType::kLoss;
            break;
        case RPS::kPaper:
            second_method_result_type = GameResultType::kDraw;
            break;
        case RPS::kScissors:
            second_method_result_type = GameResultType::kWin;
            break;
        }
        RPS second_method_player_result = GetSecondMethodPlayerResult(result, second_method_result_type);
        return static_cast<int>(second_method_result_type) + static_cast<int>(second_method_player_result);
    }

    RPSGuide::RPS RPSGuide::GetSecondMethodPlayerResult(RPSGuide::GameResult &result, RPSGuide::GameResultType &required_result_type)
    {
        switch (required_result_type)
        {
        case GameResultType::kDraw:
            return result.opponent_result;
            break;
        case GameResultType::kWin:
            return RPSGuide::kWinningMoveMap_.find(result.opponent_result)->second;
            break;
        case GameResultType::kLoss:
            return RPSGuide::kLosingMoveMap_.find(result.opponent_result)->second;
            break;
        }
        std::cerr << "Can't happen\n"s;
        return RPS::kRock;
    }

    bool RPSGuide::GetNextGameResult(RPSGuide::GameResult &result, std::istream &input_stream)
    {
        std::string terminator = ""s;
        std::string input_string;
        input_stream >> input_string;
        RPSGuide::RPS opponent_move;
        if (auto opponent_search = kOpponentGuideMoveMap_.find(input_string); opponent_search != kOpponentGuideMoveMap_.end())
        {
            opponent_move = opponent_search->second;
            input_stream >> input_string;
            RPSGuide::RPS player_move;
            if (auto player_search = kPlayerGuideMoveMap_.find(input_string); player_search != kPlayerGuideMoveMap_.end())
            {
                player_move = player_search->second;

                result.opponent_result = opponent_move;
                result.player_result = player_move;
                return true;
            }
        }
        return false;
    }

    RPSGuide::GameResultType RPSGuide::GetGameResultType(RPSGuide::GameResult &result)
    {
        if (result.player_result == result.opponent_result)
        {
            return GameResultType::kDraw;
        }
        if (kWinningMoveMap_.find(result.opponent_result)->second == result.player_result)
        {
            return GameResultType::kWin;
        }
        return GameResultType::kLoss;
    }
};
