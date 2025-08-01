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