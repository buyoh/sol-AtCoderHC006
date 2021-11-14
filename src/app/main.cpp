#include "header.hpp"

//

const int N = 1000;
const int M = 50;

//

struct Task {
  P src;
  P dst;
  void input() { scanner >> src.x >> src.y >> dst.x >> dst.y; }
};

void optimize_dfs(int v, int from, const GraphE &graph, vector<int> &visited) {
  if (v != M * 2) // kitanai
    visited.push_back(v);
  for (auto ei : graph.vertex_to[v]) {
    auto to = graph.edges[ei].to(v);
    if (from == to)
      continue;
    optimize_dfs(to, v, graph, visited);
  }
}

pair<int, vector<P>> optimize(const vector<Task> &tasks,
                              const vector<int> &task_idxs) {
  assert(task_idxs.size() >= M);
  if (task_idxs.size() > M) {
    auto ti = task_idxs;
    ti.resize(M);
    return optimize(tasks, ti);
  }
  vector<const Task *> taskis;
  taskis.reserve(M);
  for (int i : task_idxs)
    taskis.emplace_back(&tasks[i]);

  // TODO: consider start and end
  const int kBaseIdx = M * 2;

  priority_queue<pair<int, pair<int, int>>> eque; // len, vu
  repeat(i, M) {
    eque.emplace(-taskis[i]->src.distM(P{400, 400}), // * 100 - rand(0, 99)
                 make_pair(i * 2, kBaseIdx));
    eque.emplace(-taskis[i]->src.distM(taskis[i]->dst), // * 100 + rand(0, 99)
                 make_pair(i * 2, i * 2 + 1));
    iterate(j, i + 1, M) {
      eque.emplace(-taskis[i]->src.distM(taskis[j]->src), // * 100 + rand(0, 99)
                   make_pair(i * 2, j * 2));
      eque.emplace(-taskis[i]->src.distM(taskis[j]->dst), // * 100 + rand(0, 99)
                   make_pair(i * 2, j * 2 + 1));
      eque.emplace(-taskis[i]->dst.distM(taskis[j]->src), // * 100 + rand(0, 99)
                   make_pair(i * 2 + 1, j * 2));
      eque.emplace(-taskis[i]->dst.distM(taskis[j]->dst), // * 100 + rand(0, 99)
                   make_pair(i * 2 + 1, j * 2 + 1));
    }
  }
  GraphE graph(M * 2 + 1); // <src,dst,src,dst,...>
  Unionfind uf(M * 2 + 1);
  while (!eque.empty() && uf.size(0) < M * 2 + 1) {
    auto w = -eque.top().first;
    auto p = eque.top().second;
    eque.pop();
    if (uf.connect(p.first, p.second)) {
      graph.connect(p.first, p.second, w);
    }
  }

  vector<int> visited;
  // せめて最初の1つはsrcを選びたいが…
  optimize_dfs(kBaseIdx, -1, graph, visited);

  vector<int> routei;
  vector<bool> picked(M, false);
  vector<int> reroute_idxs;

  P curr{400, 400};
  routei.push_back(M * 2);
  // route.push_back(curr);
  for (auto i : visited) {
    int ti = i >> 1;
    bool isDst = i & 1;
    P next;
    if (isDst) {
      if (picked[ti]) {
        // ok
        next = taskis[ti]->dst;
      } else {
        // まだpickしていないので再度巡回する必要あり
        reroute_idxs.push_back(i);
        continue;
      }
    } else {
      next = taskis[ti]->src;
      picked[ti] = true;
    }
    curr = next;
    // route.push_back(curr);
    routei.push_back(i);
  }
  routei.push_back(M * 2);

  // vector<int> rereroute_idxs;
  for (auto i : reroute_idxs) {
    int ti = i >> 1;
    // bool isDst = i & 1;

    P p = taskis[ti]->dst;

    int pi = 0;
    while (routei[pi] != ti * 2)
      ++pi;
    int besti = -1; // besti の後に i を挿入する
    // int bestcost = numeric_limits<int>::max() / 2;
    for (; routei[pi] != M * 2; ++pi) {
      //
      int bi = routei[pi];
      int ai = routei[pi + 1];
      P b = (bi & 1) ? taskis[bi / 2]->dst : taskis[bi / 2]->src;
      P a = ai == M * 2 ? P{400, 400}
                        : (ai & 1) ? taskis[ai / 2]->dst : taskis[ai / 2]->src;
      int cost = b.distM(p) + p.distM(a) - b.distM(a);
      if (cost == 0) {
        besti = pi;
        break;
      }
    }
    if (besti == -1) {
      besti = pi - 1;
    }
    auto it = routei.begin();
    advance(it, pi + 1);
    routei.insert(it, i);
    assert(*routei.rbegin() == M * 2);
  }

  vector<P> route;
  int total_cost = 0;
  route.reserve(routei.size());
  {
    P c{400, 400};
    for (auto i : routei) {
      P p = i == M * 2 ? P{400, 400}
                       : (i & 1) ? taskis[i / 2]->dst : taskis[i / 2]->src;
      total_cost += c.distM(p);
      route.push_back(p);
    }
  }
  return make_pair(total_cost, route);
}

vector<int> resizedVec(vector<int> v, int m) {
  v.resize(m);
  v.shrink_to_fit();
  return v;
}

int main() {
  vector<Task> tasks;
  tasks.resize(N);
  repeat(i, N) tasks[i].input();

  vector<int> idxs(N);
  iota(all(idxs), 0);
  sort(all(idxs), [&](int i, int j) {
    return max(tasks[i].src.distM(P{400, 400}),
               tasks[i].dst.distM(P{400, 400})) <
           max(tasks[j].src.distM(P{400, 400}),
               tasks[j].dst.distM(P{400, 400}));
  });

  idxs.resize(M * 2);
  auto best = optimize(tasks, idxs);
  auto best_idxs = idxs;

  {

    int loopcount = 0;
    Timer timer;
    int temperature = 0;
    int tl = 100;
    int tim;
    while ((tim = timer.toc()) < 1950) {
      // move to neighbor
      int pi = rand(0, M - 1);
      int pj = rand(M, M * 2 - 1);
      swap(idxs[pi], idxs[pj]);

      auto curr = optimize(tasks, idxs);
      if (curr.first < best.first) {
        best = curr;
        best_idxs = idxs;
        temperature = 0;
      } else {
        if (++temperature > 20) { //  + 0*tim/2000 // ???
          temperature = 0;
          idxs = best_idxs;
        }
      }
      // analysis: 1200 ms 辺りで頭打ってる
      if (tl < tim) {
        tl += 100;
        clog << "score: " << best.first << endl;
      }
      ++loopcount;
    }
    clog << "loopcount: " << loopcount << endl;
  }

  best_idxs.resize(M);
  cout << M << ' ';
  repeat(i, M) cout << best_idxs[i] + 1 << ' ';
  cout << endl;

  cout << best.second.size();
  for (auto xy : best.second) {
    cout << " " << xy.x << " " << xy.y;
  }
  cout << endl;
  clog << best.first << endl;

  return 0;
}
