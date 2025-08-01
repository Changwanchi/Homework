# 41141105

作業二

## 解題說明

本題要求實作一個多項式（Polynomial）類別，其抽象資料型態（ADT）與私有資料成員已在題目圖中給出。需要根據這些結構設計對應的 C++ 類別，並實作多項式的輸入與輸出功能。輸入與輸出需透過運算子多載（operator overloading）來實作 >> 與 <<，使得多項式可以用類似內建資料型態的方式來輸入與輸出。

### 解題策略

定義資料結構來儲存每一項的係數與指數：
例如建立 Term 結構，包含 coefficient（係數）與 exponent（指數）兩個成員變數。

在 Polynomial 類別中使用陣列或 vector 儲存多個 Term：
同時加上 termCount 成員變數來紀錄實際的項數。

多載運算子 >> 以遞迴或迴圈方式輸入多項式每一項：
提示使用者輸入每一項的係數與指數，重複輸入 termCount 次。
多載運算子 << 輸出多項式格式：
以格式化方式列印每一項，注意：
正負號顯示
次數為 0 或 1 的特例處理
最後不要多印 "+" 號
主程式中建立 Polynomial 物件，並使用 >> 和 << 操作物件：
驗證整體輸入與輸出是否符合題意。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

class Polynomial {
private:
    int degree;
    int* coef;

public:
    // 建構子
    Polynomial(int d = 0) {
        degree = d;
        coef = new int[d + 1];
        for (int i = 0; i <= degree; i++) {
            coef[i] = 0;
        }
    }

    // 拷貝建構子
    Polynomial(const Polynomial& other) {
        degree = other.degree;
        coef = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coef[i] = other.coef[i];
        }
    }

    // 解構子
    ~Polynomial() {
        delete[] coef;
    }

    // 輸入運算子
    friend istream& operator>>(istream& in, Polynomial& p) {
        cout << "Enter degree: ";
        in >> p.degree;
        delete[] p.coef;
        p.coef = new int[p.degree + 1];
        for (int i = p.degree; i >= 0; i--) {
            cout << "Enter coefficient for x^" << i << ": ";
            in >> p.coef[i];
        }
        return in;
    }

    // 輸出運算子
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        bool first = true;
        for (int i = p.degree; i >= 0; i--) {
            if (p.coef[i] != 0) {
                if (!first && p.coef[i] > 0)
                    out << " + ";
                else if (p.coef[i] < 0)
                    out << " - ";

                if (abs(p.coef[i]) != 1 || i == 0)
                    out << abs(p.coef[i]);

                if (i > 0)
                    out << "x";
                if (i > 1)
                    out << "^" << i;

                first = false;
            }
        }
        if (first)
            out << "0";
        return out;
    }

    // 加法運算子
    Polynomial operator+(const Polynomial& other) const {
        int max_deg = max(degree, other.degree);
        Polynomial result(max_deg);

        for (int i = 0; i <= max_deg; i++) {
            int a = (i <= degree) ? coef[i] : 0;
            int b = (i <= other.degree) ? other.coef[i] : 0;
            result.coef[i] = a + b;
        }
        return result;
    }

    // 乘法運算子
    Polynomial operator*(const Polynomial& other) const {
        int new_deg = degree + other.degree;
        Polynomial result(new_deg);

        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= other.degree; j++) {
                result.coef[i + j] += coef[i] * other.coef[j];
            }
        }
        return result;
    }

    // 帶入 x 值
    int evaluate(int x) const {
        int result = 0;
        for (int i = 0; i <= degree; i++) {
            result += coef[i] * (int)pow(x, i);
        }
        return result;
    }
};

int main() {
    Polynomial p1, p2;

    cout << "Input first polynomial:\n";
    cin >> p1;

    cout << "\nInput second polynomial:\n";
    cin >> p2;

    cout << "\nPolynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial prod = p1 * p2;

    cout << "\nSum: " << sum << endl;
    cout << "Product: " << prod << endl;

    int x;
    cout << "\nEnter a value for x: ";
    cin >> x;

    cout << "P1(" << x << ") = " << p1.evaluate(x) << endl;
    cout << "P2(" << x << ") = " << p2.evaluate(x) << endl;

    return 0;
}

