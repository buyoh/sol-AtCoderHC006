#include "header.hpp"

//

int N, C;
vector<array<int, 3>> items; // <value, weight, index>

//

void input() {
  scanner >> N >> C;
  items.clear();
  repeat(i, N) {
    int v, w;
    scanner >> v >> w;
    items.push_back({v, w, i});
  }
}

vector<int> solve() {
  vector<int> selectedItems;
  sort(all(items));
  int totalWeight = 0;
  iterate(it, items.rbegin(), items.rend()) {
    auto &item = *it;
    totalWeight += item[1];
    if (totalWeight > C) {
      totalWeight -= item[1];
      break;
    }
    selectedItems.push_back(item[2]);
  }
  return selectedItems;
}

int calcScore(const vector<int> &selectedItems) {
  int total = 0;
  for (auto i : selectedItems) {
    for (auto &item : items) {
      if (item[2] == i) {
        total += item[0];
      }
    }
  }
  return total;
}

int main() {
  input();
  auto ans = solve();
  printer.join(all(ans));
  printer << "\n";
  clog << calcScore(ans) << endl;
  return 0;
}
