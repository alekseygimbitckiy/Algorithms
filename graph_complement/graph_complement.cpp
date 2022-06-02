#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;
vector<vector<int>> g(100001, vector<int>()), t(100001, vector<int>()),
    vertexInOrgraphComponent(100001, vector<int>());
vector<unordered_set<int>> c(100001, unordered_set<int>());
vector<unordered_set<int>> cr(100001, unordered_set<int>());
vector<unordered_set<int>> vertexInComponent(100001, unordered_set<int>());
vector<unordered_set<int>> vertexInComponentS(100001, unordered_set<int>());
vector<unordered_set<int>> vertexInComponentT(100001, unordered_set<int>());
vector<int> order;
vector<bool> useS(100001, false);
vector<bool> useT(100001, false);
vector<bool> use2(100001, true);
vector<bool> used2(100001, false);
stack<int> sC1;
unordered_set<int> sComponent;
unordered_set<int> tComponent;
vector<unordered_set<int>> stot(100001, unordered_set<int>());
int countS = 0;
int countT = 0;
bool used[100001];
bool used1[100001];
int component[100001];
int graphcomponent[100001];
int cnt_components = 1;
int cnt_components1 = 1;
int t1 = 0;
void dfs1(int v) {
  used[v] = true;
  for (size_t i = 0; i < g[v].size(); ++i) {
    if (!used[g[v][i]]) {
      dfs1(g[v][i]);
    }
  }
  order.push_back(v);
}
void dfs2(int v) {
  component[v] = cnt_components;
  vertexInOrgraphComponent[cnt_components].push_back(v);
  used[v] = false;
  for (size_t i = 0; i < t[v].size(); ++i) {
    if (used[t[v][i]]) {
      used[t[v][i]] = false;
      dfs2(t[v][i]);
    }
  }
}
void dfsS(int v, int t) {
  if (!t1) {
    stack<int> graphDfs;
    graphDfs.push(v);
    while (graphDfs.size() != 0) {
      t = graphDfs.top();
      graphDfs.pop();
      if (useT[t]) {
        if (!used2[t]) {
          if (tComponent.find(t) != tComponent.end()) {
            t1 = t;
            return;
          }
        }
      } else if (c[t].size() != 0) {
        for (int u : c[t]) {
          if (!used2[u]) {
            graphDfs.push(u);
          }
        }
      }
      used2[t] = true;
    }
  }
}
int main() {
  int n;
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  int v = -1;
  inFile >> n;
  for (int i = 1; i < n + 1; i++) {
    while (v != 0) {
      inFile >> v;
      if (v != 0) {
        g[i].push_back(v);
        t[v].push_back(i);
      } else {
        break;
      }
    }
    v = -1;
  }
  int countOrgraphComponent = 0;
  for (int i = 1; i < n + 1; i++) {
    if (!used[i]) {
      countOrgraphComponent++;
      dfs1(i);
    }
  }

  int condComponents = 0;
  for (int i = n - 1; i >= 0; i--) {
    v = order[i];
    if (component[v] == 0) {
      condComponents++;
      dfs2(v);
      cnt_components++;
    }
  } 

  int condComponents1 = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      if (component[i] != component[g[i][j]]) {
        c[component[i]].insert(component[g[i][j]]);//condense graph (alghoritm Kosaraju and Sharir)
        cr[component[g[i][j]]].insert(component[i]);
      }
    }
  }
  for (int v = 1; v <= condComponents; v++) {
    if (c[v].size() == 0) {
      vertexInComponentT[cnt_components1].insert(v);
      useT[v] = true;
      tComponent.insert(v);
      countT++;
    }
    if (cr[v].size() == 0) {
      vertexInComponentS[cnt_components1].insert(v);
      useS[v] = true;
      sComponent.insert(v);
      countS++;
    }
  }
  outFile << countS << '\n';
  bool endFor = false;
  vector<pair<int, int>> answer;
  vector<pair<int, int>> answerPair;
  countS = sComponent.size();
  if (condComponents > 1) {
    for (auto i = sComponent.begin(); i != sComponent.end(); i++) {
      dfsS(*i, *i);
      if (t1) {
        int t = t1;
        useT[t1] = false;
        useS[*i] = false;
        countS--;
        countT--;
        answerPair.push_back(make_pair(*i, t1));
      }
      t1 = 0;
    }
  } else {
    outFile << 0;
    return 0;
  }

  bool endFor1 = false;
  for (int i = 0; i < answerPair.size() && !endFor;) {
    if (i == answerPair.size() - 1) {
      int j = 0;
      answer.push_back(
          make_pair(vertexInOrgraphComponent[answerPair[i].second][0],
                    vertexInOrgraphComponent[answerPair[j].first][0]));
      endFor = true;
    } else {
      answer.push_back(
          make_pair(vertexInOrgraphComponent[answerPair[i].second][0],
                    vertexInOrgraphComponent[answerPair[i + 1].first][0]));
    }
    i++;
  }
  vector<int> sNotC;
  vector<int> tNotC;
  int cInC;
  if (answer.size() > 0) {
    cInC = answer[0].first;
  } else {
    outFile << 1 << '\n';
  }
  countT = 0;
  for (int i = 0; i < useT.size(); i++) {
    if (useT[i]) {
      tNotC.push_back(i);
      countT++;
    }
  }
  countS = 0;
  for (int i = 0; i < useS.size(); i++) {
    if (useS[i]) {
      sNotC.push_back(i);
      countS++;
    }
  }
  int j = 0;
  for (int i = 0; i < tNotC.size() && i < sNotC.size(); i++) {
    if (i > n + 1) {
      int y = tNotC[-1];
    }
    answer.push_back(make_pair(vertexInOrgraphComponent[tNotC[i]][0],
                               vertexInOrgraphComponent[sNotC[i]][0]));
    countS--;
    countT--;
    j++;
  }
  if (countS <= 0) {
    if (countT > 0) {
      for (; j < tNotC.size(); j++) {
        answer.push_back(
            make_pair(vertexInOrgraphComponent[tNotC[j]][0], cInC));
        countT--;
      }
    }
  } else if (countT <= 0) {
    if (countS > 0) {
      for (; j < sNotC.size(); j++) {
        answer.push_back(
            make_pair(cInC, vertexInOrgraphComponent[sNotC[j]][0]));
        countS--;
      }
    }
  } else {
    int y = sNotC[-1];
  }
  //}
  outFile << answer.size() << '\n';
  if (answer.size() > n + 1) {
    int y = sNotC[-1];
  }
  for (int i = 0; i < answer.size(); i++) {
    outFile << answer[i].first << " " << answer[i].second << '\n';
  }
  return 0;
}