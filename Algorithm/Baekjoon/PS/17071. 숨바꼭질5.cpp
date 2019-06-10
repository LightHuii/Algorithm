#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct n {
	int left, right;		//Ȧ, ¦
}node;

#define MAX 500000
node visited[MAX + 1];	//����� ����� �ð��� ����
int N, K;
int scale = 1;	//���� �̵� ���� ������
int td = 0;		//������ �ð�

int bfs() {
	//������ ���� ��ǥ�� ť�� ����, ������ ��ǥ�� ���������̸� ��� �����Ѵ�.
	queue<pair<int, int>>q;	//�̵� �ð�, ������ ��ǥ
	q.push(make_pair(0, N));
	visited[N].right = 0;		//0��

	while (!q.empty()) {
		int size = q.size();
		
		//�鸰 ���� �ִµ�, ��� Ȧ����, �̹����� Ȧ�� �ð��̶�� ���� ������ �ð� ���
		if (visited[K].left >= 0 && visited[K].left % 2 == td % 2)
			return td;
		//�鸰 ���� �ִµ�, ��� ¦����, �̹����� ¦�� �ð��̶�� ���� ������ �ð� ���
		else if (visited[K].right >= 0 && visited[K].right % 2 == td % 2)
			return td;

		while (size--) {
			int curr = q.front().second;
			int t = q.front().first;
			q.pop();

			//���� ���� ���� ��ǥ���
			if (curr == K)
				return t;

			if (curr * 2 <= MAX) {
				//���� �ð��� Ȧ����, ���� �� ���� �鸮�� �ʾҴٸ�, ���� �ð��� Ȧ���� ���
				if ((t + 1) % 2 == 1) {
					if (visited[curr * 2].left == -1)
					{
						visited[curr * 2].left = t + 1;
						q.push(make_pair(t + 1, curr * 2));
					}
				}
				//���� �ð��� ¦����, ���� �� ���� �鸮�� �ʾҴٸ�, ���� �ð��� ¦���� ���
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

		//������ ��ǥ, �ð� ����
		K += (scale++);
		if (K > MAX)return -1;
		td++;
	}

	return -1;
}

int main() {
	cin >> N >> K;

	//�ʱ�ȭ
	for (int i = 0; i <= MAX; i++) {
		visited[i].left = -1;
		visited[i].right = -1;
	}
	cout << bfs() << endl;

	return 0;
}