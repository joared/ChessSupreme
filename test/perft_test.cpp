#include <gtest/gtest.h>

#include "chesshandler.h"
#include "utility.h"

// The performance tests are executed optionally
#ifdef RUN_OPTIONAL_PERFORMANCE_TEST
TEST(PerfTest, Nodes)
{
    // https://www.chessprogramming.org/Perft_Results
    std::vector<std::pair<int, uint64_t>> expected = 
    {
        // (depth, expectedNodes)
        std::make_pair<int,uint64_t>(0, 1),
        std::make_pair<int,uint64_t>(1, 20),
        std::make_pair<int,uint64_t>(2, 400),
        std::make_pair<int,uint64_t>(3, 8902),
        std::make_pair<int,uint64_t>(4, 197281),
        // Tests beyond depth 4 will currently fail since enpassant is not implemented
        std::make_pair<int,uint64_t>(5, 4865609)
    };

    for ( auto it : expected )
    {
        int depth = it.first;
        uint64_t nodesExpected = it.second;
        Utils::Timer timer;
        ChessHandler ch;
        
        timer.start();
        uint64_t nodes = ch.perft(depth);
        auto elapsed = timer.stop() / 1000000.0;

        std::cout << "Elapsed: " + std::to_string(elapsed);
        std::cout << "s (depth:" << depth;
        std::cout << ", nodes: " << nodes << ")";
        std::cout << std::endl;
        
        // If the test fails, we still continue
        EXPECT_EQ(nodesExpected, nodes);
    }
    
};

TEST(PerfTest, TimePerMove)
{
    Utils::Timer timer;
    ChessHandler ch;
    int n = 1000;

    timer.start();
    for (int i=0; i<n; i++)
    {
        auto moves = ch.validMoves();
        if (moves.size() > 0)
        {
            ch.makeMove(moves[0]);
            ch.undo();
        }
    }
    auto elapsed = timer.stop();
    auto elapsedPerMove = elapsed / n / 1000000.0;

    std::cout << "Time/move: " + std::to_string(elapsedPerMove) + "s" << std::endl;

};
#endif // RUN_OPTIONAL_PERFORMANCE_TEST