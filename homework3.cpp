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