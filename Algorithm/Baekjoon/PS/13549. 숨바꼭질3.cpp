#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

#define MAX 100000
int N, K;
bool visited[MAX + 1];

int bfs() {
	priority_queue<pair<int, int>>q;	//걸린 시간, 현재 좌표
	q.push(make_pair(0, -N));
	visited[N] = true;

	while (!q.empty()) {
		int curr = -q.top().second;
		int t = -q.top().first;
		q.pop();

		if (curr == K)
			return t;

		//*2
		if (curr * 2 <= MAX) {
			if (!visited[curr * 2]) {
				visited[curr * 2] = true;
				q.push(make_pair(-t, -curr * 2));
			}
		}

		//1 증가
		if (curr + 1 <= MAX) {
			if (!visited[curr + 1]) {
				visited[curr + 1] = true;
				q.push(make_pair(-(t + 1), -(curr + 1)));
			}
		}
		//1 감소
		if (curr - 1 >= 0) {
			if (!visited[curr - 1]) {
				visited[curr - 1] = true;
				q.push(make_pair(-(t + 1), -(curr - 1)));
			}
		}
	}
}

int main() {
	cin >> N >> K;

	cout << bfs() << endl;

	return 0;
}