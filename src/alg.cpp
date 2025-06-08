// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <memory>
#include "tree.h"

Node::Node(char val) : value(val) {}

PMTree::PMTree(const std::vector<char>& symbols)
    : root(std::make_shared<Node>('*')), permutation_count_(0) {
    if (symbols.empty()) return;

    permutation_count_ = 1;
    for (int i = 2; i <= static_cast<int>(symbols.size()); ++i) {
        permutation_count_ *= i;
    }

    std::vector<char> sorted_symbols = symbols;
    std::sort(sorted_symbols.begin(), sorted_symbols.end());

    BuildSubtree(root, sorted_symbols);
}

void PMTree::BuildSubtree(std::shared_ptr<Node> node,
    const std::vector<char>& remaining) {
    if (remaining.empty()) return;
    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        node->children.push_back(child);
        std::vector<char> next_remaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) {
                next_remaining.push_back(remaining[j]);
            }
        }
        BuildSubtree(child, next_remaining);
    }
}

std::shared_ptr<Node> PMTree::GetRoot() const {
    return root;
}

int PMTree::GetPermutationCount() const {
    return permutation_count_;
}

void PMTree::CollectPermutations(const std::shared_ptr<Node>& node,
    std::vector<char>& path,
    std::vector<std::vector<char>>& result) {
    if (!node->children.empty()) {
        for (const auto& child : node->children) {
            path.push_back(child->value);
            CollectPermutations(child, path, result);
            path.pop_back();
        }
    } else if (!path.empty()) {
        result.push_back(path);
    }
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    auto root = tree.GetRoot();
    if (root && !root->children.empty()) {
        PMTree::CollectPermutations(root, path, result);
    }
    return result;
}
void CountPermutationsImpl(const std::shared_ptr<Node>& node,
    int& count) {
    if (node->children.empty()) {
        count = 1;
        return;
    }
    count = 0;
    for (const auto& child : node->children) {
        int sub_count = 0;
        CountPermutationsImpl(child, sub_count);
        count += sub_count;
    }
}
bool FindNthPermutation(PMTree& tree,
    const std::shared_ptr<Node>& node,
    std::vector<char>& path,
    std::vector<char>& result,
    int& current_num,
    int target_num) {
    if (!node->children.empty()) {
        for (const auto& child : node->children) {
            path.push_back(child->value);
            int subtree_count = 0;
            CountPermutationsImpl(child, subtree_count);
            if (current_num + subtree_count >= target_num) {
                if (FindNthPermutation(tree, child, path,
                    result, current_num, target_num)) {
                    return true;
                }
            } else {
                current_num += subtree_count;
            }
            path.pop_back();
        }
    } else {
        if (!path.empty()) {
            if (current_num == target_num - 1) {
                result = path;
                return true;
            }
            ++current_num;
        }
    }
    return false;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    int total = tree.GetPermutationCount();
    if (num < 1 || num > total) return {};
    std::vector<std::vector<char>> all_perms = getAllPerms(tree);
    return all_perms[num - 1];
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> path;
    int current_num = 0;
    auto root = tree.GetRoot();
    if (root && num >= 1 && num <= tree.GetPermutationCount()) {
        FindNthPermutation(tree, root, path, result, current_num, num);
    }
    return result;
}
