#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;
int n1;
int m1;
int n2;
int m2;
int countGraphIsomorphism = 0;
vector<unordered_set<int>> graphList1;
vector<unordered_set<int>> graphList2;
vector<vector<int>> graph1;
vector<vector<int>> graph2;
vector<vector<int>> graphIsomorphism;
bool graphIsomorphism1 = false;
vector<int> graph21;
vector<int> graphV;
bool refine(int i, int j) {
  int vNeare = 0;
  vector<int> y1;
  for (int i1 = 0; i1 < graph1[i].size(); i1++) {
    int v = graph1[i][i1];
    y1.push_back(graph1[v].size());
  }
  vector<int> y2;
  for (int i1 = 0; i1 < graph2[j].size(); i1++) {
    int v = graph2[j][i1];
    y2.push_back(graph2[v].size());
  }
  std::sort(y1.begin(), y1.end());
  std::sort(y2.begin(), y2.end());
  if (y1 != y2) {
    return false;
  }
  for (int v : graphList1[i]) {
    for (int j1 = 0; j1 < n2; j1++) {
      if (graphIsomorphism[v][j1] == 1) {
        if (graphList2[j].find(j1) != graphList2[j].end()) {
          vNeare++;
          break;
        }
      }
    }
  }
  if (vNeare == graphList1[i].size()) {
    return true;
  }
  return false;
}
bool isGraphList(vector<vector<int>> graphIsomorphism) {
  for (int i = 0; i < n1; i++) {
    int countStr = 0;
    for (int j = 0; j < n2; j++) {
      if (graphIsomorphism[i][j] == 1) {
        countStr++;
      }
    }
    if (countStr < 1) {
      return false;
    }
  }
  for (int i = 0; i < n1; i++) {
    int countStr = 0;
    for (int j = 0; j < n2; j++) {
      if (graphIsomorphism[j][i] == 1) {
        countStr++;
      }
    }
    if (countStr < 1) {
      return false;
    }
  }
  return true;
}
bool isList12(vector<int> graph12) {
  vector<vector<int>> graph22 = graph1;
  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < graph1[i].size(); j++) {
      graph22[i][j] = graph12[graph1[i][j]];
    }
  }
  vector<vector<int>> graph11 = graph22;
  for (int i = 0; i < n1; i++) {
    graph11[graph12[i]] = graph22[i];
  }
  for (int i = 0; i < n1; i++) {
    sort(graph11[i].begin(), graph11[i].end());
    sort(graph2[i].begin(), graph2[i].end());
  }
  if (graph11 == graph2) {
    if (!graphIsomorphism1) {
      graph21 = graph12;
      graphIsomorphism1 = true;
    }
    return true;
  }
  return false;
}
// bool isListpart12(vector<int> graph12) {
//  vector<unordered_set<int>> graph22 = graphList1;
//  for (int i = 0; i < n2; i++) {
//    vector<int> y;
//    if (graph12[i] != -1) {
//      for (int j = 0; j < graph22[i].size(); j++) {
//        if (graph12[graph22[i][j]] != -1) {
//          y.push_back(graph12[graph22[i][j]]);
//        }
//        graph22[i][j] = graph12[graph1[i][j]];
//      }
//    }
//    graph22[i].clear();
//    for (int v : y) {
//      graph22[i].insert(v);
//    }
//  }
//  vector<unordered_set<int>> graph11 = graph22;
//  for (int i = 0; i < n1; i++) {
//    if (graph12[i] != -1) {
//      graph11[graph12[i]] = graph22[i];
//    }
//  }
//  vector<unordered_set<int>> graph23 = graphList2;
//  for (int i = 0; i < n2; i++) {
//    if (graph12[i] == -1) {
//      graph23[i].clear();
//    }
//      else {
//      vector<int> y;
//      for (int v : graph23[i]) {
//        if (graph12[v] == -1) {
//          y.push_back(v);
//        }
//      }
//      for (int i = 0; i < y.size(); i++) {
//        graph23[i].erase(y[i]);
//      }
//    }
//  }
//  //for (int i = 0; i < n1; i++) {
//  //  sort(graph11[i].begin(), graph11[i].end());
//  //  sort(graph23[i].begin(), graph23[i].end());
//  //}
//  if (graph11 == graph23) {
//    return true;
//  }
//  return false;
//}
void graphPermutation(int i, int j, vector<vector<int>> graphIsomorphism,
                      vector<int> graph12) {
  if (i < n1) {
    for (int i1 = 0; i1 < n2; i1++) {
      if (i1 != graphV[i]) {
        graphIsomorphism[i1][j] = 0;
      }
    }
    for (int i1 = 0; i1 < n1; i1++) {
      for (int j1 = 0; j1 < n2; j1++) {
        if (graphIsomorphism[i1][j1] == 1) {
          if (!refine(i1, j1)) {
            return;
          }
        }
      }
    }
    // if (!isGraphList(graphIsomorphism)) {
    //  return;
    //}
    vector<int> graph11;
    for (int j1 = 0; j1 < n2; j1++) {
      if (i + 1 < n2) {
        if (graphIsomorphism[graphV[i + 1]][j1] == 1) {
          int v1 = graphV[i];
          int u1 = graphV[i + 1];
          int v2 = graph12[graphV[i]];
          int u2 = j1;
          if ((graphList1[v1].find(u1) != graphList1[v1].end() &&
               graphList2[v2].find(u2) != graphList2[v2].end()) ||
              (graphList1[v1].find(u1) == graphList1[v1].end() &&
               graphList2[v2].find(u2) == graphList2[v2].end())) {
            graph11 = graph12;
            graph11[graphV[i + 1]] = j1;
            graphPermutation(i + 1, j1, graphIsomorphism, graph11);
          }
        }
      } else {
        // for (int i = 0; i < graph12.size(); i++) {
        //  cout << graph12[i] << " ";
        //}
        // cout << endl;
        if (graph12.size() == n1) {
          if (isList12(graph12)) {
            countGraphIsomorphism++;
          }
        }
        return;
      }
    }
  } /*else {
    if (isList12(graph12)) {
      countGraphIsomorphism++;
    }*/
    /* return;
   }*/
}
int main() {
  int u;
  int v;
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  inFile >> n1;
  inFile >> m1;
  graphList1.assign(n1, unordered_set<int>());
  graph1.assign(n1, vector<int>());
  vector<int> graphV1(n1);
  vector<vector<int>> graph24(n1, vector<int>(n1, 0));
  int edges = 0;
  for (int i = 0; i < m1; i++) {
    inFile >> u;
    inFile >> v;
    graphList1[u].insert(v);
    graphList1[v].insert(u);
    graphV1[u] += 1;
    graphV1[v] += 1;
    graph1[u].push_back(v);
    graph1[v].push_back(u);
    graph24[u][v] = 1;
    graph24[v][u] = 1;
    edges++;
  }
  inFile >> n2;
  inFile >> m2;
  graphList2.assign(n2, unordered_set<int>());
  graph2.assign(n2, vector<int>());
  vector<vector<int>> graph23(n2, vector<int>(n2, 0));
  vector<int> graphV2(n2);
  for (int i = 0; i < m2; i++) {
    inFile >> u;
    inFile >> v;
    graphList2[u].insert(v);
    graphList2[v].insert(u);
    graphV2[u] += 1;
    graphV2[v] += 1;
    graph2[u].push_back(v);
    graph2[v].push_back(u);
    graph23[u][v] = 1;
    graph23[v][u] = 1;
  }
  sort(graphV1.begin(), graphV1.end());
  sort(graphV2.begin(), graphV2.end());
  if (graphV1 != graphV2) {
    outFile << "NO";
    return 0;
  }
  const double EPS = 1E-9;
  double det1 = 1;
  for (int i = 0; i < n1; ++i) {
    int k = i;
    for (int j = i + 1; j < n1; ++j)
      if (abs(graph24[j][i]) > abs(graph24[k][i])) k = j;
    if (abs(graph24[k][i]) < EPS) {
      det1 = 0;
      break;
    }
    swap(graph24[i], graph24[k]);
    if (i != k) det1 = -det1;
    det1 *= graph24[i][i];
    for (int j = i + 1; j < n1; ++j) graph24[i][j] /= graph24[i][i];
    for (int j = 0; j < n1; ++j)
      if (j != i && abs(graph24[j][i]) > EPS)
        for (int k = i + 1; k < n1; ++k)
          graph24[j][k] -= graph24[i][k] * graph24[j][i];
  }
  double det2 = 1;
  for (int i = 0; i < n2; ++i) {
    int k = i;
    for (int j = i + 1; j < n2; ++j)
      if (abs(graph23[j][i]) > abs(graph23[k][i])) k = j;
    if (abs(graph23[k][i]) < EPS) {
      det2 = 0;
      break;
    }
    swap(graph23[i], graph23[k]);
    if (i != k) det2 = -det2;
    det2 *= graph23[i][i];
    for (int j = i + 1; j < n2; ++j) graph23[i][j] /= graph23[i][i];
    for (int j = 0; j < n2; ++j)
      if (j != i && abs(graph23[j][i]) > EPS)
        for (int k = i + 1; k < n2; ++k)
          graph23[j][k] -= graph23[i][k] * graph23[j][i];
  }
  if (det1 != det2 && det1 != -1 * det2) {
    outFile << "NO";
    return 0;
  }
  multiset<int> dist1;
  vector<vector<int>> dist11(n1, vector<int>(n1, INT_MAX));
  for (int i = 0; i < n1; i++) {
    dist11[i][i] = 0;
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < graph1[i].size(); j++) {
      dist11[i][graph1[i][j]] = 1;
      dist11[graph1[i][j]][i] = 1;
    }
  }
  for (int k = 0; k < n1; ++k) {
    for (int i = 0; i < n1; ++i) {
      for (int j = 0; j < n1; ++j) {
        if (dist11[i][k] < INT_MAX && dist11[k][j] < INT_MAX) {
          dist11[i][j] = min(dist11[i][j], dist11[i][k] + dist11[k][j]);
        }
      }
    }
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n1; j++) {
      dist1.insert(dist11[i][j]);
    }
  }
  multiset<int> dist2;
  vector<vector<int>> dist22(n2, vector<int>(n2, INT_MAX));
  for (int i = 0; i < n2; i++) {
    dist22[i][i] = 0;
  }
  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < graph2[i].size(); j++) {
      dist22[i][graph2[i][j]] = 1;
    }
  }
  for (int k = 0; k < n2; ++k) {
    for (int i = 0; i < n2; ++i) {
      for (int j = 0; j < n2; ++j) {
        if (dist22[i][k] < INT_MAX && dist22[k][j] < INT_MAX) {
          dist22[i][j] = min(dist22[i][j], dist22[i][k] + dist22[k][j]);
        }
      }
    }
  }
  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < n2; j++) {
      dist2.insert(dist22[i][j]);
    }
  }
  if (dist1 != dist2) {
    outFile << "NO";
    return 0;
  }

  if (edges > n1 * (n1 - 1) / 4) {
    vector<vector<int>> graph11(n1);
    vector<vector<int>> graph22(n1);
    vector<unordered_set<int>> graphV11(n1);
    vector<unordered_set<int>> graphV22(n1);
    for (int i = 0; i < n1; i++) {
      for (int j = 0; j < n1; j++) {
        if (graphList1[i].find(j) == graphList1[i].end()) {
          if (i != j) {
            graph11[i].push_back(j);
            graphV11[i].insert(j);
          }
        }
        if (graphList2[i].find(j) == graphList2[i].end()) {
          if (i != j) {
            graph22[i].push_back(j);
            graphV22[i].insert(j);
          }
        }
      }
    }
    graph1 = graph11;
    graph2 = graph22;
    graphList1 = graphV11;
    graphList2 = graphV22;
  }
  graphIsomorphism.assign(n1, vector<int>(n1, 0));
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      if (graphList1[i].size() == graphList2[j].size()) {
        graphIsomorphism[i][j] = 1;
      }
    }
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      if (graphIsomorphism[i][j] == 1) {
        if (!refine(i, j)) {
          graphIsomorphism[i][j] = 0;
        }
      }
    }
  }
  int i1 = 0;
  stack<int> graphIsomorphism2;
  vector<bool> used(n1, false);
  vector<int> y1;
  for (int i = 0; i < n1; i++) {
    if (!used[i]) {
      graphIsomorphism2.push(i);
      while (graphIsomorphism2.size() != 0) {
        int v = graphIsomorphism2.top();
        i1++;
        graphIsomorphism2.pop();
        used[v] = true;
        graphV.push_back(v);
        for (int j = 0; j < graph1[v].size(); j++) {
          if (!used[graph1[v][j]]) {
            graphIsomorphism2.push(graph1[v][j]);
            used[graph1[v][j]] = true;
          }
        }
      }
      y1.push_back(i1);
    }
  }
  while (!graphIsomorphism2.empty()) {
    graphIsomorphism2.pop();
  }
  i1 = 0;
  vector<bool> used1(n1, false);
  vector<int> y2;
  for (int i = 0; i < n1; i++) {
    if (!used1[i]) {
      graphIsomorphism2.push(i);
      while (graphIsomorphism2.size() != 0) {
        int v = graphIsomorphism2.top();
        graphIsomorphism2.pop();
        used1[v] = true;
        i1++;
        for (int j = 0; j < graph2[v].size(); j++) {
          if (!used1[graph2[v][j]]) {
            graphIsomorphism2.push(graph2[v][j]);
            used1[graph2[v][j]] = true;
          }
        }
      }
      y2.push_back(i1);
    }
  }
  sort(y1.begin(), y1.end());
  sort(y2.begin(), y2.end());
  if (y1 != y2) {
    outFile << "NO";
    return 0;
  }

  // vector<bool> used(n1, false);
  // for (int i = 0; i < n1; i++) {
  //  int y = INT_MAX;
  //  int i1 = -1;
  //  for (int j = 0; j < n1; j++) {
  //    if (graph1[j].size() < y && !used [j]) {
  //      y = graph1[j].size();
  //      i1 = j;
  //    }
  //  }
  //  used[i1] = true;
  //  graphV.push_back(i1);
  //}
  vector<int> graph12(n1, -1);
  for (int j = 0; j < n2; j++) {
    if (graphIsomorphism[graphV[0]][j] == 1) {
      graph12[graphV[0]] = j;
      graphPermutation(0, j, graphIsomorphism, graph12);
      graph12.clear();
      graph12.assign(n1, -1);
    }
  }
  if (graphIsomorphism1) {
    outFile << "YES" << '\n';
    for (int i = 0; i < graph21.size(); i++) {
      outFile << graph21[i] << " ";
    }
    outFile << '\n';
    outFile << countGraphIsomorphism;
  } else {
    outFile << "NO";
  }
  return 0;
}