#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
using namespace std;

typedef struct _node {
	int y, x;
	int e, d;
	bool live;
}atom;

#define MAX 2001
int T;
int map[MAX][MAX] = { 0, };
vector<atom> v;
int dy[] = { 1, -1, 0, 0 };	//상: y증가, 하: y감소, 좌, 우
int dx[] = { 0, 0, -1, 1 };	//상 하 좌:x감소, 우: x증가

int ddy[] = { 1, -1, 0, 0, 1, -1, 1, -1, 0, 2, 0, -2 };
int ddx[] = { 0, 0, -1, 1, 1, -1, -1, 1, 2, 0, -2, 0 };

bool check(int y, int x, int dir, int ny, int nx, int ndir) {
	//상
	if (dir == 0) {
		if (ny == y + 1 && nx == x - 1 && ndir == 3)
			return true;
		else if (ny == y + 2 && nx == x && ndir == 1)
			return true;
		else if (ny == y + 1 && nx == x + 1 && ndir == 2)
			return true;
		else return false;
	}
	//하
	else if (dir == 1) {
		if (ny == y - 1 && nx == x - 1 && ndir == 3)
			return true;
		else if (ny == y - 2 && nx == x && ndir == 0)
			return true;
		else if (ny == y - 1 && nx == x + 1 && ndir == 2)
			return true;
		else return false;
	}
	//좌
	else if (dir == 2) {
		if (ny == y + 1 && nx == x - 1 && ndir == 1)
			return true;
		else if (ny == y && nx == x - 2 && ndir == 3)
			return true;
		else if (ny == y - 1 && nx == x - 1 && ndir == 0)
			return true;
		else return false;
	}
	//우
	else if (dir == 3) {
		if (ny == y + 1 && nx == x + 1 && ndir == 1)
			return true;
		else if (ny == y && nx == x + 2 && ndir == 2)
			return true;
		else if (ny == y - 1 && nx == x + 1 && ndir == 0)
			return true;
		else return false;
	}
	return false;
}

//정면 판단
bool front_atom(int d1, int d2) {
	switch (d1)
	{
	case 0:if (d2 == 1)return true;
		   else return false;
		   break;
	case 1:if (d2 == 0)return true;
		   else return false;
		   break;
	case 2:if (d2 == 3)return true;
		   else return false;
		   break;
	case 3:if (d2 == 2)return true;
		   else return false;
		   break;
	default:
		break;
	}
	return false;
}

int main() {
	int N, y, x, d, k;
	cin >> T;
	int Ttmp = T;

	while (Ttmp--) {
		int rst = 0, cnt;	//결과 값, 원자 개수

		cin >> N;
		v.resize(N + 1);

		for (int i = 1; i <= N; i++) {
			cin >> x >> y >> d >> k;
			atom tmp;
			tmp.d = d;
			tmp.e = k;
			tmp.y = y + 1000;
			tmp.x = x + 1000;
			tmp.live = true;
			v[i] = tmp;
		}

		cnt = N;
		//노드가 전부 없어질 때까지
		while (cnt > 0) {
			//살아있는 원자에 대해: 일단 map에 매핑
			for (int i = 1; i <= N; i++) {
				if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000 || !v[i].live)continue;
				map[v[i].y][v[i].x] = i;
			}

			//각 원자에 대해 이동 전, 체크하고 이동
			for (int i = 1; i <= N; i++) {
				y = v[i].y, x = v[i].x;
				//없어진 원자면 무시
				if (!v[i].live || y < 0 || y>2000 || x < 0 || x>2000)continue;

				int dir = v[i].d;
				int ny = y + dy[v[i].d];
				int nx = x + dx[v[i].d];	//다음 좌표: 1거리 정면
				int other; //다른 원자 번호

						   //1거리에 원자가 있을 경우
				if (ny >= 0 && ny <= 2000 && nx >= 0 && nx <= 2000 && map[ny][nx] != 0) {
					other = map[ny][nx];

					//정면으로 올 경우
					if (front_atom(v[other].d, dir)) {


						//둘 다 죽는다
						rst += (v[i].e + v[other].e);
						v[i].live = false;
						v[other].live = false;
						cnt -= 2;
						map[v[i].y][v[i].x] = 0;
						map[v[other].y][v[other].x] = 0;


						//다음원자로 넘어감
						continue;
					}
					else {
						//0.5초 후 사라질 원자면 처리 해주기
						int next = map[v[other].y + dy[v[other].d]][v[other].x + dx[v[other].d]];

						if (next != 0) {
							//정면이라면
							if (front_atom(v[other].d, v[next].d)) {
								rst += (v[next].e + v[other].e);
								v[next].live = false;
								v[other].live = false;
								map[v[next].y][v[next].x] = 0;
								map[v[other].y][v[other].x] = 0;
								cnt -= 2;
							}
						}
						//정면이 아니거나, 없거나, 이미 처리가 됐다면, i의 거리 2 처리로 넘어가기
					}
				}

				//거리 2 원자들 처리
				bool flag = false;	//터졌는지 확인
				for (int j = 0; j < 12; j++) {
					int nny, nnx;
					nny = y + ddy[j];
					nnx = x + ddx[j];
					if (nny < 0 || nny>2000 || nnx < 0 || nnx>2000 || map[nny][nnx] == 0)continue;
					int next = map[nny][nnx];

					if (check(y, x, dir, nny, nnx, v[next].d) && v[next].live) {
						//next 터짐
						rst += v[next].e;
						v[next].live = false;
						map[v[next].y][v[next].x] = 0;
						flag = true;
						cnt--;
					}
				}

				//터졌다면 i도 터짐
				if (flag) {
					rst += v[i].e;
					v[i].live = false;
					map[v[i].y][v[i].x] = 0;
					cnt--;
				}
				else {
					//이동
					map[v[i].y][v[i].x] = 0;
					v[i].y = ny;
					v[i].x = nx;

					//이동 후 밖으로 나갔다면 삭제
					if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000) {
						v[i].live = false;
						cnt--;
					}
				}
			}

			//맵 내부에 있는 모든 원소들에 대해 맵에서 삭제
			for (int i = 1; i <= N; i++) {
				if (!v[i].live)continue;
				if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000)continue;
				map[v[i].y][v[i].x] = 0;
			}

			//cout << "현재: " << i << endl;
			////if (rst > 0) {
			//	for (int k = 1; k <= N; k++) {
			//		cout << "i: (" << v[k].y << ", " << v[k].x << "), d: " << v[k].d << ", " << v[k].live << endl;
			//	}
			//	cout << "cnt, rst: " << cnt << ", " << rst << endl;
			//	cout << endl;
			////}

		}

		cout << '#' << T - Ttmp << ' ' << rst << endl;
		v.clear();
		memset(map, 0, sizeof(map));
	}


	return 0;
}