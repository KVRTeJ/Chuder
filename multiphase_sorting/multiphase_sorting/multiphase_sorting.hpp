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

void multiphaseSort(const std::string& fileName);
//для разделителя 
//1) использовать int_max или int_min, при разбиении считать количесво int_max и в конце записать их в конец файла
//2) использовать перенос строки .peek() на проверку /n или любого другого символа как разделителя
//для обмена можно использоввать swap() и без 

#endif /* multiphase_sorting_hpp */
