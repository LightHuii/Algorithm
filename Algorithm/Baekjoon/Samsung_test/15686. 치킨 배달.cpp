#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
using namespace std;

#define MAX 51
int map[MAX][MAX] = { 0, };
vector<pair<int, int>>house;	//집의 좌표
int h_cnt;						//집의 개수
vector<pair<int, int>>chstore;	//치킨집의 좌표
int ch_cnt;						//치키집의 개수
bool visited[MAX];
int N, M, rst = INT32_MAX;
int ary[13] = { 0, };		//선택된 치킨 집의 idx 저장 배열

							//도시의 치킨  거리 리턴 함수
int chdist() {
	int rst = 0;

	//모든 집에 대해
	for (int i = 0; i < h_cnt; i++) {
		//선택된 치킨 집들에 대해 최소 치킨 거리를 구함
		int mi = INT32_MAX;
		for (int j = 0; j < M; j++) {
			mi = min(mi, abs(chstore[ary[j]].first - house[i].first) + abs(chstore[ary[j]].second - house[i].second));
		}
		//모두 합하고 리턴
		rst += mi;
	}

	return rst;
}

void dfs(int cnt, int idx) {
	//선택된 치킨집의 개수가 M개라면
	if (cnt == M) {
		//도시의 치킨 거리비교하여 최소값 저장 후 리턴
		rst = min(rst, chdist());
		return;
	}

	//첫 번째 시도에서 0번 째도 포함해야 하기 때문에 idx부터 중복으로 체크하기
	for (int i = idx; i < ch_cnt; i++) {
		if (visited[i])continue;
		visited[i] = true;
		ary[cnt] = i;

		dfs(cnt + 1, i);

		visited[i] = false;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back(make_pair(i, j));
			else if (map[i][j] == 2)
				chstore.push_back(make_pair(i, j));
		}
	}

	h_cnt = house.size();
	ch_cnt = chstore.size();
	dfs(0, 0);

	cout << rst << endl;

	return 0;
}