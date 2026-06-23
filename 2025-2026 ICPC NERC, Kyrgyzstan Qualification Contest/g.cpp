#include <bits/stdc++.h>
using namespace std;

string A, B, C;

char a2n[26];
char n2a[10];

void guess(string* s, char pos) {
    if (pos >= s->size()) {
        if (s == &B) return;
        else guess(&B, pos);
    }
    
    for (char d = 0; d < 10; d++) {
        if (pos == s->size() - 1 && d == 0) continue;
    }
}

int main() {
    cin >> A >> B >> C;
    for (auto& c : A) c -= 'A';
    for (auto& c : B) c -= 'A';
    for (auto& c : C) c -= 'A';
    ranges::reverse(A);
    ranges::reverse(B);
    ranges::reverse(C);
}