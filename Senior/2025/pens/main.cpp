#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, M, Q;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);

  cin >> N >> M >> Q;

  vector<int> pretty(N);
  vector<int> color(N);
  vector<map<int, int>> cmap(M);
  map<int, int> maxes;
  map<int, int> nmaxes;
  ll sum = 0;

  for (int i = 0; i < N; i++) {
    int c, p; cin >> c >> p; c--;
    color[i] = c;
    pretty[i] = p;
    cmap[c][p]++;
  }

  for (int i = 0; i < M; i++) {
    auto it = cmap[i].rbegin();

    maxes[it->first]++;
    sum += it->first;
    if (it->second > 1) {
      nmaxes[it->first] += it->second-1;
    }

    it++;
    while (it != cmap[i].rend()) {
      nmaxes[it->first] += it->second;
      it++;
    }
  }

  cout << (sum + max(0, (0 - maxes.begin()->first + (nmaxes.size() > 0 ? nmaxes.rbegin()->first : 0)))) << endl;

  for (int i = 0; i < Q; i++) {
    int q; cin >> q;
    int t; cin >> t; t--;
    int c = color[t];
    int p = pretty[t];

    if (q == 1) {
      // color change
      int newC; cin >> newC; newC--;
      
      int oldCMax = cmap[c].rbegin()->first;
      cmap[c][p]--;
      if (cmap[c][p] == 0) cmap[c].erase(p);
      int newCMax = cmap[c].rbegin()->first;

      // newCMax must be equal to or smaller than oldCMax
      bool pWasMax = false;
      if (newCMax < oldCMax) {
        pWasMax = true;
        sum += newCMax - oldCMax;
        maxes[oldCMax]--;
        if (maxes[oldCMax] == 0) maxes.erase(oldCMax);

        nmaxes[newCMax]--;
        if (nmaxes[newCMax] == 0) nmaxes.erase(newCMax);
        maxes[newCMax]++;
      }

      int oldNewCMax = cmap[newC].rbegin()->first;
      cmap[newC][p]++;
      int newNewCMax = cmap[newC].rbegin()->first;

      // newNewCMax must be equal to or greater than oldNewCMax
      if (newNewCMax > oldNewCMax) {
        sum += newNewCMax - oldNewCMax;
        maxes[oldNewCMax]--;
        if (maxes[oldNewCMax] == 0) maxes.erase(oldNewCMax);
        maxes[newNewCMax]++;
        nmaxes[oldNewCMax]++;

        if (!pWasMax) {
          nmaxes[p]--;
          if (nmaxes[p] == 0) nmaxes.erase(p);
        }
      } else {
        if (pWasMax) {
          nmaxes[p]++;
        }
      }

      color[t] = newC;
    } else {
      // pretty change
      int newP; cin >> newP;

      int oldCMax = cmap[c].rbegin()->first;
      bool pIsMax = (p == oldCMax);

      cmap[c][p]--;
      if (cmap[c][p] == 0) cmap[c].erase(p);

      cmap[c][newP]++;

      int newCMax = cmap[c].rbegin()->first;
      bool newPIsMax = (newP == newCMax);

      if (oldCMax != newCMax) {
        sum += newCMax - oldCMax;
        maxes[newCMax]++;
        maxes[oldCMax]--;
        if (maxes[oldCMax] == 0) maxes.erase(oldCMax);

        if (pIsMax != newPIsMax) {
          if (newPIsMax) {
            nmaxes[p]--;
            if (nmaxes[p] == 0) nmaxes.erase(p);
            nmaxes[oldCMax]++;
          } else {
            nmaxes[newCMax]--;
            if (nmaxes[newCMax] == 0) nmaxes.erase(newCMax);
            nmaxes[newP]++;
          }
        }
      } else {
        nmaxes[p]--;
        if (nmaxes[p] == 0) nmaxes.erase(p);
        nmaxes[newP]++;
      }

      pretty[t] = newP;
    }

    // calculation
    cout << (sum + max(0, (0 - maxes.begin()->first + (nmaxes.size() > 0 ? nmaxes.rbegin()->first : 0)))) << endl;
  }

  return 0;
}