#ifndef multiphase_sorting_hpp
#define multiphase_sorting_hpp

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <assert.h>


void outputFile(const std::string& fileName);

bool isFileContainsSortedArray(const std::string &fileName);

void naturalMergeSort3Files(const std::string& fileName);

#endif /* multiphase_sorting_hpp */