```

## 效能分析

1. 加法時間複雜度：O(n)，其中 n 為最大階數。

   乘法時間複雜度：O(n^2)，因為每項與另一多項式全部項相乘。


2. 空間複雜度：O(n)，儲存係數陣列。

## 測試與驗證

### 測試案例
 1. 測試一

 ```
Input first polynomial:
Enter degree: 3
Enter coefficient for x^3: 2
Enter coefficient for x^2: 1
Enter coefficient for x^1: 5
Enter coefficient for x^0: 8

Input second polynomial:
Enter degree: 4
Enter coefficient for x^4: 3
Enter coefficient for x^3: 2
Enter coefficient for x^2: 1
Enter coefficient for x^1: 3
Enter coefficient for x^0: 4

Polynomial 1: 2x^3 + x^2 + 5x + 8
Polynomial 2: 3x^4 + 2x^3 + x^2 + 3x + 4

Sum: 3x^4 + 4x^3 + 2x^2 + 8x + 12
Product: 6x^7 + 7x^6 + 19x^5 + 41x^4 + 32x^3 + 27x^2 + 44x + 32

Enter a value for x: 6
P1(6) = 506
P2(6) = 4378
```

2.  測試二
```
 Input first polynomial:
Enter degree: 5
Enter coefficient for x^5: 9
Enter coefficient for x^4: 8
Enter coefficient for x^3: 7
Enter coefficient for x^2: 6
Enter coefficient for x^1: 5
Enter coefficient for x^0: 4

Input second polynomial:
Enter degree: 6
Enter coefficient for x^6: 9
Enter coefficient for x^5: 8
Enter coefficient for x^4: 7
Enter coefficient for x^3: 6
Enter coefficient for x^2: 5
Enter coefficient for x^1: 4
Enter coefficient for x^0: 3

Polynomial 1: 9x^5 + 8x^4 + 7x^3 + 6x^2 + 5x + 4
Polynomial 2: 9x^6 + 8x^5 + 7x^4 + 6x^3 + 5x^2 + 4x + 3

Sum: 9x^6 + 17x^5 + 15x^4 + 13x^3 + 11x^2 + 9x + 7
Product: 81x^11 + 144x^10 + 190x^9 + 220x^8 + 235x^7 + 236x^6 + 197x^5 + 140x^4 + 94x^3 + 58x^2 + 31x + 12

Enter a value for x: 5
P1(5) = 34179
P2(5) = 170898

```


### 編譯與執行指令

```shell
g++ -o polynomial polynomial.cpp

```

### 結論

這段程式成功實現了多項式類別的封裝設計與操作符重載應用，透過物件導向方式將多項式的邏輯整合進一個類別中，並支援多種常見運算（加法、乘法、代入值計算）。使用者可以直覺地進行輸入、運算與輸出，對於學習 C++ 類別、動態記憶體與運算子多載等核心觀念具有良好示範效果。

## 申論及開發報告

1. 建構與解構

   預設建構子：初始化多項式次數與動態分配記憶體空間。

   拷貝建構子：深拷貝確保物件之間互不干擾。

   解構子：釋放記憶體，防止記憶體洩漏。


2. 輸入與輸出運算子多載

   operator>> 允許用戶輸入多項式的次數與各項係數。

   operator<< 輸出格式化的多項式表示，包含正負號、次方顯示等排版處理。


3. 多項式的加法與乘法

   operator+：建立一個新多項式，其次數為兩者最大次數，對應次方逐項相加。

   operator*：
   進行分配律展開 $a_i x^i \cdot b_j x^j = (a_i b_j) x^{i+j}$，結果次數為兩者次數相加。

