#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 1001
int H, W;
char map[MAX][MAX];
int dy[] = { 0,0,-1,1,-1,1,-1,1 };
int dx[] = { -1,1,0,0,-1,1,1,-1 };
int scount[MAX][MAX] = { 0, };
int t = 0;
vector<pair<int, int>>v1;
vector<pair<int, int>>v2;

int main()
{
	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
		}
	}

	bool flag1 = false;		//처음 개수를 셀 때 하나라도 없어진다면 true

	//단순 탐색으로 주변'.'의 개수를 세고, 없어지는 좌표가 있다면 push
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] == '.')continue;
			for (int k = 0; k < 8; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
				if (map[ny][nx] == '.') {
					scount[i][j]++;
					if (scount[i][j] == map[i][j] - '0') {
						v1.push_back(make_pair(i, j));
						flag1 = true;
					}
				}
			}
		}
	}

	while (flag1) {
		bool flag2 = false;		//한 번이라도 무너진다면 true

		//이전에 무너졌던 좌표:v1
		//이전에 무너졌던 좌표는 '.'이 되고, 주변 좌표의 카운트를 증가시킨다.
		for (int i = 0; i < (int)v1.size(); i++) {
			int y = v1[i].first;
			int x = v1[i].second;

			for (int j = 0; j < 8; j++) {
				int ny = y + dy[j];
				int nx = x + dx[j];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
				if (map[ny][nx] == '.')continue;
				
				//주변 '.'이 아닌 좌표를 증가
				scount[ny][nx]++;
				//수가 같아질 때만 v2에 push한다 
				if (map[ny][nx] - '0' == scount[ny][nx]) {
					v2.push_back(make_pair(ny, nx));
					flag2 = true;
				}
			}
		}
		v1.clear();

		//v2로 복사
		for (int i = 0; i < (int)v2.size(); i++)
			v1.push_back(v2[i]);
		v2.clear();

		t++;
		if (!flag2)break;

	}

	cout << t << endl;

	return 0;
}