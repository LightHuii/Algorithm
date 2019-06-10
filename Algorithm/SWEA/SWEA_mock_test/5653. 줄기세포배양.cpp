
​

​

#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

#define MAX 350
#define padd 150
pair<int, int> cell[MAX][MAX];    //생명력, 상태(0: 비활, 1: 활, 2: 죽음)
int remTime[MAX][MAX];          //남은 시간
int N, M, K, T;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void init() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			remTime[i][j] = 0;
			cell[i][j] = make_pair(0, 0);
		}
	}
}

int main() {
	cin >> T;
	int tmpT = T;
	int hour = 0;

	while (tmpT--) {
		cin >> N >> M >> K;
		init();
		for (int i = padd; i < padd + N; i++) {
			for (int j = padd; j < padd + M; j++) {
				cin >> cell[i][j].first;
				cell[i][j].second = 0;
				remTime[i][j] = cell[i][j].first;
			}
		}


		for (hour = 0; hour < K; hour++) {
			//한 사이클
			queue<pair<int, pair<int, int>>>q;

			for (int y = 0; y < MAX; y++) {
				for (int x = 0; x < MAX; x++) {
					//아무것도 아니면 스킵
					if (cell[y][x].first == 0 && cell[y][x].second == 0)continue;

					int life = cell[y][x].first;
					bool spread = false;
					//활성 -> 죽음 or 퍼질 준비
					if (life > 0 && cell[y][x].second == 1) {
						if (remTime[y][x] == 0) {
							cell[y][x].second = 2;
						}
						if (remTime[y][x] == life - 1) {
							spread = true;
						}
					}

					//비활 -> 활성
					if (life > 0 && cell[y][x].second == 0) {
						if (remTime[y][x] == 1) {
							cell[y][x].second = 1;
							remTime[y][x] = life;
						}
					}

					//살아있다면 남은 시간 감소
					if (cell[y][x].first > 0 && cell[y][x].second <= 1) {
						remTime[y][x]--;
					}


					if (spread) {
						for (int i = 0; i < 4; i++) {
							int ny = y + dy[i];
							int nx = x + dx[i];
							//이미 세포가 있다면 스킵
							if (cell[ny][nx].first > 0)continue;
							//아니라면 일단 큐에 푸시
							q.push(make_pair(life, make_pair(ny, nx)));
							//cout << y << ", " << x << endl;
							//cout << "ny,nx: " << ny << ", " << nx << endl;
						}
					}
				}
			}
			//사이클 끝

			int qsize = q.size();
			while (qsize--) {
				int val = q.front().first;
				int ny = q.front().second.first;
				int nx = q.front().second.second;
				q.pop();

				if (cell[ny][nx].first == 0) {
					cell[ny][nx].first = val;
					remTime[ny][nx] = val;
					cell[ny][nx].second = 0;
				}
				else {
					if (val > cell[ny][nx].first) {
						cell[ny][nx].first = val;
						remTime[ny][nx] = val;
						cell[ny][nx].second = 0;
					}
				}
			}
		}


		int rst = 0;
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				if (cell[i][j].first > 0 && cell[i][j].second <= 1)
					rst++;

		cout << '#' << T - tmpT << ' ' << rst << endl;
	}

}