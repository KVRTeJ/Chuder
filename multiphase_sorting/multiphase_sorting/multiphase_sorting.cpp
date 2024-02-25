#include "multiphase_sorting.hpp"

namespace {

void createEmptyFile(const std::vector<std::string>& fileNames) {
    for(auto it = fileNames.begin(); it != fileNames.end(); ++it) {
        std::ofstream temp(*it);
        temp.close();
    }
}

bool copyFile(const std::string& origin, const std::string& copy) {
    
    std::ifstream fileOrigin(origin);
    std::ofstream fileCopy(copy);
    if(!fileOrigin.is_open() || !fileCopy.is_open())
        return false;
    
    int current = 0;
    while(fileOrigin >> current) {
        fileCopy << current << ' ';
    }
    
    fileOrigin.close();
    fileCopy.close();
    return true;
}

}

namespace NaturalMergeSort {

bool merge(const std::string& boo, const std::string& foo, const std::string& merged) {
    std::ifstream fileBoo(boo), fileFoo(foo);
    std::ofstream fileMerged(merged);
    
    if(!fileBoo.is_open() || !fileFoo.is_open() || !fileMerged.is_open())
        return false;
    
    int currentFoo = 0, currentBoo = 0;
    fileBoo >> currentBoo;
    fileFoo >> currentFoo;
    
    while(fileBoo && fileFoo) {
        if(currentBoo > currentFoo) {
            fileMerged << currentFoo << ' ';
            fileFoo >> currentFoo;
        }
        else {
            fileMerged << currentBoo << ' ';
            fileBoo >> currentBoo;
        }
    }
    
    while(fileBoo) {
        fileMerged << currentBoo << ' ';
        fileBoo >> currentBoo;
    }
    
    while(fileFoo) {
        fileMerged << currentFoo << ' ';
        fileFoo >> currentFoo;
    }
    
    fileBoo.close();
    fileFoo.close();
    fileMerged.close();
    return true;
}

bool split(const std::string& first, const std::string& second, const std::string& splited) {
    std::ifstream supportFileOne(splited);
    std::ofstream supportFileTwo(first);
    std::ofstream supportFileThree(second);
    
    if(!supportFileOne.is_open() || !supportFileTwo.is_open() || !supportFileThree.is_open())
        return false;
    
    int current = 0, next = 0;
    supportFileOne >> current;
    while(supportFileOne) {
        supportFileTwo << current << ' ';
        supportFileOne >> next;
        
        while(supportFileOne && (current <= next)) {
            current = next;
            supportFileTwo << current << ' ';
            supportFileOne >> next;
        }
        if(supportFileOne) {
            current = next;
            supportFileThree << current << ' ';
            supportFileOne >> next;
            while(supportFileOne && (current <= next)) {
                current = next;
                supportFileThree << current << ' ';
                supportFileOne >> next;
            }
        }
        current = next;
    }
    
    supportFileOne.close();
    supportFileTwo.close();
    supportFileThree.close();
    
    return true;
}

}

namespace MultiphaseSort {

int fib(const int num) {
    if(num == 0)
        return 0;
    if(num == 1)
        return 1;
    return fib(num - 1) + fib(num - 2);
}



}

void outputFile(const std::string& fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    assert(origin.is_open());
    
    int current = 0;
    while(origin >> current) {
        std::cout << current << ' ';
    }
    
    origin.close();
    std::cout << std::endl;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    int current = 0, next = 0;
    
    while(origin >> current) {
        origin >> next;
        std::cout << "cur - " << current << " next - " << next << std::endl;
        if(next > current)
            return false;
    }
    
    origin.close();
    return true;
}

void naturalMergeSort3Files(const std::string& fileName) {
    std::ifstream origin(fileName);//1 открытие
    
    std::vector<std::string> supportFileName = {"support_file1.txt", "support_file2.txt", "support_file3.txt"};
    
    std::ifstream isSorted(supportFileName[2]);//1 открытие

    copyFile(fileName, "support_file1.txt");//2 открытия 2 закрытия
    int temp = 0;
    do {
        //использовать fstream и clear для сброса вместо открытия и закрытия?
        NaturalMergeSort::split(supportFileName[1], supportFileName[2], supportFileName[0]);//3 открытия 3 закрытия
        NaturalMergeSort::merge(supportFileName[1], supportFileName[2], supportFileName[0]);//3 открытия 3 закрытия
    } while(isSorted >> temp);
    
    origin.close();
    isSorted.close();//2 закрытия
    // итого 20 операций
}

void multiphaseSort(const std::string& fileName) {
    std::ifstream origin(fileName);
    
    
    
}
