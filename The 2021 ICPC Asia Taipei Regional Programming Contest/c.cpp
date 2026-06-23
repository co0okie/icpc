#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, e;

struct Residents {
    // bool hasWorked = 0;
    char name[17];
    ll l, r;
    list<pair<ll, list<ll>::iterator>> nodes;
};

vector<Residents> residents;
ll residents_size = 0;

struct Node {
    list<ll> residents;
    ll maxResidentId = -1;
};

vector<Node> nodes;

template <template <typename...> class C, class... T>
ostream& operator<<(ostream& o, const C<T...>& c) {
    o << "["; auto sep = "";
    for (auto& x : c) { o << sep << x; sep = ", "; }
    return o << "]";
}

ll id(ll l, ll r) {
    return (l + r) | (l != r);
}

ll newcome(ll sl, ll sr, ll ul, ll ur) {
    // cout << residents.size() << ": [" << sl << ":" << sr << "] [" << ul << ":" << ur << "]" << endl;
    ll i = id(sl, sr);
    if (ul <= sl && sr <= ur) {
        nodes[i].residents.push_back(residents_size);
        nodes[i].maxResidentId = residents_size;
        auto it = nodes[i].residents.end();
        residents[residents_size].nodes.push_back({i, --it});
    } else {
        ll sm = (sl + sr) / 2;
        if (ul <= sm) newcome(sl, sm, ul, ur);
        if (ur > sm) newcome(sm + 1, sr, ul, ur);
        nodes[i].maxResidentId = residents_size;
    }
    return i;
}

ll work(ll sl, ll sr, ll ql, ll qr) {
    ll i = id(sl, sr);
    // cout << "work: [" << sl << ":" << sr << "] [" << ql << ":" << qr << "]" << endl;
    // cout << i << ": max = " << nodes[i].maxResidentId << ", residents = " << nodes[i].residents << endl;
    auto& n = nodes[i];
    if (ql <= sl && sr <= qr) {
        // cout << "lazy" << endl;
        return n.maxResidentId;
    }
    ll sm = (sl + sr) / 2;
    ll s = n.residents.size() ? n.residents.back() : -1;
    if (ql <= sm) s = max(s, work(sl, sm, ql, qr));
    if (sm < qr) s = max(s, work(sm + 1, sr, ql, qr));
    // cout << "[" << sl << ":" << sr << "].maxResidentId = " << n.maxResidentId << ", " << s << endl;
    return s;
}
// ll work(ll sl, ll sr, ll ql, ll qr) {
//     ll i = id(sl, sr);
//     // cout << "work: [" << sl << ":" << sr << "] [" << ql << ":" << qr << "]" << endl;
//     // cout << i << ": max = " << nodes[i].maxResidentId << ", residents = " << nodes[i].residents << endl;
//     auto& n = nodes[i];
//     if (ql <= sl && sr <= qr && n.maxResidentId != -1 && !residents[n.maxResidentId].hasWorked) {
//         // cout << "lazy" << endl;
//         return n.maxResidentId;
//     }
//     while (n.residents.size() && residents[n.residents.back()].hasWorked)
//         n.residents.pop_back();
//     auto maxSegResidentId = n.residents.size() ? n.residents.back() : -1;
//     if (sl == sr) {
//         // cout << "leaf" << endl;
//         return n.maxResidentId = maxSegResidentId;
//     }
//     ll sm = (sl + sr) / 2;
//     ll s = maxSegResidentId;
//     auto &n1 = nodes[id(sl, sm)], &n2 = nodes[id(sm + 1, sr)];
//     n.maxResidentId = max({maxSegResidentId, n1.maxResidentId, n2.maxResidentId});
//     if (ql <= sl && sr <= qr && n.maxResidentId != -1 && !residents[n.maxResidentId].hasWorked) {
//         return n.maxResidentId;
//     }
//     if (ql <= sm) s = max(s, work(sl, sm, ql, qr));
//     if (sm < qr) s = max(s, work(sm + 1, sr, ql, qr));
//     // cout << "[" << sl << ":" << sr << "].maxResidentId = " << n.maxResidentId << ", " << s << endl;
//     return s;
// }

void leave(ll sl, ll sr, ll ul, ll ur) {
    // cout << residents.size() << ": [" << sl << ":" << sr << "] [" << ul << ":" << ur << "]" << endl;
    ll i = id(sl, sr);
    auto& n = nodes[i];
    ll sm = (sl + sr) / 2;
    if (ul <= sl && sr <= ur) {
    } else {
        if (ul <= sm) leave(sl, sm, ul, ur);
        if (ur > sm) leave(sm + 1, sr, ul, ur);
    }
    n.maxResidentId = n.residents.size() ? n.residents.back() : -1;
    if (sl == sr) return;
    auto &n1 = nodes[id(sl, sm)], &n2 = nodes[id(sm + 1, sr)];
    n.maxResidentId = max({n.maxResidentId, n1.maxResidentId, n2.maxResidentId});
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> e;
    nodes.resize(2 * n);
    residents.reserve(e / 2);
    while (e--) {
        int i; cin >> i;
        if (i == 1) {
            // cout << "newcome" << endl;
            ll a, b;
            residents.push_back({});
            auto& r = residents.back();
            cin >> r.name >> r.l >> r.r;
            newcome(0, n - 1, r.l, r.r);
            residents_size++;
        } else if (i == 2) {
            // cout << "work" << endl;
            ll c, d;
            cin >> c >> d;
            auto resident_id = work(0, n - 1, c, d);
            if (resident_id == -1) {
                cout << ">_<\n";
            } else {
                auto& r = residents[resident_id];
                cout << r.name << '\n';
                for (auto& [i, it] : r.nodes) {
                    // cout << "remove " << i << " " << *it << endl;
                    nodes[i].residents.erase(it);
                }
                leave(0, n - 1, r.l, r.r);
                // residents[resident_id].hasWorked = 1;
            }
        }
    }
}
