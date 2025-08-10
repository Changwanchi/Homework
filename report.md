# 41141105

作業三

## 解題說明

本題要求實作一個 Polynomial 類別，用 帶頭節點的循環鏈表 來儲存與運算單變數整數係數多項式，並且實作多項式的基本功能與運算子重載

### 解題策略

這題的解題策略是利用帶頭節點的循環鏈表來儲存多項式的各項，鏈表節點包含係數與指數，並依指數降序插入，同指數時合併係數、若結果為 0 則刪除該節點。輸入時讀入 (coef, exp) 直到 exp = -1，輸出時依數學格式處理符號、省略 1 與 ^1 等細節。運算子重載部分，透過複製建構子與賦值運算子確保物件正確複製與清除，加法與減法直接插入對方多項式（減法將係數取負），乘法則以雙層迴圈逐項相乘並插入結果，多項式求值則遍歷鏈表計算每項 coef * pow(x, exp) 累加。整體流程先完成鏈表結構與插入邏輯，再依序實作輸入輸出、加減乘運算及求值，最後測試各功能以確保正確性。

## 程式實作

以下為主要程式碼：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

using namespace std;

// 節點結構：儲存整數係數與非負整數指數
struct Node {
    int coef;
    int exp;
    Node* next;
    Node(int c = 0, int e = 0, Node* n = nullptr) : coef(c), exp(e), next(n) {}
};

class Polynomial {
private:
    Node* head; // 帶頭節點，並且形成循環（head->next ... -> head）

    // 插入或合併一個項（保持指數由大到小，並合併相同指數）
    void insertTerm(int coef, int exp) {
        if (coef == 0) return;
        Node* prev = head;
        Node* cur = head->next;
        // 找到第一個指數小於等於 exp 的位置（要插在 prev->next 前）
        while (cur != head && cur->exp > exp) {
            prev = cur;
            cur = cur->next;
        }
        if (cur != head && cur->exp == exp) {
            // 合併係數
            cur->coef += coef;
            if (cur->coef == 0) {
                // 刪除節點
                prev->next = cur->next;
                delete cur;
            }
        } else {
            // 插入新節點在 prev 與 cur 之間
            Node* n = new Node(coef, exp, cur);
            prev->next = n;
        }
    }

public:
    // (e) 解析構析：將所有節點清掉
    ~Polynomial() {
        // 刪除所有資料節點再刪 head
        Node* cur = head->next;
        while (cur != head) {
            Node* t = cur;
            cur = cur->next;
            delete t;
        }
        delete head;
    }

    // (c) 複製建構子
    Polynomial(const Polynomial& a) {
        head = new Node(); // create head
        head->next = head;
        Node* cur = a.head->next;
        while (cur != a.head) {
            insertTerm(cur->coef, cur->exp);
            cur = cur->next;
        }
    }

    // 無參數建構子（建立空多項式）
    Polynomial() {
        head = new Node();
        head->next = head;
    }

    // (d) 賦值運算子
    Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this;
        // 先清除原本資料
        Node* cur = head->next;
        while (cur != head) {
            Node* t = cur;
            cur = cur->next;
            delete t;
        }
        head->next = head;
        // 複製 a 的內容
        cur = a.head->next;
        while (cur != a.head) {
            insertTerm(cur->coef, cur->exp);
            cur = cur->next;
        }
        return *this;
    }

    // (f) 多項式加法
    Polynomial operator+(const Polynomial& b) const {
        Polynomial res;
        // 先加入 this 的所有項
        Node* cur = head->next;
        while (cur != head) {
            res.insertTerm(cur->coef, cur->exp);
            cur = cur->next;
        }
        // 再加入 b 的所有項（insertTerm 會自動合併）
        cur = b.head->next;
        while (cur != b.head) {
            res.insertTerm(cur->coef, cur->exp);
            cur = cur->next;
        }
        return res;
    }

    // (g) 多項式減法
    Polynomial operator-(const Polynomial& b) const {
        Polynomial res;
        Node* cur = head->next;
        while (cur != head) {
            res.insertTerm(cur->coef, cur->exp);
            cur = cur->next;
        }
        cur = b.head->next;
        while (cur != b.head) {
            res.insertTerm(-cur->coef, cur->exp);
            cur = cur->next;
        }
        return res;
    }

    // (h) 多項式乘法
    Polynomial operator*(const Polynomial& b) const {
        Polynomial res;
        for (Node* aNode = head->next; aNode != head; aNode = aNode->next) {
            for (Node* bNode = b.head->next; bNode != b.head; bNode = bNode->next) {
                int newCoef = aNode->coef * bNode->coef;
                int newExp = aNode->exp + bNode->exp;
                res.insertTerm(newCoef, newExp);
            }
        }
        return res;
    }

    // (i) Evaluate 在 x 處評估，多項式係數為 int，但回傳 float
    float Evaluate(float x) const {
        float sum = 0.0f;
        for (Node* cur = head->next; cur != head; cur = cur->next) {
            // pow 可能回傳 double，轉 float
            sum += cur->coef * std::pow(x, cur->exp);
        }
        return sum;
    }

    // 幫助函式：測試/手動加入一個項（外部也可用）
    void addTerm(int c, int e) { insertTerm(c, e); }

    // (b) ostream << operator：將多項式轉成人類可讀形式輸出
    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        Node* cur = p.head->next;
        if (cur == p.head) {
            os << "0";
            return os;
        }
        bool first = true;
        while (cur != p.head) {
            int c = cur->coef;
            int e = cur->exp;
            if (!first) {
                if (c > 0) os << " + ";
                else os << " - ";
            } else {
                if (c < 0) os << "-";
            }
            int absC = (c < 0 ? -c : c);
            // 顯示係數（若係數為1或-1且次方非0，則僅顯示 x 部分）
            if (e == 0) {
                os << absC;
            } else {
                if (absC != 1) os << absC;
                os << "x";
                if (e != 1) os << "^" << e;
            }
            first = false;
            cur = cur->next;
        }
        return os;
    }

    // (a) istream >> operator：讀入多項式 (假設格式: n coef exp coef exp ...)
    friend istream& operator>>(istream& is, Polynomial& p) {
        // 讀入項數
        int n;
        if (!(is >> n)) return is;
        // 清空原本 p 中的資料
        Node* cur = p.head->next;
        while (cur != p.head) {
            Node* t = cur;
            cur = cur->next;
            delete t;
        }
        p.head->next = p.head;
        // 讀入 n 個 (coef exp) 對
        for (int i = 0; i < n; ++i) {
            int coef, exp;
            if (!(is >> coef >> exp)) break;
            p.insertTerm(coef, exp);
        }
        return is;
    }
};

