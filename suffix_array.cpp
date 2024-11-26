#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class SuffixArray {
public:
    string s;
    vector<int> sa;    // Suffix array
    vector<int> lcp;   // Longest Common Prefix array

    SuffixArray(const string& str) : s(str + '$') {
        build_sa();
        build_lcp();
    }

    // Build the suffix array
    void build_sa() {
        int n = s.size();
        vector<int> rank(n), temp_sa(n), temp_rank(n), cnt(max(256, n), 0);
        sa.resize(n);

        // Initial ranking based on characters
        for (int i = 0; i < n; ++i) {
            rank[i] = s[i];
            sa[i] = i;
        }

        for (int k = 1; k < n; k <<= 1) {
            // Counting sort based on second key
            counting_sort(sa, rank, k);
            // Counting sort based on first key
            counting_sort(sa, rank, 0);

            temp_rank[sa[0]] = 0;
            int r = 0;
            for (int i = 1; i < n; ++i) {
                if (rank[sa[i]] != rank[sa[i - 1]] ||
                    rank[(sa[i] + k) % n] != rank[(sa[i - 1] + k) % n])
                    ++r;
                temp_rank[sa[i]] = r;
            }
            rank = temp_rank;
            if (rank[sa[n - 1]] == n - 1)
                break;
        }
    }

    // Build the LCP array
    void build_lcp() {
        int n = s.size();
        vector<int> rank(n, 0);
        lcp.resize(n, 0);

        for (int i = 0; i < n; ++i)
            rank[sa[i]] = i;

        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (rank[i] > 0) {
                int j = sa[rank[i] - 1];
                while (i + h < n && j + h < n && s[i + h] == s[j + h])
                    ++h;
                lcp[rank[i]] = h;
                if (h > 0)
                    --h;
            }
        }
    }

    // Function to perform counting sort based on rank and offset k
    void counting_sort(vector<int>& sa, const vector<int>& rank, int k) {
        int n = sa.size();
        int max_rank = max(256, n);
        vector<int> cnt(max_rank, 0), temp_sa(n);

        for (int i = 0; i < n; ++i)
            cnt[(i + k < n) ? rank[i + k] : 0]++;
        for (int i = 1; i < max_rank; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int idx = (sa[i] + k < n) ? rank[sa[i] + k] : 0;
            temp_sa[--cnt[idx]] = sa[i];
        }
        sa = temp_sa;
    }

    // Function to search for a pattern in the text
    bool search(const string& pattern) {
        int n = s.size();
        int m = pattern.size();
        int left = 0, right = n - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            string substr = s.substr(sa[mid], min(n - sa[mid], m));
            if (substr.compare(0, m, pattern) == 0)
                return true;
            if (substr < pattern)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }

    // Additional functions can be added as needed
};

int main() {
    string s;
    cout << "Enter the string to build the Suffix Array: ";
    cin >> s;

    SuffixArray sa(s);

    cout << "Suffix Array:\n";
    for (int i = 0; i < sa.sa.size(); ++i)
        cout << sa.sa[i] << " " << sa.s.substr(sa.sa[i]) << endl;

    cout << "\nLCP Array:\n";
    for (int i = 1; i < sa.lcp.size(); ++i)
        cout << sa.lcp[i] << endl;

    string pattern;
    cout << "Enter a pattern to search: ";
    cin >> pattern;
    if (sa.search(pattern))
        cout << "Pattern exists in the original string." << endl;
    else
        cout << "Pattern does not exist in the original string." << endl;

    return 0;
}
