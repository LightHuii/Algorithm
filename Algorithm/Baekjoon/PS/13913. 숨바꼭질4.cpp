#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
#include<stack>
using namespace std;

#define MAX 100000
int N, K;
int visited[MAX + 1];	//-1로 초기화, 이전 좌표들을 저장
int rst, pre_num;

void bfs() {
	queue<tuple<int, int, int>>q;	//시간, 현재 좌표, 이전 좌표
	q.push(make_tuple(0, N, N));

	while (!q.empty()) {
		int curr = get<1>(q.front());	//현재
		int pre = get<2>(q.front());	//이전
		int t = get<0>(q.front());		//시간
		q.pop();

		//도착하면 시간, 현재 좌표(마지막) 저장
		if (curr == K) {
			rst = t;
			pre_num = curr;
			return;
		}

		if (curr * 2 <= MAX && visited[curr * 2] == -1) {
			visited[curr * 2] = curr;
			q.push(make_tuple(t + 1, curr * 2, curr));
		}
		if (curr + 1 <= MAX && visited[curr + 1] == -1) {
			visited[curr + 1] = curr;
			q.push(make_tuple(t + 1, curr + 1, curr));
		}
		if (curr - 1 >= 0 && visited[curr - 1] == -1) {
			visited[curr - 1] = curr;
			q.push(make_tuple(t + 1, curr - 1, curr));
		}
	}
}

int main() {
	cin >> N >> K;

	for (int i = 0; i <= MAX; i++)
		visited[i] = -1;

	bfs();
	cout << rst << endl << N << ' ';

	//N 이후의 좌표들을 역순으로 저장할 스택
	stack<int>st;
	int curr = pre_num;
	for (int i = 0; i < rst; i++) {
		st.push(curr);
		curr = visited[curr];
	}

	for (int i = 0; i < rst; i++) {
		cout << st.top() << ' ';
		st.pop();
	}

	return 0;
}