#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, p, q;

struct Team {
    ll id;
    vector<ll> fail = vector<ll>(p, 0);
    vector<ll> time = vector<ll>(p, -1);
    ll point = 0;
    ll time_sum = 0;
};

int main() {
    cin >> n >> p >> q;

    vector<Team> teams(n);

    for (int i = 0; i < n; i++) {
        teams[i].id = i + 1;
    }

    for (ll _ = q; _--;) {
        ll m, id, t, v;
        cin >> m >> id >> t >> v;
        id--; t--;
        auto& team = teams[id];
        if (team.time[t] == -1) {
            if (v) {
                team.time[t] = m;
            } else {
                team.fail[t]++;
            }
        }
    }

    for (auto& team : teams) {
        team.point = count_if(team.time.begin(), team.time.end(), [](ll a) {
            return a != -1;
        });
        team.time_sum = 0;
        for (int i = 0; i < p; i++) {
            if (team.time[i] != -1) {
                team.time_sum += 20 * team.fail[i] + team.time[i];
            }
        }
    }

    ranges::sort(teams, [](Team& t1, Team& t2) {
        return t1.point != t2.point ?
            t1.point > t2.point :
            t1.time_sum != t2.time_sum ?
            t1.time_sum < t2.time_sum :
            t1.id < t2.id;
    });

    int rank = 0;
    for (int i = 0; i < n; i++) {
        auto team = teams[i];
        if (teams[rank].point != team.point || teams[rank].time_sum != team.time_sum) rank = i;
        cout << rank + 1 << " " << team.id << " " << team.point << " " << team.time_sum << "\n";
    }
}