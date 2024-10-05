#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int N, L, R;
vector<vector<int>> map;
vector<vector<bool>> visited;

// ���� �˻� �Լ�
bool isRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}

// �ǳʰ� �� �ִ� �α� �� �������� �˻�
bool canMove(int x, int y, int nx, int ny) {
	int diff = abs(map[x][y] - map[nx][ny]);
	return diff >= L && diff <= R;
}

bool bfs(int x, int y) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> unions;	// ������ �����Ͽ� �湮�� ������� ����ϱ� ����
	int total_population = 0;

	q.push({ x, y });
	unions.push_back({ x, y });
	visited[x][y] = true;
	total_population += map[x][y];

	while (!q.empty()) {
		pair<int, int> current = q.front();
		int cx = current.first;
		int cy = current.second;

		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			// ������ �Ѿ �� �ִٸ� �̵�.
			if (isRange(nx, ny) && !visited[nx][ny] && canMove(cx, cy, nx, ny)) {
				q.push({ nx, ny });
				unions.push_back({ nx, ny });
				visited[nx][ny] = true;
				total_population += map[nx][ny];
			}
		}
	}

	// �̵����� ���ߴٸ�
	if (unions.size() == 1) return false;

	// ������ ������� ������� �� ������� �α� ����
	int avg = total_population / unions.size();
	for (pair<int, int> p : unions) {
		map[p.first][p.second] = avg;
	}

	return true;
}

int simulate() {
	int days = 0;
	// �Ϸ縶�� �湮 ���� üũ
	while (true) {
		visited.assign(N, vector<bool>(N, false));
		bool moved = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// bfs�� �ѹ��̶� true�� ��ȯ�ȴٸ� �̵��� �̷�����.
				if (!visited[i][j] && bfs(i, j)) {
					moved = true;
				}
			}
		}

		if (!moved) break;
		days++;
	}
	return days;
}

int main(void)
{
	cin >> N >> L >> R;
	map.resize(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cout << simulate() << endl;
	return 0;
}