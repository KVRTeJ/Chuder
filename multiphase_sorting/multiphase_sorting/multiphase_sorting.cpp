#include <algorithm>
#include <cstdio>

#include "multiphase_sorting.hpp"

void MultiphaseSort::setFileCount(const int value) {
    if(value <= 2) {
        std::cerr << "MultiphaseSort::setFileCount: file count must be > 2. File count = 3. . . " << std::endl;
        m_fileCount = 3;
    }
    m_fileCount = value;
    
    m_supportFiles.resize(m_fileCount);
}

void MultiphaseSort::setFileName(const std::string& fileName) {
    m_originFileName = fileName;
}

void MultiphaseSort::sort() {
    m_allocateFileType();
    
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
        m_supportFiles[i].supportFile->open(m_supportFiles[i].name, std::ios_base::out);
        if(!m_supportFiles[i].supportFile->is_open()) {
            std::cerr << "MultiphaseSort::sort(): can't open file named: " << m_supportFiles[i].name << ". . ." << std::endl;
            return;
        }
        m_supportFiles[i].idealPartition = 1;
        m_supportFiles[i].missingSegments = 1;
    }
    m_supportFiles[m_fileCount - 1].supportFile->open(m_supportFiles[m_fileCount - 1].name, std::ios_base::out);
    if(!m_supportFiles[m_fileCount - 1].supportFile->is_open()) {
        std::cerr << "MultiphaseSort::sort(): can't open file named: " << m_supportFiles[m_fileCount - 1].name << ". . ." << std::endl;
        return;
    }
    m_supportFiles[m_fileCount - 1].idealPartition = 0;
    m_supportFiles[m_fileCount - 1].missingSegments = 0;
    
    Data data;
    data.level = 1;
    data.intMinCounter = 0;
    
    m_split(data);
    m_merge(data);
    
    for(int i = 0; i < m_fileCount - 1; ++i) {
        m_supportFiles[i].supportFile->close();
        remove(m_supportFiles[i].name.data());
    }
    m_supportFiles[m_fileCount - 1].supportFile->close();
    std::rename(m_supportFiles[m_fileCount - 1].name.data(), "result.txt");
    
    m_deAllocateFileType();
}

