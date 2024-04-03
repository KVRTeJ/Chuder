#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "Binary_Tree.hpp"

class SearchTree : public BinaryTree {
public:
    SearchTree() = default;
    ~SearchTree() override = default;
    
    int max() const override;//TODO: перегрузить не их а приватные методы -> их в protected для remove
    int min() const override;
    
    int level(const int key) const override;
    
    bool remove(const int key) override {return false;} //TODO: implement me
    
    SearchTree copy(Node* tree); //TODO: implement me

    Node* find(const int key) const override;
    
    std::vector<int> toVector() const override; //TODO: правильная реализация? (можно передавать лямбду в аргмуенты, в бинарном дереве сортировка, а тут nullpttr)
    
    SearchTree& operator = (const SearchTree& other) = default;
    
private:
    Node* add(Node* root, const int value) override;
    
    
    
};

#endif /* BinarySearchTree_hpp */
