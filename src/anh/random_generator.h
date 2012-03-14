#ifndef ANH_RANDOM_GENERATOR_H_
#define ANH_RANDOM_GENERATOR_H_

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <cstdint>

namespace anh {

class RandomGenerator
{
public:
    explicit RandomGenerator(boost::random::uniform_int_distribution<> distribution);
    RandomGenerator(int start, int end);
    /*
    * Gets the next random number in the generator
    */
    int Rand();
    // generates a random number between the start and end
    // Closed set,meaning it can be the start and end numbers
    int Rand(int start, int end);
    int LastRand();
private:
    int last_random;
    // Mersenne Twister Generator
    boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> distribution_;
};

}
#endif // ANH_RANDOM_GENERATOR_H_