class Solution {
public:
    // 2D memoization table to store minimum cuts for substring s[i..j]
    int isit[2001][2001];

    // Recursive function to calculate minimum cuts needed for s[i..j]
    int hlo(string &s, int i, int j, vector<vector<int>>& dp) {
        // Base case: if the substring is empty or a single character, no cut needed
        if (i >= j) {
            return 0;
        }

        // If the entire substring s[i..j] is a palindrome, no cut is needed
        if (dp[i][j])
            return 0;

        // Return memoized result if already computed
        if (isit[i][j] != -1)
            return isit[i][j];

        int mainans = INT_MAX;

        // Try every possible partition point p from i to j
        for (int p = i; p <= j; p++) {
            // If s[i..p] is a palindrome, solve the rest recursively
            if (dp[i][p]) {
                // Count one cut and solve left and right substrings
                mainans = min(mainans, 1 + hlo(s, i, p, dp) + hlo(s, p + 1, j, dp));
            }
        }

        // Store result in memo table
        isit[i][j] = mainans;
        return mainans;
    }

    int minCut(string &s) {
        int n = s.length();

        // dp[i][j] = 1 if s[i..j] is a palindrome
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // All substrings of length 1 are palindromes
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;

        // Check palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1])
                dp[i][i + 1] = 1;
            else
                dp[i][i + 1] = 0;
        }

        // Check palindromes of length >= 3
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                // s[i..j] is palindrome if s[i] == s[j] and s[i+1..j-1] is palindrome
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = 1;
                }
            }
        }

        // Initialize memoization table with -1
        memset(isit, -1, sizeof(isit));

        // If the entire string is already a palindrome, no cuts needed
        if (dp[0][n - 1])
            return 0;

        // Call the recursive function to c
