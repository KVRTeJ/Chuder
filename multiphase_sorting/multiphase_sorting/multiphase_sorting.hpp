#ifndef multiphase_sorting_hpp
#define multiphase_sorting_hpp

#include <iostream>
#include <fstream>

class MultiphaseSort {
private:
    struct File;
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
    int m_split(); //TODO: void -> int //return level && intMinCounter //TODO: intMinCounter
    void m_merge(int level); //TODO: в разбиении считаем уровень и передаем в слияние
    
private:
    std::string m_originFileName = "";
    std::ifstream m_originFile;
    int m_fileCount = 0;
    std::vector<File> m_supportFiles; //std::move для r-value
};



struct MultiphaseSort::File {
    std::string name = "";
    std::fstream supportFile;
    int idealPartition = 0;
    int missingSegments = 0;
};



#endif /* multiphase_sorting_hpp */
