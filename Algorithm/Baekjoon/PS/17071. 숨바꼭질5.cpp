#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct n {
	int left, right;		//홀, 짝
}node;

#define MAX 500000
node visited[MAX + 1];	//들렸을 당시의 시간을 저장
int N, K;
int scale = 1;	//동생 이동 단위 스케일
int td = 0;		//동생의 시간

int bfs() {
	//수빈의 현재 좌표는 큐에 들어가고, 동생의 좌표는 전역변수이며 계속 증가한다.
	queue<pair<int, int>>q;	//이동 시간, 수빈의 좌표
	q.push(make_pair(0, N));
	visited[N].right = 0;		//0초

	while (!q.empty()) {
		int size = q.size();
		
		//들린 적이 있는데, 당시 홀수고, 이번에도 홀수 시간이라면 현재 동생의 시간 출력
		if (visited[K].left >= 0 && visited[K].left % 2 == td % 2)
			return td;
		//들린 적이 있는데, 당시 짝수고, 이번에도 짝수 시간이라면 현재 동생의 시간 출력
		else if (visited[K].right >= 0 && visited[K].right % 2 == td % 2)
			return td;

		while (size--) {
			int curr = q.front().second;
			int t = q.front().first;
			q.pop();

			//현재 값이 동생 좌표라면
			if (curr == K)
				return t;

			if (curr * 2 <= MAX) {
				//다음 시간이 홀수고, 아직 한 번도 들리지 않았다면, 현재 시간을 홀수에 기록
				if ((t + 1) % 2 == 1) {
					if (visited[curr * 2].left == -1)
					{
						visited[curr * 2].left = t + 1;
						q.push(make_pair(t + 1, curr * 2));
					}
				}
				//다음 시간이 짝수고, 아직 한 번도 들리지 않았다면, 현재 시간을 짝수에 기록
				else {
					if (visited[curr * 2].right == -1)
					{
						visited[curr * 2].right = t + 1;
						q.push(make_pair(t + 1, curr * 2));
					}
				}
			}
			if (curr + 1 <= MAX) {
				if ((t + 1) % 2 == 1) {
					if (visited[curr + 1].left == -1)
					{
						visited[curr + 1].left = t + 1;
						q.push(make_pair(t + 1, curr + 1));
					}
				}
				else {
					if (visited[curr + 1].right == -1)
					{
						visited[curr + 1].right = t + 1;
						q.push(make_pair(t + 1, curr + 1));
					}
				}
			}

			if (curr - 1 >= 0) {
				if ((t + 1) % 2 == 1) {
					if (visited[curr - 1].left == -1)
					{
						visited[curr - 1].left = t + 1;
						q.push(make_pair(t + 1, curr - 1));
					}
				}
				else {
					if (visited[curr - 1].right == -1)
					{
						visited[curr - 1].right = t + 1;
						q.push(make_pair(t + 1, curr - 1));
					}
				}
			}
		}

		//동생의 좌표, 시간 증가
		K += (scale++);
		if (K > MAX)return -1;
		td++;
	}

	return -1;
}

int main() {
	cin >> N >> K;

	//초기화
	for (int i = 0; i <= MAX; i++) {
		visited[i].left = -1;
		visited[i].right = -1;
	}
	cout << bfs() << endl;

	return 0;
}