#include<iostream>
#include<algorithm>
using namespace std;

typedef struct rb {
	int y, x, dir;
}Robot;
typedef struct cd {
	int num, cnt;
	char cmd;
}Command;

int dy[] = { 1,0,-1,0 };	//북서남동
int dx[] = { 0,-1,0,1 };

#define MAX 101
int A, B, N, M;
Robot robot[MAX];
Command command[MAX];
int map[MAX][MAX] = { 0, };

int main()
{
	cin >> A >> B;
	cin >> N >> M;

	//로봇 정보 입력
	for (int i = 1; i <= N; i++) {
		char d;
		cin >> robot[i].x >> robot[i].y >> d;
		switch (d) {
		case 'N': robot[i].dir = 0; break;
		case 'W': robot[i].dir = 1; break;
		case 'S': robot[i].dir = 2; break;
		case 'E': robot[i].dir = 3; break;
		default:
			break;
		}
		map[robot[i].y][robot[i].x] = i;
	}

	for (int i = 1; i <= M; i++)
		cin >> command[i].num >> command[i].cmd >> command[i].cnt;

	//각 커맨드 실행
	int err_flag = 0;	//0: OK, 1: 벽 충돌, 2: 다른 로봇과 충돌
	int rst_me, rst_other;

	for (int i = 1; i <= M; i++) {
		int rnum = command[i].num;	//명령할 로봇 번호

		//반시계 회전
		if (command[i].cmd == 'L') {
			for (int j = 0; j < command[i].cnt; j++)
				robot[rnum].dir = (robot[rnum].dir + 1) % 4;
		}
		//시계 회전
		else if (command[i].cmd == 'R') {
			for (int j = 0; j < command[i].cnt; j++) {
				robot[rnum].dir--;
				if (robot[rnum].dir < 0)robot[rnum].dir = 3;
			}
		}
		else if (command[i].cmd == 'F') {
			int y = robot[rnum].y;
			int x = robot[rnum].x;
			int d = robot[rnum].dir;
			int ny = 0, nx = 0;

			for (int j = 0; j < command[i].cnt; j++) {
				ny = y + dy[d];
				nx = x + dx[d];

				//벽에 출동
				if (ny <= 0 || ny > B || nx <= 0 || nx > A) {
					err_flag = 1;
					rst_me = rnum;
					break;
				}
				//다른 로봇에 충돌
				else if (map[ny][nx] != 0) {
					rst_me = rnum;
					rst_other = map[ny][nx];
					err_flag = 2;
					break;
				}
				if (err_flag != 0)break;	//충돌했다면 나가기
				y = ny;
				x = nx;
			}

			//충돌하지 않는다면 이동
			map[robot[rnum].y][robot[rnum].x] = 0;
			map[ny][nx] = rnum;
			robot[rnum].y = y;
			robot[rnum].x = x;
		}
		if (err_flag != 0)break;
	}

	if (err_flag == 0)
		cout << "OK" << endl;
	else if (err_flag == 1)
		cout << "Robot " << rst_me << " crashes into the wall" << endl;
	else if (err_flag == 2)
		cout << "Robot " << rst_me << " crashes into robot " << rst_other << endl;
}