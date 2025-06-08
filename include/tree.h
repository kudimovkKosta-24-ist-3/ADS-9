// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

// Узел дерева
struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;

    explicit Node(char val);
};

// Класс дерева перестановок
class PMTree {
 private:
    std::shared_ptr<Node> root;
    int permutation_count_;

    void BuildSubtree(std::shared_ptr<Node> node,
        const std::vector<char>& remaining);

 public:
    explicit PMTree(const std::vector<char>& symbols);

    std::shared_ptr<Node> GetRoot() const;
    int GetPermutationCount() const;

    static void CollectPermutations(const std::shared_ptr<Node>& node,
        std::vector<char>& path,
        std::vector<std::vector<char>>& result);
    friend void CountPermutationsImpl(const std::shared_ptr<Node>& node,
        int& count);

    friend std::vector<std::vector<char>> GetAllPerms(PMTree& tree);
    friend std::vector<char> GetPerm1(PMTree& tree, int num);
    friend std::vector<char> GetPerm2(PMTree& tree, int num);
};

std::vector<std::vector<char>> GetAllPerms(PMTree& tree);
std::vector<char> GetPerm1(PMTree& tree, int num);
std::vector<char> GetPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
