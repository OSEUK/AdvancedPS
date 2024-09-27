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

// ���� ������ �˻��ϴ� �Լ�
bool isValid(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}

// dfs
void dfs(int x, int y, int depth, int sum) {
	// ��Ʈ�ι̳밡 �ϼ��Ǹ� �� �˻�
	if (depth == 4) {
		result = max(result, sum);
		return;
	}

	visited[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (isValid(nx, ny) && !visited[nx][ny]) {	// �湮���� ���� �������� �̵�.
			dfs(nx, ny, depth + 1, sum + map[nx][ny]);

			// T�� ����� ����� ���� �κ�
			// nx, ny == 3��° ���
			// nnx, nny == 4��° ���
			if (depth == 2) {
				visited[nx][ny] = true;

				for (int i = 0; i < 4; i++) {
					int nnx = x + dx[i];
					int nny = y + dy[i];

					// 3��°�� �̹� �̵��� ����, 2��°���� �ٽ� Ž���� ������ T�� ����� �ϼ���Ŵ
					// �� ���� ���ؼ� �ִ��� ����.
					if (isValid(nnx, nny) && !visited[nnx][nny]) {
						result = max(result, sum + map[nx][ny] + map[nnx][nny]);
					}
				}

				visited[nx][ny] = false;
			}
		}
	}
	// ���� Ž������ visited�� ��� ����ϹǷ�, �湮 �迭�� �ʱ�ȭ��.
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
