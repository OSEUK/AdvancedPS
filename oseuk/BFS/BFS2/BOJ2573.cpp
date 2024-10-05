#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<vector<bool>> visited;
const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1,  0, -1 };

// ��ǥ�� ���̸� �ѹ��� ����
// ����ü ����
struct Pos {
	int x, y, height;
};

void bfs(int x, int y) 
{
	queue<Pos> q;
	q.push({ x, y, map[x][y] });
	visited[x][y] = true;

	while (!q.empty()) {
		Pos p = q.front();
		q.pop();

		int nextHeight = p.height;

		for (int i = 0; i < 4; i++) {
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];

			// �ֺ��� 0 ������ �ľ� ����. �̹� �湮�� ������ ��� ����
			if (!visited[nx][ny] && map[nx][ny] == 0) {
				if (nextHeight > 0) nextHeight--;
				continue;
			}

			if (!visited[nx][ny] && map[nx][ny] != 0) {
				q.push({ nx, ny, map[nx][ny] });
				visited[nx][ny] = true;
			}
		}

		// �湮 �Ϸ��� ������ ���� ����
		map[p.x][p.y] = nextHeight;
	}
}
int simulate() 
{
	int years = 0;

	while (true) 
	{
		int bfsCount = 0;

		visited = vector<vector<bool>>(N, vector<bool>(M, false));

		// bfsCount > 1  : ���� �и�
		// bfsCount == 1 : ��� ����
		// bfsCount == 0 : ������ ���� ����. 0 ��ȯ
		for (int i = 1; i < N - 1; i++) {
			for (int j = 1; j < M - 1; j++) {
				if (!visited[i][j] && map[i][j] != 0) {
					bfsCount++;
					bfs(i, j);
				}
			}
		}

		if (bfsCount > 1) {
			return years;
		}

		if (bfsCount == 0) {
			return 0;
		}

		years++;
	}
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> M;
	map = vector<vector<int>>(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	cout << simulate() << endl;
}