void MultiphaseSort::outputFile(const std::string& fileName) {
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

bool MultiphaseSort::isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream origin(fileName, std::ios_base::in);
    if(!origin.is_open()) {
        std::cerr << "isFileContainsSortedArray: can't open file named: " << fileName << ". . ." << std::endl;
        return false;
    }
    
    int current = 0, next = 0;
    
    while(origin >> current) {
        origin >> next;
        if(next < current){
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

void MultiphaseSort::m_allocateFileType() {
    for(auto it = m_supportFiles.begin(); it != m_supportFiles.end(); ++it)
        it->supportFile = new std::fstream;
}

void MultiphaseSort::m_deAllocateFileType() {
    for(auto it = m_supportFiles.begin(); it != m_supportFiles.end(); ++it) {
        delete it->supportFile;
        it->supportFile = nullptr;
    }
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


int MultiphaseSort::findMinElementIndex() {
    int result = 0;
    while(m_supportFiles[result].idealPartition == INT_MIN)
        ++result;
    if(result >= m_fileCount - 1)
        return -1;
    for(int i = result + 1; i < m_fileCount - 1; ++i) {
        if(m_supportFiles[result].idealPartition > m_supportFiles[i].idealPartition && m_supportFiles[i].idealPartition != INT_MIN)
            result = i;
    }
    
    return result;
}

MultiphaseSort::Data MultiphaseSort::m_split(Data& data) {
    {
        auto processingIntMin {
            [this](Data& data, int& buffer){
                if(buffer == INT_MIN) {
                    ++data.intMinCounter;
                    if(m_originFile)
                        m_originFile >> buffer;
                }
            }
        };
        
        int i = 0;
        int firstIdealPartition = 0;
        int current = 0;
        int next = 0;
        bool hasCurrent = false;
        while(m_originFile) {
            if(hasCurrent) {
                current = next;
                *(m_supportFiles[i].supportFile) << current << ' ';
            }
            else {
                m_originFile >> current;
                processingIntMin(data, current);
                *(m_supportFiles[i].supportFile) << current << ' ';
            }
            m_originFile >> next;
            processingIntMin(data, next);
            while(m_originFile && current < next) {
                current = next;
                m_originFile >> next;
                processingIntMin(data, next);
                *(m_supportFiles[i].supportFile) << current << ' ';
            }
            hasCurrent = true;
            *(m_supportFiles[i].supportFile) << INT_MIN << ' ';
            --m_supportFiles[i].missingSegments;
            
            if(!m_originFile) {
                m_originFile.close();
                for(int i = 0; i < m_fileCount; ++i) {
                    m_supportFiles[i].supportFile->close();
                }
                break;
            }
            
            if(m_supportFiles[i].missingSegments < m_supportFiles[i + 1].missingSegments) {
                ++i;
            }
            
            else if(m_supportFiles[i].missingSegments == 0) {
                ++data.level;
                firstIdealPartition = m_supportFiles[0].idealPartition;
                i = 0;
                for(int k = 0; k < m_fileCount - 1; ++k) {
                    m_supportFiles[k].missingSegments = m_supportFiles[k + 1].idealPartition - m_supportFiles[k].idealPartition + firstIdealPartition;
                    m_supportFiles[k].idealPartition = m_supportFiles[k + 1].idealPartition + firstIdealPartition;
                }
            }
            
            else {
                i = 0;
            }
            
        }
    }
    
    return data;
}

bool MultiphaseSort::m_peekSegmentsFromFiles() {
    for(int i = m_fileCount - 2; i >= 0; --i) {
        if(m_supportFiles[i].missingSegments) {
            --m_supportFiles[i].missingSegments;
            m_supportFiles[i].idealPartition = INT_MIN;
        }
        
        else {
            *(m_supportFiles[i].supportFile) >> m_supportFiles[i].idealPartition;
            if(!(*m_supportFiles[i].supportFile)) {
                return false;
            }
        }
    }
    return true;
}

void MultiphaseSort::m_merge(Data& data) {
    for(int i = 0; i < m_fileCount - 1; ++i) {
        m_supportFiles[i].idealPartition = INT_MIN;
        m_supportFiles[i].supportFile->close();
        m_supportFiles[i].supportFile->open(m_supportFiles[i].name, std::ios_base::in);
    }
    m_supportFiles[m_fileCount - 1].idealPartition = INT_MIN;
    m_supportFiles[m_fileCount - 1].supportFile->close();
    m_supportFiles[m_fileCount - 1].supportFile->open(m_supportFiles[m_fileCount - 1].name, std::ios_base::out);
    
    bool hasFictitiousSegment = true;
    while(data.level != 0) {
        while((*m_supportFiles[m_fileCount - 2].supportFile)) {
            
            for(int m = 0; m < m_fileCount - 1; ++m) {
                hasFictitiousSegment &= static_cast<bool>(m_supportFiles[m].missingSegments);
            }
            
            while(hasFictitiousSegment) {
                hasFictitiousSegment = false;
                for(int m = 0; m < m_fileCount - 1; ++m) {
                    --m_supportFiles[m].missingSegments;
                    hasFictitiousSegment &= static_cast<bool>(m_supportFiles[m].missingSegments);
                }
                ++m_supportFiles[m_fileCount - 1].missingSegments;
            }
            
            if(!m_peekSegmentsFromFiles())
                break;
            
            for(int minIndex = findMinElementIndex(); minIndex != -1;
                minIndex = findMinElementIndex()) {
                *(m_supportFiles[m_fileCount - 1].supportFile) << m_supportFiles[minIndex].idealPartition << ' ';
                *(m_supportFiles[minIndex].supportFile) >> m_supportFiles[minIndex].idealPartition;
            }
            *(m_supportFiles[m_fileCount - 1].supportFile) << INT_MIN << ' ';
        }
        --data.level;
        m_supportFiles[m_fileCount - 1].supportFile->close();
        m_supportFiles[m_fileCount - 1].supportFile->open(m_supportFiles[m_fileCount - 1].name, std::ios_base::in);
        
        m_supportFiles[m_fileCount - 2].supportFile->close();
        m_supportFiles[m_fileCount - 2].supportFile->open(m_supportFiles[m_fileCount - 2].name, std::ios_base::out);
        
        std::swap(m_supportFiles[0], m_supportFiles[m_fileCount - 1]);
        for(int i = m_fileCount - 1; i > 1; --i) {
            std::swap(m_supportFiles[i], m_supportFiles[i - 1]);
        }
    }
    
    while(data.intMinCounter != 0) {
        *(m_supportFiles[m_fileCount - 1].supportFile) << INT_MIN << ' ';
        --data.intMinCounter;
    }
    
    while(*(m_supportFiles[0].supportFile) >> m_supportFiles[0].idealPartition) {
        if(m_supportFiles[0].idealPartition != INT_MIN)
            *(m_supportFiles[m_fileCount - 1].supportFile) << m_supportFiles[0].idealPartition << ' ';
    }
    
}
