#ifndef multiphase_sorting_hpp
#define multiphase_sorting_hpp

#include <iostream>
#include <fstream>
#include <vector>

class MultiphaseSort {
private:
    struct File;
    struct Data;
public:
    MultiphaseSort() = default;
    
    int getFileCount() const {return m_fileCount;};
    void setFileCount(const int value);
    std::string getFileName() const {return m_originFileName;};
    void setFileName(const std::string& fileName);
    
    void sort();
    void outputFile(const std::string& fileName) const;
    bool isFileContainsSortedArray(const std::string &fileName) const;
    
private:
    std::vector<std::string> m_generateSupportFileNames() const;
    bool m_setSupportFileNames(const std::vector<std::string>& fileNames);
    int findMinElementIndex();
    Data m_split(Data& data);
    bool m_peekSegmentsFromFiles();
    void m_merge(Data& data);
    
private:
    std::string m_originFileName = "";
    std::ifstream m_originFile;
    int m_fileCount = 0;
    std::vector<File> m_supportFiles;
};



struct MultiphaseSort::File {
    std::string name = "";
    std::fstream supportFile;
    int idealPartition = 0;
    int missingSegments = 0;
};

struct MultiphaseSort::Data {
    int level = 0;
    int intMinCounter = 0;
};



#endif /* multiphase_sorting_hpp */
