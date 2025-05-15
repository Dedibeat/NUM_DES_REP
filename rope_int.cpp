#include <ext/rope>
#include <bits/stdc++.h>
using namespace __gnu_cxx;
using namespace std;
using uint = unsigned int;
rope<char> r;
void put_at(int pos, uint x) {
    char s[4];
    for (int i = 0; i < 4; ++i) {
        s[i] = static_cast<char>(x & 0xFF);
        x >>= 8;
    }
    r.insert(pos * 4, s, 4);
}
uint get_at(int pos) {
    uint ret = 0;
    for (int i = 3; i >= 0; --i) {
        ret <<= 8;
        ret |= static_cast<unsigned char>(r.at(pos * 4 + i));
    }
    return ret;
}