// 範例 main：示範 a~i（可當作測試）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   
    Polynomial A;
    A.addTerm(5, 4);
    A.addTerm(-2, 2);
    A.addTerm(1, 0);

    Polynomial B;
    B.addTerm(1, 2);
    B.addTerm(3, 0);

    cout << "A = " << A << "\n";
    cout << "B = " << B << "\n";
    cout << "A + B = " << (A + B) << "\n";
    cout << "A - B = " << (A - B) << "\n";
    cout << "A * B = " << (A * B) << "\n";
    cout << "A(2.0) = " << (A.Evaluate(2.0f)) << "\n";

    return 0;
}
```

## 效能分析

1. 時間複雜度分析
	•	插入單項：需依指數降序搜尋插入位置，最壞 O(k)，k 為當前項數。
	•	輸入整個多項式：逐項插入，最壞 O(k²)。
	•	加法 / 減法：將兩多項式項依序插入新鏈表，最壞 O((m+n)²)，m、n 分別為兩多項式項數。
	•	乘法：雙層迴圈逐項相乘（m×n 次），每次插入最壞 O(k)，結果最壞可達 O(m²n²)。
	•	求值：遍歷一次鏈表 O(k)，但 pow() 計算增加常數時間開銷。

2. 空間複雜度分析
	•	儲存多項式：每項需係數、指數與指標，空間 O(k)。
	•	加減法：需建立新鏈表儲存結果，額外 O(m+n) 空間。
	•	乘法：最壞情況每對項都生成新項，需 O(mn) 空間，之後合併可減少。
	•	求值：額外空間僅常數級 O(1)，不隨項數增加。
## 測試與驗證

### 測試案例
 1. 測試一

 ```
    Polynomial A;
    A.addTerm(3, 2);
    A.addTerm(-1, 6);
    A.addTerm(2, 1);

    Polynomial B;
    B.addTerm(2, 6);
    B.addTerm(3, 2);

    cout << "A = " << A << "\n";
    cout << "B = " << B << "\n";
    cout << "A + B = " << (A + B) << "\n";
    cout << "A - B = " << (A - B) << "\n";
    cout << "A * B = " << (A * B) << "\n";
    cout << "A(2.0) = " << (A.Evaluate(2.0f)) << "\n";

 A = -x^6 + 3x^2 + 2x
 B = 2x^6 + 3x^2
 A + B = x^6 + 6x^2 + 2x
 A - B = -3x^6 + 2x
 A * B = -2x^12 + 3x^8 + 4x^7 + 9x^4 + 6x^3
 A(2.0) = -48
```


```


### 編譯與執行指令

```shell
g++ -std=c++17 -O2 -Wall main.cpp -o polynomial

```

### 結論

這題透過循環鏈結串列作為多項式的儲存結構，實作了輸入輸出、加減乘運算、評估、複製建構子、賦值運算子與解構子等功能，並在插入項時自動維持降冪排序與合併同次項，確保資料結構的一致性與運算正確性。由於鏈結串列能在運算過程中靈活插入與刪除節點，此設計在處理稀疏多項式與頻繁更新的情境下具備良好彈性，但相較於陣列結構，其遍歷與存取效能偏低。

## 申論及開發報告

1. 	運算子重載實作
	•	透過運算子重載（operator+、operator-、operator*、operator=）實現多項式的加、減、乘以及賦值操作，讓使用者可以用直觀的運算符號進行多項式運算。
	•	搭配輸入輸出運算子（operator>>、operator<<），實現多項式的格式化輸入與輸出。

2.	循環鏈結串列資料結構設計
	•	採用帶頭節點的循環鏈結串列，節點包含係數（coef）、指數（expn）與下一節點指標（next）。
	•	插入時依降冪排序並合併同次項，確保多項式結構有序且簡化後便於運算。

3.	動態記憶體與物件導向管理
	•	實作複製建構子與賦值運算子以進行深拷貝，避免多個物件共用同一鏈表導致資料錯亂。
	•	解構子負責釋放動態配置的節點記憶體，避免記憶體洩漏，確保程式穩定性。
