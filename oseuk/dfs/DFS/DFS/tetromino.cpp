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

// 맵의 범위를 검사하는 함수
bool isValid(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}

// dfs
void dfs(int x, int y, int depth, int sum) {
	// 테트로미노가 완성되면 값 검사
	if (depth == 4) {
		result = max(result, sum);
		return;
	}

	visited[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (isValid(nx, ny) && !visited[nx][ny]) {	// 방문하지 않은 방향으로 이동.
			dfs(nx, ny, depth + 1, sum + map[nx][ny]);

			// T자 모양을 만들기 위한 부분
			// nx, ny == 3번째 블록
			// nnx, nny == 4번째 블록
			if (depth == 2) {
				visited[nx][ny] = true;

				for (int i = 0; i < 4; i++) {
					int nnx = x + dx[i];
					int nny = y + dy[i];

					// 3번째로 이미 이동한 블럭과, 2번째에서 다시 탐색한 블럭으로 T자 모양을 완성시킴
					// 두 값을 더해서 최댓값을 구함.
					if (isValid(nnx, nny) && !visited[nnx][nny]) {
						result = max(result, sum + map[nx][ny] + map[nnx][nny]);
					}
				}

				visited[nx][ny] = false;
			}
		}
	}
	// 완전 탐색으로 visited를 계속 사용하므로, 방문 배열을 초기화함.
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
