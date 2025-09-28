#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {1, 2, 3};  // 示例数组
    
    // 先排序（必须步骤，确保生成所有排列）
    std::sort(arr.begin(), arr.end());
    
    // 输出所有排列组合
    do {
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    } while (std::next_permutation(arr.begin(), arr.end()));
    
    return 0;
}