#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<vector<bool>> visited;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int result = 0;

bool isValid(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}

void dfs(int x, int y, int depth, int sum) {
	if (depth == 4) {
		result = max(result, sum);
		return;
	}

	visited[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (isValid(nx, ny) && !visited[nx][ny]) {
			dfs(nx, ny, depth + 1, sum + map[nx][ny]);

			if (depth == 2) {
				visited[nx][ny] = true;

				for (int i = 0; i < 4; i++) {
					int nnx = x + dx[i];
					int nny = y + dy[i];

					if (isValid(nnx, nny) && !visited[nnx][nny]) {
						result = max(result, sum + map[nx][ny] + map[nnx][nny]);
					}
				}

				visited[nx][ny] = false;
			}
		}
	}

	visited[x][y] = false;
}
int main(void) 
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> M;
	
	map = vector<vector<int>>(N, vector<int>(M));
	visited = vector<vector<bool>>(N, vector<bool>(M, false));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dfs(i, j, 1, map[i][j]);
		}
	}

	cout << result << "\n";

	return 0;
}
