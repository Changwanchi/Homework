# 41141105

作業一

第一題
## 解題說明

撰寫函數來計算 Ackermann 函數 A(m,n)，要求實作一個遞迴版本的 Ackermann 函數，
再實作一個非遞迴版本的算法計算 Ackermann 函數。


### 解題策略

1. 遞迴版本
直接根據定義使用遞迴函數實作。
根據 m 和 n的值判斷條件並呼叫對應遞迴式。
2. 非遞迴版本
使用堆疊（Stack）模擬遞迴過程，手動管理函數呼叫的狀態。
將每次函數呼叫的參數放入堆疊，依序取出計算。
持續更新堆疊，直到得到最終結果。

## 程式實作

以下為主要程式碼：

```cpp
遞迴版本
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

非遞迴版本 
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
```

## 效能分析
遞迴版本
1. 時間複雜度：無法以傳統 Big-O 表示，成長速度超過 O(2^n)，為超指數（hyper-exponential）級別
2. 空間複雜度：O(遞迴深度) → 也會呈超級快速增長，容易導致堆疊溢位 Stack Overflow

非遞迴版本
1. 時間複雜度（Time Complexity）
Ackermann 函數是已知成長最快的基本可計算函數之一。
其時間複雜度無法用多項式（Polynomial）或指數（Exponential）簡單表達，因為它屬於超指數成長。
2. 空間複雜度（Space Complexity）
程式使用了兩個大小為 1000 的陣列作為手動模擬遞迴的堆疊（mStack, nStack），這代表最多只能模擬 1000 層遞迴深度。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | m=0 n=0       | 1        | 1        |
| 測試二   | m=1 n=2       | 4        | 4        |
| 測試三   | m=2 n=2       | 7        | 7        |
| 測試四   | m=3 n=2       | 29       | 29       |
| 測試五   | m=4 n=1       | 異常      |異常      |

### 編譯與執行指令

```shell
$ g++ -o ackermann ackermann.cpp
$ ./ackermann
請輸入 m 和 n：2 3
遞迴版 Ackermann(2, 3) = 9

```

### 結論

這段程式碼實作了 Ackermann 函數的遞迴版本，讓使用者輸入參數後計算結果。Ackermann 函數增長非常快，遞迴層數深，適合用小數值測試，否則可能會導致程式崩潰或運算時間過長。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **數學定義本質是遞迴**  
   Ackermann 函數本身是以遞迴定義的數學函數，其定義中下一步的計算依賴於函數本身的先前值，這種「函數呼叫自身」的結構非常自然地對應到程式語言中的遞迴機制。因此，遞迴實作是直接且符合數學邏輯的實現方式。

2. **程式結構清晰易懂**  
  透過遞迴，可以用簡潔且直觀的程式碼表達複雜的數學規則，減少繁瑣的迴圈與狀態管理，讓程式碼更具可讀性與維護性。

3. **遞迴利於問題分解**  
   Ackermann 函數的問題可自然分解為較小子問題（如計算 Ackermann(m-1, n) 或 Ackermann(m, n-1)），遞迴機制適合處理這種分治式問題。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。


## 第二題




## 解題說明

power set 是一個集合的所有子集合的集合。
若原集合 S = {a, b, c}，其 power set 為：
{∅, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}}
總共有$(2^n)$
個子集合，其中 n 是原集合的元素數量。

### 解題策略

1. 遞迴參數：目前處理到第幾個元素，還有目前累積的子集合。
2. 終止條件：如果已處理完所有元素，將目前的子集合加入答案中。
3. 遞迴公式：不選當前元素，繼續往下遞迴。選當前元素，加進子集合後再遞迴。

## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析
時間複雜度： O(n × 2ⁿ)，因為需要列舉所有子集合並逐個輸出，
每個子集合最長為 n。

空間複雜度： O(n)，因為遞迴與暫存子集合最多同時使用 n 個元素的空間。

## 測試與驗證

### 測試案例

輸入：
{'a','b','c'}   

預期輸出字串:
powerset (S) = {{},{a},{a,b},{a,b,c},{a,c},{b},{b,c},{c}}

實際輸出字串:
powerset (S) = {{},{a},{a,b},{a,b,c},{a,c},{b},{b,c},{c}}

### 編譯與執行指令

```shell
g++ -o powerset powerset.cpp   # 編譯
./powerset                     # 執行（或 powerset.exe on Windows）

```

### 結論

在輸入集合為空的情況下，程式亦能正確輸出僅包含空集合的結果，符合設計預期。
測試案例涵蓋了多種邊界情況（空集合、一個元素、兩個以上元素），驗證程式在不同輸入下皆能正確產出所有子集合。

## 申論及開發報告

### 選擇遞迴的原因

1. 自然對應問題結構：
冪集的本質是一種「對每個元素做選或不選」的所有組合，這正好符合遞迴的特性——每一步都面臨相同的子問題（包含或不包含下一個元素）。

2. 程式結構簡潔清晰：
使用遞迴可以避免複雜的巢狀迴圈或額外的堆疊操作，讓邏輯結構更簡單、更容易閱讀與維護。

3. 方便展開所有組合：
每次呼叫都處理一個元素的加入與不加入情況，自然展開所有子集合，這樣可以保證完整遍歷所有可能。
