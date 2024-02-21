#ifndef multiphase_sorting_hpp
#define multiphase_sorting_hpp

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <assert.h>


void outputFile(const std::string& fileName);

bool isFileContainsSortedArray(const std::string &fileName);

bool merge(const std::string& boo, const std::string& foo, const std::string& merged);

#endif /* multiphase_sorting_hpp */
