# Leetcode-132.-Palindrome-Partitioning-II

# Palindrome Partitioning II - LeetCode 132

## Problem Statement

Given a string `s`, partition `s` such that every substring of the partition is a **palindrome**. Return the **minimum number of cuts** needed to partition `s`.

---

## 🚀 Approaches

This document covers **three elegant approaches** to solve LeetCode 132 using recursion, backtracking, and dynamic programming (DP).

---

### ✅ Approach 1: Backtracking with Substrings (Count by Partition Size)

**Intuition:**
Recursively try all possible palindromic partitions. Count number of cuts as `partition size - 1`.

```cpp
class Solution {
public:
    int mainans = 10000;

    void hlo(string &s, int i, vector<string>& small, vector<vector<int>>& dp) {
        if (i >= s.length()) {
            int b = small.size() - 1;
            mainans = min(mainans, b);
            return;
        }
        for (int j = i; j < s.length(); j++) {
            if (dp[i][j]) {
                small.push_back(s.substr(i, j - i + 1));
                hlo(s, j + 1, small, dp);
                small.pop_back();
            }
        }
    }

    int minCut(string &s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int i = 0; i < n - 1; i++) if (s[i] == s[i + 1]) dp[i][i + 1] = 1;
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) dp[i][j] = 1;
            }
        }
        vector<string> small;
        hlo(s, 0, small, dp);
        return mainans;
    }
};
```

**Complexity:**

* Time: Exponential (backtracking all paths)
* Space: O(n\*n) for `dp`

---

### ✅ Approach 2: Backtracking with Integer Cut Count (No Substring Storage)

**Intuition:**
Avoid using substring vectors and directly track cut count during recursion.

```cpp
class Solution {
public:
    int mainans = 1000;

    void hlo(string &s, int i, vector<vector<int>>& dp, int count) {
        if (i >= s.length()) {
            mainans = min(mainans, count - 1);
            return;
        }
        for (int j = i; j < s.length(); j++) {
            if (dp[i][j]) {
                hlo(s, j + 1, dp, count + 1);
            }
        }
    }

    int minCut(string &s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int i = 0; i < n - 1; i++) if (s[i] == s[i + 1]) dp[i][i + 1] = 1;
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) dp[i][j] = 1;
            }
        }
        hlo(s, 0, dp, 0);
        return mainans;
    }
};
```

**Advantage:** Cleaner logic with less memory overhead.

---

### ✅ Approach 3: DP with Memoized Recursive Cuts

**Intuition:**
Use full dynamic programming with memoization to avoid recomputation. For each `s[i..j]`, if it's not a palindrome, try all cuts `p` and choose the one with minimum cuts.

```cpp
class Solution {
public:
    int isit[2001][2001];

    int hlo(string &s, int i, int j, vector<vector<int>>& dp) {
        if (i >= j) return 0;
        if (dp[i][j]) return 0;
        if (isit[i][j] != -1) return isit[i][j];

        int mainans = INT_MAX;
        for (int p = i; p <= j; p++) {
            if (dp[i][p]) {
                mainans = min(mainans, 1 + hlo(s, i, p, dp) + hlo(s, p + 1, j, dp));
            }
        }
        return isit[i][j] = mainans;
    }

    int minCut(string &s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int i = 0; i < n - 1; i++) if (s[i] == s[i + 1]) dp[i][i + 1] = 1;
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) dp[i][j] = 1;
            }
        }

        memset(isit, -1, sizeof(isit));
        if (dp[0][n - 1]) return 0;
        return hlo(s, 0, n - 1, dp);
    }
};
```

**Advantage:** Optimal in terms of overlapping subproblems.

**Complexity:**

* Time: \~O(n^3)
* Space: O(n^2)

---

## 🧠 Conclusion

All three approaches solve the same problem using recursion, DP, and backtracking. The choice of approach depends on:

* **Approach 1 & 2**: Conceptual clarity, useful for interview understanding.
* **Approach 3**: Optimal for performance.

---

## ✍️ Author

**Ridham Garg**

---

Let me know if you want visual diagrams or test case walkthroughs added!
