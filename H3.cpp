#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::pair;

class RMQ {
 public:
  explicit RMQ(vector<int> a) {
    int count_lines = int(ceil(log2(a.size())));
    int count_elements = a.size();

    sparse_table.resize(count_lines, vector<pair<int, int>>(count_elements));

    for (int i = 0; i < count_elements; i++) {
      sparse_table[0][i] = {a[i], a[i]};
    }

    for (int i = 1; i < count_lines; i++) {
      for (int j = 0; j < count_elements - (1 << i) + 1; ++j) {
        sparse_table[i][j] = GetPairsStats(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int GetSecondStat(int left, int right) {
    int number = int(ceil(log2(right - left + 1)));

    return GetPairsStats(sparse_table[number - 1][left],
                         sparse_table[number - 1][right - (1 << (number - 1)) + 1]).second;
  }

 private:

  static pair<int, int> GetPairsStats(pair<int, int> pair1, pair<int, int> pair2) {
    vector<int> values{pair1.first, pair1.second, pair2.first, pair2.second};
    int stat1 = 1e9, stat2 = 1e9;

    for (int i = 0; i < values.size(); i++) {
      if (values[i] < stat1) {
        stat1 = values[i];
      }
    }
    for (int i = 0; i < values.size(); i++) {
      if (values[i] < stat2 && values[i] != stat1) {
        stat2 = values[i];
      }
    }

    return {stat1, stat2};
  }

  vector<vector<pair<int, int>>> sparse_table;
};

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> input(N);
  for (int i = 0; i < N; i++) {
    cin >> input[i];
  }

  RMQ rmq(input);

  for (int i = 0; i < M; ++i) {
    int left, right;
    cin >> left >> right;
    left--;
    right--;
    cout << rmq.GetSecondStat(left, right) << "\n";
  }
}