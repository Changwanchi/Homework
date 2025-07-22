#include <iostream>
#include <vector>

// 輸出一個子集合
void printSet(const std::vector<char>& set) {
    std::cout << "{";
    for (size_t i = 0; i < set.size(); ++i) {
        std::cout << set[i];
        if (i < set.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}";
}

// 遞迴產生冪集
void powerSetRecursive(std::vector<char>& currentSet,
                       const std::vector<char>& originalSet,
                       int startIndex,
                       bool& isFirst) {
    if (!isFirst) std::cout << ", ";
    printSet(currentSet);
    isFirst = false;

    for (int i = startIndex; i < originalSet.size(); ++i) {
        currentSet.push_back(originalSet[i]);
        powerSetRecursive(currentSet, originalSet, i + 1, isFirst);
        currentSet.pop_back();
    }
}

// 計算冪集
void computePowerSet(const std::vector<char>& S) {
    std::cout << "powerset (S) = {";
    std::vector<char> currentSet;
    bool isFirst = true;
    powerSetRecursive(currentSet, S, 0, isFirst);
    std::cout << "}\n";
}

int main() {
    computePowerSet({'a', 'b', 'c'});
    return 0;
}