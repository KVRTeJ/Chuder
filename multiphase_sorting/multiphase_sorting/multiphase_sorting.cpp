#include "multiphase_sorting.hpp"

void outputFile(const std::string& fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    if(!origin.is_open()) {
        std::cerr << "outputFile: can't open file named: " << fileName << ". . ." << std::endl;
        return;
    }
    
    int current = 0;
    while(origin >> current) {
        std::cout << current << ' ';
    }
    
    origin.close();
    std::cout << std::endl;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    if(!origin.is_open()) {
        std::cerr << "isFileContainsSortedArray: can't open file named: " << fileName << ". . ." << std::endl;
        return false;
    }
    
    int current = 0, next = 0;
    
    while(origin >> current) {
        origin >> next;
        std::cout << "cur - " << current << " next - " << next << std::endl;
        if(next > current){
            origin.close();
            return false;
        }
    }
    
    origin.close();
    return true;
}


void multiphaseSort(const std::string& fileName) {//TODO: to class or create struct and split for functions
    const int fileCount = 4; //TODO: в аргументы
    
    std::ifstream origin(fileName);
    
    if(!origin.is_open()) {
        std::cerr << "multiphaseSort: can't open file named: " << fileName << ". . ." << std::endl;
        return;
    }
    
    std::string supportFileNames[fileCount];
    for(int i = 0; i < fileCount; ++i) {
        supportFileNames[i] = "supportFile" + std::to_string(i) + ".txt";
    }
    
    std::fstream **supportFiles = new std::fstream* [fileCount];
    for(int i = 0; i < fileCount; ++i) {
        supportFiles[i] = new std::fstream(supportFileNames[i], std::ios_base::out);
        if(!supportFiles[i]->is_open()) {
            std::cerr << "multiphaseSort: can't open file named: " << supportFileNames[i] << ". . ." << std::endl;
            return;
        }
    }
    
    int idealPartition[fileCount];
    int missingSegments[fileCount];
    for(int i = 0; i < fileCount - 1; ++i) {
        idealPartition[i] = missingSegments[i] = 1;
    }
    idealPartition[fileCount - 1] = missingSegments[fileCount - 1] = 0;
    
    int level = 1;
    {
        int i = 0;
        int firstIdealPartition = 0;
        int current = 0;
        int next = 0;
        bool hasCurrent = false;
        while(origin) {
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
            hasCurrent = true;
            *supportFiles[i] << '\n';
            --missingSegments[i];
            
            if(!origin) {
                origin.close();
                for(int i = 0; i < fileCount; ++i) {
                    supportFiles[i]->close();
                }
                break;
            }
            
            if(missingSegments[i] < missingSegments[i + 1]) {
                ++i;
            }
            
            else if(missingSegments[i] == 0) {
                ++level;
                firstIdealPartition = idealPartition[0];
                i = 0;
                for(int k = 0; k < fileCount - 1; ++k) {
                    missingSegments[k] = idealPartition[k + 1] - idealPartition[k] + firstIdealPartition;
                    idealPartition[k] = idealPartition[k + 1] + firstIdealPartition;
                }
            }
            
            else {
                i = 0;
            }
            
        }
    }
    
    //TODO: merge
    for(int i = 0; i < fileCount - 1; ++i) {
        supportFiles[i]->open(supportFileNames[i], std::ios_base::in);
    }
    supportFiles[fileCount - 1]->open(supportFileNames[fileCount - 1], std::ios_base::out);
    
    bool hasFictitiousSegment = true;
    
    while(level > 0) {
        while(supportFiles[fileCount - 2]) {
            
            for(int m = 0; m < fileCount - 1; ++m) {
                hasFictitiousSegment &= static_cast<bool>(missingSegments[m]);
            }
            
            while(hasFictitiousSegment) {
                hasFictitiousSegment = false;
                for(int m = 0; m < fileCount - 1; ++m) {
                    --missingSegments[m];
                    hasFictitiousSegment &= static_cast<bool>(missingSegments[m]);
                }
                ++missingSegments[fileCount - 1];
            }
            
            //TODO: MERGING
            
        }
        
        --level;
        supportFiles[fileCount - 1]->close();
        supportFiles[fileCount - 2]->close();
        supportFiles[fileCount - 1]->open(supportFileNames[fileCount - 1], std::ios_base::in);
        supportFiles[fileCount - 2]->open(supportFileNames[fileCount - 2], std::ios_base::out);
        //TODO: SWAP
        
    }
    
    for(int i = 0; i < fileCount; ++i) {
        delete supportFiles[i];
    }
    delete [] supportFiles;
    
}


