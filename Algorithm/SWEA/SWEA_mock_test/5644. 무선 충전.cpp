#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct _tmp {
	int y, x, C, P;
}Battery;

typedef struct tmp {
	int y, x;
}person;

#define MAX 100
int T, M, BCnum;
int mov[MAX][2];
person A, B;
Battery BC[8] = { 0, };
int rst = 0;
int dy[] = { 0,-1,0,1,0 };
int dx[] = { 0,0,1,0,-1 };

void func() {
	vector<int>a, b;
	int ma = 0;

	//A와 BC들 탐색
	for (int i = 0; i < BCnum; i++)
		if (abs(A.y - BC[i].y) + abs(A.x - BC[i].x) <= BC[i].C)
			a.push_back(i);

	//B와 BC들 탐색
	for (int i = 0; i < BCnum; i++)
		if (abs(B.y - BC[i].y) + abs(B.x - BC[i].x) <= BC[i].C)
			b.push_back(i);

	//A만 속할 때
	if (a.size() > 0 && b.size() == 0) {
		for (int i = 0; i < (int)a.size(); i++)
			ma = max(ma, BC[a[i]].P);
	}
	//B만 속할 때
	else if (b.size() > 0 && a.size() == 0) {
		for (int i = 0; i < (int)b.size(); i++)
			ma = max(ma, BC[b[i]].P);
	}
	//둘 다 속할 때
	else if (a.size() > 0 && b.size() > 0) {
		for (int i = 0; i < (int)a.size(); i++) {
			for (int j = 0; j < (int)b.size(); j++) {
				if (a[i] == b[j]) {
					ma = max(ma, BC[a[i]].P);
				}
				else {
					ma = max(ma, BC[a[i]].P + BC[b[j]].P);
				}
			}
		}
	}

	rst += ma;
}

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		//초기화
		rst = 0;
		A = { 1, 1 };
		A.y = 1;
		A.x = 1;
		B.y = 10;
		B.x = 10;

		cin >> M >> BCnum;
		for (int i = 0; i < M; i++)
			cin >> mov[i][0];
		for (int i = 0; i < M; i++)
			cin >> mov[i][1];

		for (int i = 0; i < BCnum; i++) {
			int y, x, c, p;
			cin >> x >> y >> c >> p;
			BC[i].C = c;
			BC[i].P = p;
			BC[i].y = y;
			BC[i].x = x;
		}

		func();
		for (int i = 0; i < M; i++) {
			A.y += dy[mov[i][0]];
			A.x += dx[mov[i][0]];
			B.y += dy[mov[i][1]];
			B.x += dx[mov[i][1]];
			func();
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}