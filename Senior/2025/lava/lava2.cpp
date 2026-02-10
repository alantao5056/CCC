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
    if (b < a) swap(a, b);
		edges[i][0] = a;
		edges[i][1] = b;
		edges[i][2] = c;

		nadj[a].push_back({b, i});
		nadj[b].push_back({a, i});
	}

	vector<ll> minD(M, LLONG_MAX/2);
	priority_queue<pli, vector<pli>, greater<pli>> pq;
  for (int i = 0; i < M; i++) {
    if (edges[i][0] == 0) {
      minD[i] = edges[i][2];
      pq.push({edges[i][2], i});
    }
  }

	while (!pq.empty()) {
		ll d = pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (minD[cur] < d) {
			continue;
		}

    int a = edges[cur][0];
    int b = edges[cur][1];

    for (pii nb : nadj[a]) {
      int e = nb.second;
      if (e == cur) continue;
			ll newD = d + abs(edges[cur][2] - edges[e][2]);
			if (newD < minD[e]) {
				minD[e] = newD;
				pq.push({newD, e});
			}
		}

    for (pii nb : nadj[b]) {
      int e = nb.second;
      if (e == cur) continue;
			ll newD = d + abs(edges[cur][2] - edges[e][2]);
			if (newD < minD[e]) {
				minD[e] = newD;
				pq.push({newD, e});
			}
		}
	}

	ll ans = LLONG_MAX;

	for (pii nb : nadj[N-1]) {
		ans = min(ans, minD[nb.second]);
	}

	cout << ans << endl;

	return 0;
}

