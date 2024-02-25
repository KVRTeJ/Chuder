#include "multiphase_sorting.hpp"

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


void multiphaseSort(const std::string& fileName) {
    const int fileCount = 4; //TODO: в аргументы
    
    std::ifstream origin(fileName);
    
    std::string supportFileNames[fileCount];
    for(int i = 0; i < fileCount; ++i) {
        supportFileNames[i] = "supportFile" + std::to_string(i);
    }
    
    std::fstream **supportFiles = new std::fstream* [fileCount];
    for(int i = 0; i < fileCount; ++i) {
        supportFiles[i] = new std::fstream(supportFileNames[i], std::ios_base::out);
    }
    
    int idealPartition[fileCount];
    int missinSegments[fileCount];
    for(int i = 0; i < fileCount - 1; ++i) {
        idealPartition[i] = missinSegments[i] = 1;
    }
    idealPartition[fileCount - 1] = missinSegments[fileCount - 1] = 0;
    
    int level = 1;
    //TODO: split
    {
        int i = 0;
        int current = 0;
        int next = 0;
        bool hasCurrent = false;
        while(origin) {
            if(i > fileCount - 1)
                i = 0;
            if(hasCurrent) {
                current = next;
                *supportFiles[i] << current << ' ';
            }
            else {
                origin >> current;
                *supportFiles[i] << current << ' ';
            }
            origin >> next;
            while(origin && current < next) {
                current = next;
                origin >> next;
                *supportFiles[i] << current << ' ';
            }
            *supportFiles[i] << '\n';
            hasCurrent = true;
            ++i;
        }
    }
    
    //TODO: merge
    
    for(int i = 0; i < fileCount; ++i) {
        delete supportFiles[i];
    }
    delete [] supportFiles;
    
}
