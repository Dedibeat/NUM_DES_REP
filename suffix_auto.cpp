#include<bits/stdc++.h>

using namespace std;

struct State {
    int len;                        // Length of the longest substring
    int link;                       // Suffix link
    map<char, int> next;            // Transitions
    bool isClone;                   // Indicates if the state is a clone
    int firstPos;                   // Position of the first occurrence of the substring
    vector<int> invLink;            // Inverse links (used for counting occurrences)

    State() : len(0), link(-1), isClone(false), firstPos(-1) {}
};

class SuffixAutomaton {
public:
    vector<State> st;
    int size;
    int last;

    // Constructor to build the automaton from the given string
    SuffixAutomaton(const string& s) {
        st.reserve(2 * s.size());
        st.push_back(State());
        size = 1;
        last = 0;

        for (char c : s)
            sa_extend(c);
    }

    // Function to extend the automaton with character c
    void sa_extend(char c) {
        int cur = size++;
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].firstPos = st[cur].len - 1;

        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = size++;
                st.push_back(State());
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                st[clone].isClone = true;
                st[clone].firstPos = st[q].firstPos;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Function to check if a substring exists in the automaton
    bool substring_exists(const string& substr) {
        int current = 0;
        for (char c : substr) {
            if (!st[current].next.count(c))
                return false;
            current = st[current].next[c];
        }
        return true;
    }

    // Function to count the number of different substrings
    long long count_different_substrings() {
        long long result = 0;
        for (int i = 1; i < size; ++i)
            result += st[i].len - st[st[i].link].len;
        return result;
    }

    // Function to find the longest common substring between the initial string and another string
    int longest_common_substring(const string& t) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < t.size(); ++i) {
            char c = t[i];
            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next.count(c)) {
                v = st[v].next[c];
                ++l;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        // The longest common substring is t.substr(bestpos - best + 1, best)
        return best;
    }

    // Function to count occurrences of each substring (optional)
    vector<int> count_occurrences() {
        vector<int> occ(size, 0);
        vector<int> order(size);
        for (int i = 0; i < size; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [this](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int i = 0; i < size; ++i)
            occ[i] = st[i].isClone ? 0 : 1;
        for (int i : order) {
            if (st[i].link != -1)
                occ[st[i].link] += occ[i];
        }
        return occ;
    }
};

int main() {
    string s;
    cout << "Enter the string to build the Suffix Automaton: ";
    cin >> s;

    SuffixAutomaton sa(s);

    cout << "Number of different substrings: " << sa.count_different_substrings() << endl;

    string substr;
    cout << "Enter a substring to search: ";
    cin >> substr;
    if (sa.substring_exists(substr))
        cout << "Substring exists in the original string." << endl;
    else
        cout << "Substring does not exist in the original string." << endl;

    string t;
    cout << "Enter another string to find the longest common substring: ";
    cin >> t;
    int lcs_length = sa.longest_common_substring(t);
    cout << "Length of the longest common substring: " << lcs_length << endl;

    return 0;
}
