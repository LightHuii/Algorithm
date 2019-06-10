#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct _cell {
	vector<pair<int, bool>>tree;	//나무의 나이, 생사 유무
	int nutrient;	//양분
}cell;

#define MAX 11
cell area[MAX][MAX];
int nutr[MAX][MAX];		//겨울에 공급할 양분
int N, M, K;	//크기, 나무 개수, 년
int dy[] = { 0,0,1,-1,1,-1,-1,1 };
int dx[] = { 1,-1,0,0,1,-1,1,-1 };

void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//트리가 비어있다면
			if (area[i][j].tree.empty())continue;

			//정렬하고 수행
			sort(area[i][j].tree.begin(), area[i][j].tree.end());
			for (int k = 0; k < (int)area[i][j].tree.size(); k++) {
				if (area[i][j].tree[k].first <= area[i][j].nutrient) {
					area[i][j].nutrient -= area[i][j].tree[k].first;	//양분 감소
					if (area[i][j].nutrient < 0)area[i][j].nutrient = 0;
					area[i][j].tree[k].first += 1;	//나이 증가
				}
				else {
					//죽는다.
					area[i][j].tree[k].second = false;
				}
			}
		}
	}
}

void summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (area[i][j].tree.empty())continue;

			int size = area[i][j].tree.size();
			int cnt = 0;
			for (int k = 0; k < size; k++) {
				//죽었다면
				if (!area[i][j].tree[k].second) {
					//양분 증가
					area[i][j].nutrient += area[i][j].tree[k].first / 2;
					cnt++;
				}
			}
			for (int k = 0; k < cnt; k++)
				area[i][j].tree.pop_back();
		}
	}
}

void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (area[i][j].tree.empty())continue;

			for (int k = 0; k < (int)area[i][j].tree.size(); k++) {
				//나이가 5의 배수라면
				if (area[i][j].tree[k].first % 5 == 0) {
					for (int l = 0; l < 8; l++) {
						int ny = i + dy[l];
						int nx = j + dx[l];
						if (ny<1 || ny>N || nx<1 || nx>N)continue;
						area[ny][nx].tree.push_back(make_pair(1, true));
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			area[i][j].nutrient += nutr[i][j];
		}
	}
}

int main() {
	int y, x, age;
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> nutr[i][j];
			area[i][j].nutrient = 5;
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> y >> x >> age;
		area[y][x].tree.push_back(make_pair(age, true));
	}

	for (int i = 0; i < K; i++) {
		//봄
		spring();

		//여름
		summer();

		//가을
		fall();

		//겨울
		winter();
	}

	int rst = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			rst += area[i][j].tree.size();
		}
	}

	cout << rst << endl;
	return 0;
}
​