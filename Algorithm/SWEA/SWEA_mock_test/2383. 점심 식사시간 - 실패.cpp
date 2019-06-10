#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

typedef struct _node {
	int dist, entrance, y, x;
	bool live;
}person;

typedef struct node {
	int depth, cnt, y, x;
}stairs;

#define MAX 10
int T, N;
int map[MAX][MAX];
int pcnt = 0;
int scnt = 0;
person P[10];
stairs S[2];
person Ptmp[10];
stairs Stmp[2];
int rst = INT32_MAX;

int func() {
	int person_cnt = pcnt;

	int snum = 0;
	int len = 0;
	int ret = 0;
	while (person_cnt > 0) {
		//모든 사람에 대해

		/*cout << "ret: " << ret << endl;
		for (int i = 0; i < pcnt; i++) {
		cout << "i: " << i << ", dist: " << Ptmp[i].dist << endl;
		}
		cout << endl;*/

		for (int i = 0; i < pcnt; i++) {
			if (!Ptmp[i].live)continue;

			snum = Ptmp[i].entrance;	//할당된 입구 넘버

			if (Ptmp[i].dist == 0) {
				//이미 3명 이상이 있을 경우
				if (Stmp[snum].cnt >= 3)
					continue;
				else {
					Stmp[snum].cnt++;
					Ptmp[i].dist--;
				}
			}
			else if (Ptmp[i].dist > 0)
				Ptmp[i].dist--;
			else if (Ptmp[i].dist < 0) {
				Ptmp[i].dist--;

				//계단을 전부 내려가면
				if (Ptmp[i].dist == -1 * Stmp[snum].depth - 1) {
					Ptmp[i].live = false;
					Stmp[snum].cnt--;
					person_cnt--;

					/*for (int j = 0; j < pcnt; j++) {
					if (!Ptmp[j].live || Ptmp[j].dist != 0)continue;
					int snum2 = Ptmp[j].entrance;
					if (snum == snum2 && Stmp[snum].cnt < 3) {
					Ptmp[j].dist--;
					Stmp[snum].cnt++;
					}
					}*/
					continue;
				}
			}
		}
		ret++;
	}
	return ret;
}

void dfs(int idx) {
	if (idx == pcnt) {
		//여기서 실행
		for (int i = 0; i < pcnt; i++)
			Ptmp[i] = P[i];
		Stmp[0] = S[0];
		Stmp[1] = S[1];
		rst = min(rst, func());
		return;
	}

	P[idx].entrance = 0;
	P[idx].dist = abs(P[idx].y - S[0].y) + abs(P[idx].x - S[0].x);
	dfs(idx + 1);
	P[idx].entrance = 1;
	P[idx].dist = abs(P[idx].y - S[1].y) + abs(P[idx].x - S[1].x);
	dfs(idx + 1);
}

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		cin >> N;
		pcnt = 0;
		scnt = 0;
		rst = INT32_MAX;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					P[pcnt].y = i;
					P[pcnt].x = j;
					P[pcnt].live = true;
					pcnt++;
				}
				else if (map[i][j] > 1) {
					S[scnt].cnt = 0;
					S[scnt].depth = map[i][j];
					S[scnt].y = i;
					S[scnt].x = j;
					scnt++;
				}
			}
		}

		dfs(0);
		/*for (int i = 0; i < pcnt; i++)
		Ptmp[i] = P[i];

		Ptmp[0].entrance = 0;
		Ptmp[0].dist = abs(Ptmp[0].y - S[0].y) + abs(Ptmp[0].x - S[0].x);
		Ptmp[1].entrance = 0;
		Ptmp[1].dist = abs(Ptmp[1].y - S[0].y) + abs(Ptmp[1].x - S[0].x);
		Ptmp[2].entrance = 0;
		Ptmp[2].dist = abs(Ptmp[2].y - S[0].y) + abs(Ptmp[2].x - S[0].x);
		Ptmp[3].entrance = 1;
		Ptmp[3].dist = abs(Ptmp[3].y - S[1].y) + abs(Ptmp[3].x - S[1].x);
		Ptmp[4].entrance = 1;
		Ptmp[4].dist = abs(Ptmp[4].y - S[1].y) + abs(Ptmp[4].x - S[1].x);
		Ptmp[5].entrance = 1;
		Ptmp[5].dist = abs(Ptmp[5].y - S[1].y) + abs(Ptmp[5].x - S[1].x);
		Stmp[0] = S[0];
		Stmp[1] = S[1];

		rst = min(rst, func());*/


		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}