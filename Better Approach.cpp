class Solution {
public:
    int mainans = 1000; // Stores the minimum number of cuts required to partition the string into palindromic substrings

    // Backtracking helper function to explore all palindromic partitions
    void hlo(string &s, int i, vector<vector<int>>& dp, int count) {
        // Base case: if we have reached the end of the string
        if (i >= s.length()) {
            // Update the answer with the minimum cuts found so far
            mainans = min(mainans, count - 1); // count-1 because no cut is needed after the last partition
            return;
        }

        // Try every possible end index j for the substring starting at i
        for (int j = i; j < s.length(); j++) {
            // If s[i..j] is a palindrome
            if (dp[i][j]) {
                // Recur for the remaining substring starting at j+1 and increase cut count
                hlo(s, j + 1, dp, count + 1);
            }
        }
    }

    int minCut(string &s) {
        int n = s.length();

        // dp[i][j] = 1 if the substring s[i..j] is a palindrome, 0 otherwise
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Every single character is a palindrome
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;

        // Check for palindromic substrings of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1])
                dp[i][i + 1] = 1;
            else
                dp[i][i + 1] = 0;
        }

        // Check for palindromic substrings of length >= 3 using dynamic programming
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                // s[i..j] is a palindrome if s[i] == s[j] and s[i+1..j-1] is also a palindrome
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = 1;
                }
            }
        }

        // Start recursive backtracking to explore all valid palindromic partitions
        hlo(s, 0, dp, 0);

        return mainans; // Return the minimum number of cuts
    }
};
