#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
#include<stack>
using namespace std;

#define MAX 100000
int N, K;
int visited[MAX + 1];	//-1�� �ʱ�ȭ, ���� ��ǥ���� ����
int rst, pre_num;

void bfs() {
	queue<tuple<int, int, int>>q;	//�ð�, ���� ��ǥ, ���� ��ǥ
	q.push(make_tuple(0, N, N));

	while (!q.empty()) {
		int curr = get<1>(q.front());	//����
		int pre = get<2>(q.front());	//����
		int t = get<0>(q.front());		//�ð�
		q.pop();

		//�����ϸ� �ð�, ���� ��ǥ(������) ����
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

	//N ������ ��ǥ���� �������� ������ ����
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