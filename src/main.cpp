// Copyright 2022 NNTU-CS
#include "tree.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Функции измерения времени
long long MeasureGetAllPerms(PMTree& tree) {
    auto start = std::chrono::high_resolution_clock::now();
    GetAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long MeasureGetPerm1(PMTree& tree, int num) {
    auto start = std::chrono::high_resolution_clock::now();
    GetPerm1(tree, num);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long MeasureGetPerm2(PMTree& tree, int num) {
    auto start = std::chrono::high_resolution_clock::now();
    GetPerm2(tree, num);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::default_random_engine generator;
    std::cout << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";

    for (int n = 1; n <= 8; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) {
            symbols.push_back('1' + i);
        }

        PMTree tree(symbols);
        int total_perms = tree.GetPermutationCount();

        std::uniform_int_distribution<int> dist(1, total_perms);
        int random_num = dist(generator);

        long long time_all = MeasureGetAllPerms(tree);
        long long time_1 = MeasureGetPerm1(tree, random_num);
        long long time_2 = MeasureGetPerm2(tree, random_num);

        std::cout << n << "\t" << time_all << "\t" << time_1 << "\t" << time_2 << "\n";
    }

    return 0;
}
