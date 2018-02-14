#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

#define BLOCK_SIZE 300
typedef float data_t;

int main(int argc, char** argv)
{
    //Allocate Memory in Host Memory
    size_t vector_size_bytes = sizeof(data_t) * BLOCK_SIZE;
    std::vector<data_t> source_input(BLOCK_SIZE);
    std::vector<data_t> source_input_1(BLOCK_SIZE);
    std::vector<data_t> source_sw_results(BLOCK_SIZE);

    // Floating point generator for source_input
    std::random_device rd;
    {
      std::mt19937_64 gen(rd());
      std::uniform_real_distribution<float> dis(-2.f, 2.f);
      auto rand = std::bind(dis, gen);
      std::generate(source_input.begin(), source_input.end(), rand);
    }

    // Floating point generator for source_input_1
    {
      std::mt19937_64 gen(rd());
      std::uniform_real_distribution<float> dis(-2.f, 2.f);
      auto rand = std::bind(dis, std::ref(gen));
      std::generate(source_input_1.begin(), source_input_1.end(), rand);
    }

    // Truncating the floating point value to the second place after
    // the decimal point.
    for(int i = 0 ; i < BLOCK_SIZE ; i++) {
      source_input[i] = std::trunc(100 *  source_input[i]) / 100;
      source_input_1[i] = std::trunc(100 *  source_input_1[i]) / 100;
    }

    // Do vector add and print out the operands and the result
    for(int i = 0 ; i < BLOCK_SIZE ; i++){
        source_sw_results[i] = source_input[i] + source_input_1[i];
        std::cout << source_input[i] << " " << source_input_1[i]
                  << " " << source_sw_results[i] << "\n";
    }

    return 0;
}
