// This solution finds the minimum number of cuts needed to partition a string
// such that every substring in the partition is a palindrome.

class Solution {
public:
    int mainans = 10000; // Stores the minimum number of cuts (initialized to a large number)

    // Recursive function to explore all palindromic partitions
    void hlo(string &s, int i, vector<string>& small, vector<vector<int>>& dp) {
        // Base case: if we reach the end of the string
        if (i >= s.length()) {
            int b = small.size() - 1; // Number of cuts is size - 1
            mainans = min(mainans, b); // Update minimum answer
            return;
        }
        // Try all substrings starting from index i
        for (int j = i; j < s.length(); j++) {
            // If substring s[i..j] is a palindrome
            if (dp[i][j]) {
                small.push_back(s.substr(i, j - i + 1)); // Choose the palindrome substring
                hlo(s, j + 1, small, dp);               // Recurse for the remaining string
                small.pop_back();                       // Backtrack
            }
        }
    }

    // Main function to compute the minimum number of cuts
    int minCut(string &s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0)); // dp[i][j] = 1 if s[i..j] is a palindrome

        // Initialize palindromes of length 1
        for (int i = 0; i < n; i++) dp[i][i] = 1;

        // Initialize palindromes of length 2
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1])
                dp[i][i + 1] = 1;
        }

        // Fill dp table for substrings of length >= 3
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = 1;
                }
            }
        }

        vector<string> small; // Stores the current list of palindrome substrings
        hlo(s, 0, small, dp); // Start recursive exploration

        return mainans; // Return the minimum number of cuts found
    }
};
