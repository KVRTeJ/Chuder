#include <assert.h>

#include "multiphase_sorting.hpp"

void MultiphaseSort::setFileCount(const int value) {
    if(value <= 2) {
        m_fileCount = 3;
    }
    m_fileCount = value;
    
    m_supportFiles.resize(m_fileCount);
}

void MultiphaseSort::setFileName(const std::string& fileName) {
    m_originFileName = fileName;
}

void MultiphaseSort::sort() {
    if(!m_setSupportFileNames(m_generateSupportFileNames())) {
        std::cerr << "MultiphaseSort::sort: error, file count must be > 2 . . ." << std::endl;
        return;
    }
    
    m_originFile.open(m_originFileName);
    if(!m_originFile.is_open()) {
        std::cerr << "MultiphaseSort::sort(): can't open file named: " << m_originFileName << ". . ." << std::endl;
        return;
    }
   
    for(int i = 0; i < m_fileCount - 1; ++i) {
        m_supportFiles[i].supportFile.open(m_supportFiles[i].name, std::ios_base::out);
        if(!m_supportFiles[i].supportFile.is_open()) {
            std::cerr << "MultiphaseSort::sort(): can't open file named: " << m_supportFiles[i].name << ". . ." << std::endl;
            return;
        }
        m_supportFiles[i].idealPartition = 1;
        m_supportFiles[i].missingSegments = 1;
    }
    m_supportFiles[m_fileCount - 1].supportFile.open(m_supportFiles[m_fileCount - 1].name, std::ios_base::out);
    if(!m_supportFiles[m_fileCount - 1].supportFile.is_open()) {
        std::cerr << "MultiphaseSort::sort(): can't open file named: " << m_supportFiles[m_fileCount - 1].name << ". . ." << std::endl;
        return;
    }
    m_supportFiles[m_fileCount - 1].idealPartition = 0;
    m_supportFiles[m_fileCount - 1].missingSegments = 0;
    
    m_merge(m_split());
    
    
    
}

void MultiphaseSort::outputFile(const std::string& fileName) const {
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

bool MultiphaseSort::isFileContainsSortedArray(const std::string &fileName) const {
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

std::vector<std::string> MultiphaseSort::m_generateSupportFileNames() const {
    std::vector<std::string> fileNames(m_fileCount);
    
    for(int i = 0; i < m_fileCount; ++i) {
       fileNames[i] = "supportFile_" + std::to_string(i) + ".txt";
    }
    
    return fileNames;
}

bool MultiphaseSort::m_setSupportFileNames(const std::vector<std::string>& fileNames) {
    if(m_fileCount <= 2)
        return false;
    if(fileNames.size() != m_fileCount)
        return false;
    
    for(int i = 0; i < m_fileCount; ++i) {
        m_supportFiles[i].name = fileNames[i];
    }
    
    return true;
}

/*
int MultiphaseSort::findMinElementIndex() { //FIXME: fixme
    int result = 0;
    while(nums[result] == INT_MIN)
        ++result;
    if(result >= size)
        return -1;
    for(int i = result + 1; i < size; ++i) {
        if(nums[result] > nums[i] && nums[i] != INT_MIN)
            result = i;
    }
    
    return result;
}
*/

int MultiphaseSort::split() { //TODO: intMinCounter
    //FIXME: fixme
    int level = 1;
    {
        int i = 0;
        int firstIdealPartition = 0;
        int current = 0;
        int next = 0;
        bool hasCurrent = false;
        while(m_originFile) {
            if(hasCurrent) {
                current = next;
                m_supportFiles[i].supportFile << current << ' ';
            }
            else {
                m_originFile >> current;
                /* //FIXME: fixme
                 if(current == INT_MIN)
                    ++intMinCounter;
                 */
                m_supportFiles[i].supportFile << current << ' ';
            }
            origin >> next;
            while(origin && current < next) {
                current = next;
                origin >> next;
                *supportFiles[i] << current << ' ';
            }
            hasCurrent = true;
            *supportFiles[i] << INT_MIN; //Разделитель отрезков
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
    
}

/*


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
    int intMinCounter = 0;
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
                ///
                 if(current == INT_MIN)
                    ++intMinCounter;
                 ///
                *supportFiles[i] << current << ' ';
            }
            origin >> next;
            while(origin && current < next) {
                current = next;
                origin >> next;
                *supportFiles[i] << current << ' ';
            }
            hasCurrent = true;
            *supportFiles[i] << INT_MIN; //Разделитель отрезков
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
    
    //TODO: merge//////////////////////////////////////////////////////////////////
    
    for(int i = 0; i < fileCount - 1; ++i) {
        supportFiles[i]->open(supportFileNames[i], std::ios_base::in);
    }
    supportFiles[fileCount - 1]->open(supportFileNames[fileCount - 1], std::ios_base::out);
    
    bool hasFictitiousSegment = true;
    
    while(level > 0) {
        while(*supportFiles[fileCount - 2]) { //FIXME: итерируется на 1 раз больше. Скорее ввсего из-за INT_MIN
            
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
            for(int i = 0; i < fileCount - 1; ++i) {
                if(missingSegments[i]) {
                    --missingSegments[i];
                    idealPartition[i] = INT_MIN;
                }
                
                else {
                    *supportFiles[i] >> idealPartition[i];
                    if(!*supportFiles[i]) {
                        
                    }
                }
            }
            
            for(int minIndex = findMinElementIndex(idealPartition, fileCount - 1); minIndex != -1;
                minIndex = findMinElementIndex(idealPartition, fileCount - 1)) {
                *supportFiles[fileCount - 1] << ' ' << idealPartition[minIndex] << ' ';
                ////
                std::cout << "min - " << idealPartition[minIndex] << std::endl;
                std::cout << "ip - ";
                for(int i = 0; i < fileCount - 1; ++i)
                    std::cout << idealPartition[i] << ' ';
                std::cout << std::endl;
                for(int i = 0; i < fileCount; ++i)
                    outputFile(supportFileNames[i]);
                ////
                *supportFiles[minIndex] >> idealPartition[minIndex];
            }
            *supportFiles[fileCount - 1] << INT_MIN << ' ';
            std::cout << "end iteration\n" << std::endl;
        }
        assert(false);
        --level;
        supportFiles[fileCount - 1]->close();
        supportFiles[fileCount - 2]->close();
        supportFiles[fileCount - 1]->open(supportFileNames[fileCount - 1], std::ios_base::in);
        supportFiles[fileCount - 2]->open(supportFileNames[fileCount - 2], std::ios_base::out);
        //TODO: SWAP
        return;//////////////////////////////////////////////////////////////////
    }
    
    for(int i = 0; i < fileCount; ++i) {
        delete supportFiles[i];
    }
    delete [] supportFiles;
    
}
 
 */


