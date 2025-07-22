#include <iostream>
using namespace std;

int ackermann_non_recursive(int m, int n) {
    int mStack[1000];
    int nStack[1000];
    int top = -1;

    top++;
    mStack[top] = m;
    nStack[top] = n;

    while (top >= 0) {
        m = mStack[top];
        n = nStack[top];
        top--;

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            top++;
            mStack[top] = m - 1;
            nStack[top] = 1;
            continue;
        } else {
            top++;
            mStack[top] = m - 1;

            top++;
            mStack[top] = m;
            nStack[top] = n - 1;
            continue;
        }

        if (top >= 0) {
            m = mStack[top];
            top--;
            top++;
            mStack[top] = m;
            nStack[top] = n;
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "請輸入 m 和 n：";
    cin >> m >> n;

    int result = ackermann_non_recursive(m, n);
    cout << "非遞迴版 Ackermann(" << m << ", " << n << ") = " << result << endl;

    return 0;
}