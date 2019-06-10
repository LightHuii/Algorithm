#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 100
int T, N, M, K;
typedef struct _cell {
	int y, x, dir;
	int n;
	bool del;
}cell;
vector<cell> v;
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,-1,1 };

int main() {
	int Ttmp, y, x, n, d;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			cin >> y >> x >> n >> d;
			cell tmp;
			tmp.y = y;
			tmp.x = x;
			tmp.n = n;
			tmp.del = false;
			tmp.dir = d;
			v.push_back(tmp);
		}

		//시간
		for (int i = 0; i < M; i++) {
			pair<int, int> map[MAX][MAX] = { make_pair(0,0), };

			//미생물 마다
			for (int j = 0; j < K; j++) {
				if (v[j].del)
					continue;

				//다음 좌표
				int ny = v[j].y + dy[v[j].dir];
				int nx = v[j].x + dx[v[j].dir];

				//이동하기 전에, 겹친다면
				if (map[ny][nx].first != 0) {
					int other = map[ny][nx].first - 1;	//겹치는 군집 번호

														//아직 해당 좌표에 겹치는 경우가 없다면
					if (map[ny][nx].second == 0) {
						if (v[other].n < v[j].n) {
							map[ny][nx].second = v[j].n;	//더 큰 값을 second에 저장한다
							v[j].n += v[other].n;
							v[other].del = true;	//작은 값은 삭제
						}
						else {
							map[ny][nx].second = v[other].n;
							v[other].n += v[j].n;
							v[j].del = true;		//작은 값은 삭제
							continue;	//j는 더이상 진행X
						}
					}
					//이미 해당 좌표에 겹친 적이 있다면
					else {
						//비교 전 더 컸던 원래 값과 비교한다.
						if (map[ny][nx].second < v[j].n) {
							map[ny][nx].second = v[j].n;
							v[j].n += v[other].n;
							v[other].del = true;
						}
						else {
							v[other].n += v[j].n;
							v[j].del = true;
							continue;	//j는 더이상 진행X
						}
					}
				}

				//외곽이라면 미생물 수 감소하고, 방향 전환
				if (ny == 0) {
					v[j].dir = 2;
					v[j].n /= 2;
				}
				else if (ny == N - 1) {
					v[j].dir = 1;
					v[j].n /= 2;
				}
				else if (nx == 0) {
					v[j].dir = 4;
					v[j].n /= 2;
				}
				else if (nx == N - 1) {
					v[j].dir = 3;
					v[j].n /= 2;
				}

				if (v[j].n == 0) {
					v[j].del = true;
					continue;
				}

				//이동
				v[j].y = ny;
				v[j].x = nx;
				map[ny][nx].first = (j + 1);	//map에 위치 표시
			}
		}

		//몇 개인지 세기
		int rst = 0;
		for (int i = 0; i < K; i++) {
			if (v[i].del)continue;
			rst += v[i].n;
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
		v.clear();
	}

	return 0;
}
