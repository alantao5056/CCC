#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

vector<vector<int>> deps;

int main() {
  // freopen("3.in", "r", stdin);
  // freopen("output.out", "w", stdout);

  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  vector<int> B(N);
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }

  vector<pii> ints;
  int start = 0;
  for (int i = 1; i < N; i++) {
    if (B[i] != B[start]) {
      ints.push_back({start, i-1});
      start = i;
    }
  }

  ints.push_back({start, N-1});

  int j = 0;
  bool works = true;
  
  vector<int> points;
  for (int i = 0; i < ints.size(); i++) {
    while (j < N && A[j] != B[ints[i].first]) {
      j++;
    }

    if (j == N) {
      works = false;
      break;
    }

    points.push_back(j++);
  }

  if (!works) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;

  vector<string> ans;
  for (int i = 0; i < points.size(); i++) {
    if (ints[i].first < points[i] && ints[i].second <= points[i]) {
      stringstream ss;
      ss << "L " << ints[i].first << " " << points[i];
      ans.push_back(ss.str());
    }
  }

  for (int i = points.size()-1; i >= 0; i--) {
    if (ints[i].first >= points[i] && ints[i].second > points[i]) {
      stringstream ss;
      ss << "R " << points[i] << " " << ints[i].second;
      ans.push_back(ss.str());
    }
  }

  for (int i = 0; i < points.size(); i++) {
    if (ints[i].first < points[i] && ints[i].second > points[i]) {
      stringstream ss;
      ss << "L " << ints[i].first << " " << points[i];
      ans.push_back(ss.str());
      stringstream ss2;
      ss2 << "R " << points[i] << " " << ints[i].second;
      ans.push_back(ss2.str());
    }
  }

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << endl;
  }

  return 0;
}
