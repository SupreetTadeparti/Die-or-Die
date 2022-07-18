#include "Util.hpp"

namespace Moon
{
	Int Util::Random(Int start, Int end)
	{
        std::mt19937_64 rng;
        uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
        rng.seed(ss);
        std::uniform_int_distribution<> unif(start, end);
        return unif(rng);
	}

    std::chrono::milliseconds Util::CurrentTime()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }
}