#include <iostream>
#include <vector>

using namespace std;

int n = 3;
vector<vector<int>> g;
bool used[3];
vector<int> comp;

void dfs(int v) {
	used[v] = true;
	comp.push_back(v);
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs(to);
	}
}

void find_comps() {
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i]) {
			comp.clear();
			dfs(i);

			cout << "Component:";
			for (size_t j = 0; j < comp.size(); ++j)
				cout << ' ' << comp[j];
			cout << endl;
		}
}


int main()
{
	g.push_back({ 1,2,3 });
	g.push_back({ 0,2,3 });
	g.push_back({ 0,1,3 });
	g.push_back({ 0,1,2 });
	find_comps();
	return 0;
}