#include <bits/stdc++.h>
#include <queue>

using namespace std;
using pii = pair<int, int>;
using ll = long long;
using pli = pair<ll, int>;

int N, M;

int main() {
	cin >> N >> M;

	vector<vector<int>> edges(M, vector<int>(3));

	// we store indicies of edges instead of weight
	vector<vector<pii>> nadj(N, vector<pii>());
	// a->b through edge c
	for (int i = 0; i < M; i++) {
		int a, b, c; cin >> a >> b >> c; a--; b--;
		edges[i][0] = a;
		edges[i][1] = b;
		edges[i][2] = c;

		nadj[a].push_back({b, i});
		nadj[b].push_back({a, i});
	}

	vector<vector<int>> eadj(M, vector<int>());
	for (int i = 0; i < M; i++) {
		int a = edges[i][0]; int b = edges[i][1];

		for (pii nb : nadj[a]) {
			if (nb.first == b) continue;
			eadj[nb.second].push_back(i);
		}
		for (pii nb : nadj[b]) {
			if (nb.first == a) continue;
			eadj[nb.second].push_back(i);
		}
	}

	vector<ll> minD(M, LLONG_MAX/2);
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	for (pii nb : nadj[0]) {
		minD[nb.second] = edges[nb.second][2];
		pq.push({edges[nb.second][2], nb.second});
	}

	while (!pq.empty()) {
		ll d = pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (minD[cur] < d) {
			continue;
		}

		for (int nb : eadj[cur]) {
			ll newD = d + abs(edges[cur][2] - edges[nb][2]);
			if (newD < minD[nb]) {
				minD[nb] = newD;
				pq.push({newD, nb});
			}
		}
	}

	ll ans = INT_MAX;

	for (pii nb : nadj[N-1]) {
		ans = min(ans, minD[nb.second]);
	}

	cout << ans << endl;

	return 0;
}
