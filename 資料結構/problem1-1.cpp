#include <iostream>
using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackermann_recursive(m - 1, 1);
    } else {
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
    }
}

int main() {
    int m = 2, n = 3;  // 直接帶入值
    int result = ackermann_recursive(m, n);
    cout << "遞迴版 Ackermann(" << m << ", " << n << ") = " << result << endl;
    return 0;
}