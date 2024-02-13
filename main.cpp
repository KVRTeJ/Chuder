#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <random>

namespace functions {
    void outputIfInRange(const int num) {
        if(num > 10 && num < 40)
            std::cout << num << std::endl;
    }

    void outputIfEven(const int num) {
        if(num % 2 == 0) {
            std::cout << num << std::endl;
        }
    }

    int sum(const int foo, const int boo) {
        std::cout << "\t\tfunctions::sum started. . ." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Поток #" << std::this_thread::get_id() << " first num - " << foo << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Поток #" << std::this_thread::get_id() << " second num - " << boo << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Поток #" << std::this_thread::get_id() << "calculated. . ." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "\t\tfunctions::sum ended. . ." << std::endl;
        
        return foo + boo;
    }
}

namespace vector {
    void sift(const std::vector<int>& nums, std::function<void(const int)> func) {
        for(auto it = nums.begin(); it != nums.end(); ++it) {
            func(*it);
        }
    }

    void setRandom(std::vector<int>& elements) {
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            *it = rand() % 5 + (it != elements.begin()
                                ? *(it - 1) :
                                0);
        }
    }

    void output(const std::vector<int>& elements) {
        std::cout << "\t\tvector::output started. . ." << std::endl;
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Поток #" << std::this_thread::get_id() << "\t-\t" << *it << std::endl;
        }
        std::cout << "\t\tvector::output ended. . ." << std::endl;
    }
}

int main() {
    srand(0);
    
    std::vector<int> nums(15);
    vector::setRandom(nums);
    
    int result;
    std::thread th([&result]() {
        result = functions::sum(10, 20);
    });
    vector::output(nums);
    
    std::vector<std::function<void(const int)>> funcs = {functions::outputIfEven, functions::outputIfInRange, [](const int num) {
        std::cout << num << " ";
    }};
    
    th.join();

    std::cout << "Result is " << result << std::endl;
    return 0;
}
