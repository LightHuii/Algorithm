#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

#define MAX 11
int N;
int popu[MAX];
vector<vector<int>>adj;
bool selected[MAX];
bool visited[MAX];
int rst = 10000;

//Ŭ�������� ������ ���� �� ���
void func(int n) {
	visited[n] = true;
	for (int i = 0; i < (int)adj[n].size(); i++) {
		int next = adj[n][i];
		if (!visited[next]) {
			visited[next] = true;
			func(adj[n][i]);
		}
	}
}

//�� ������ ������ �� �� ���
int bfs(int n, bool flag) {
	queue<int>q;
	q.push(n);

	int cnt = 0;
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		visited[curr] = true;
		cnt++;

		for (int i = 0; i < (int)adj[curr].size(); i++) {
			int next = adj[curr][i];
			if (!visited[next] && selected[next] == flag) {
				visited[next] = true;
				q.push(next);
			}
		}
	}

	return cnt;
}

//�� �������� ����� ���� �� �ִ��� Ȯ��
bool check(int cnt) {
	memset(visited, false, sizeof(visited));
	//select�� �� Ȯ��: cnt��
	for (int i = 1; i <= N; i++) {
		if (selected[i]) {
			if (bfs(i, true) != cnt) 
				return false;
			break;
		}
	}
	memset(visited, false, sizeof(visited));
	for (int i = 1; i <= N; i++) {
		if (!selected[i]) {
			if (bfs(i, false) != N - cnt) 
				return false;
			break;
		}
	}
	return true;
}

//cnt�� 0�Ǵ� N���� ���� ����X
//������ �� �ִ� ��� ����� ���� ����
void dfs(int cnt, int curr) {
	//�˻�
	if (cnt >= 1 && cnt < N) {
		if (check(cnt)) {
			int a = 0, b = 0;
			for (int i = 1; i <= N; i++) {
				if (selected[i])
					a += popu[i];
				else
					b += popu[i];
			}

			int tmp = abs(a - b);
			rst = min(rst, tmp);
		}
	}
	else if (cnt >= N)
		return;

	//�ߺ����� ����
	for (int i = curr; i <= N; i++) {
		if (i == curr)continue;
		if (!selected[i]) {
			selected[i] = true;
			dfs(cnt + 1, i);
			selected[i] = false;
		}
	}
}


int main()
{
	cin >> N;
	adj.resize(N + 1);

	for (int i = 1; i <= N; i++)
		cin >> popu[i];
	
	for (int i = 1; i <= N; i++) {
		int cnt;
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			int tmp;
			cin >> tmp;
			adj[i].push_back(tmp);
		}
	}

	//���� ����� ������ 3�� �̻��̸� �� �������� ���� �� ����.
	bool flag = true;
	int cnt = 0;
	memset(visited, false, sizeof(visited));
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {
			func(i);
			cnt++;
		}
	}
	if (cnt >= 3)
		flag = false;

	//���� �� ���� ��
	if (flag) {
		for (int i = 1; i <= N; i++)
			dfs(0, i);
		cout << rst << endl;
	}
	//���� �� ���ٸ�
	else
		cout << -1 << endl;

	return 0;
}