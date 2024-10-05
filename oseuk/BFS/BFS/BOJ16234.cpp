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

// 범위 검사 함수
bool isRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}

// 건너갈 수 있는 인구 수 차이인지 검사
bool canMove(int x, int y, int nx, int ny) {
	int diff = abs(map[x][y] - map[nx][ny]);
	return diff >= L && diff <= R;
}

bool bfs(int x, int y) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> unions;	// 연합을 정의하여 방문한 나라들을 계산하기 위함
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

			// 국경을 넘어갈 수 있다면 이동.
			if (isRange(nx, ny) && !visited[nx][ny] && canMove(cx, cy, nx, ny)) {
				q.push({ nx, ny });
				unions.push_back({ nx, ny });
				visited[nx][ny] = true;
				total_population += map[nx][ny];
			}
		}
	}

	// 이동하지 못했다면
	if (unions.size() == 1) return false;

	// 합쳐진 나라들의 평균으로 각 나라들의 인구 통일
	int avg = total_population / unions.size();
	for (pair<int, int> p : unions) {
		map[p.first][p.second] = avg;
	}

	return true;
}

int simulate() {
	int days = 0;
	// 하루마다 방문 여부 체크
	while (true) {
		visited.assign(N, vector<bool>(N, false));
		bool moved = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// bfs가 한번이라도 true가 반환된다면 이동이 이뤄진것.
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