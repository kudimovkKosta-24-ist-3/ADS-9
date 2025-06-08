// Copyright 2022 NNTU-CS
#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory>

struct Node {
  char value;
  std::vector<std::shared_ptr<Node>> children;

  explicit Node(char val);
};

class PMTree {
 private:
  std::shared_ptr<Node> root;
  int permutation_count_;

  void BuildSubtree(std::shared_ptr<Node> node,
                    const std::vector<char>& remaining);
  void CountPermutations(std::shared_ptr<Node> node, int& count) const;

 public:
  explicit PMTree(const std::vector<char>& symbols);

  std::shared_ptr<Node> GetRoot() const;
  int GetPermutationCount() const;

  static void CollectPermutations(const std::shared_ptr<Node>& node,
                                  std::vector<char>& path,
                                  std::vector<std::vector<char>>& result);

  friend bool FindNthPermutation(PMTree& tree,
                                 const std::shared_ptr<Node>& node,
                                 std::vector<char>& path,
                                 std::vector<char>& result,
                                 int& current_num,
                                 int target_num);
};

std::vector<std::vector<char>> GetAllPerms(PMTree& tree);
std::vector<char> GetPerm1(PMTree& tree, int num);
std::vector<char> GetPerm2(PMTree& tree, int num);

#endif  // TREE_H
