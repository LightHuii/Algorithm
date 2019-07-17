#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 32001
int N, M;
int cnt[MAX] = { 0, };		//자신으로 들어오는 엣지의 개수
vector<vector<int>>v;

int main()
{
	int a, b;
	cin >> N >> M;
	v.resize(N + 1);

	//노드를 향하는 엣지의 수를 체크
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cnt[b]++;
		v[a].push_back(b);
	}

	int mi, idx = 0;
	for (int i = 1; i <= N; i++) {
		mi = INT32_MAX;

		//최소값 찾기
		for (int j = 1; j <= N; j++) {
			if (mi > cnt[j]) {
				mi = cnt[j];
				idx = j;
			}
		}

		//가장 적은 노드의 번호 출력
		cout << idx << ' ';
		cnt[idx] = INT32_MAX;

		//연결된 노드의  cnt 감소
		for (int j = 0; j < (int)v[idx].size(); j++) {
			int next = v[idx][j];
			cnt[next]--;
		}
		v[idx].clear();
	}


	return 0;
}
