#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 50
int m, n;
int map[MAX][MAX];
int visited[MAX][MAX];		//�� ��ǥ�� ���� �� ��ȣ�� ����
int dy[] = { 0,-1,0,1 };
int dx[] = { -1,0,1,0 };	//���ϵ���
int first = 0, second = 0, third = 0;	//��� ��
bool room_adj[MAX * MAX][MAX * MAX];	//��� �� ���̰� ������ �ִ��� Ȯ��
bool visited2[MAX][MAX];				//�� ��° bfs�� ���
int room_big[MAX * MAX] = { 0, };		//�� ���� ũ�� ����

//�� ���� ũ�⸦ ����
int roomArea(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int cnt = 0;
	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		visited[y][x] = first;
		cnt++;

		for (int i = 0; i < 4; i++) {
			int mul = 1 << i;
			if (map[y][x] & mul)continue;	//0�� ���;� ���� ��
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= m || nx < 0 || nx >= n)continue;

			if (visited[ny][nx] == -1) {
				visited[ny][nx] = first;
				q.push(make_pair(ny, nx));
			}
		}
	}
	return cnt;
}

//�� ���� �湮�ϸ� ��� �� ���̰� ������ �ִ��� üũ�ϴ� �Լ�
void bfs(int num, int y, int x) {		//�� ��ȣ
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		visited2[y][x] = true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= m || nx < 0 || nx >= n)continue;
			if (visited[ny][nx] != num) {
				room_adj[num][visited[ny][nx]] = true;
				room_adj[visited[ny][nx]][num] = true;
			}
			else if (!visited2[ny][nx]) {
				visited2[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			visited[i][j] = -1;
		}
	}

	//���� ����, ���� ū ���� ũ��, ��� ��ǥ�� ���� �� ��ȣ ����
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == -1) {
				int tmp = roomArea(i, j);
				second = max(second, tmp);
				room_big[first] = tmp;	//���� ũ�� ����
				first++;
			}
		}
	}

	//�� ���� ���� üũ
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited2[i][j]) {
				bfs(visited[i][j], i, j);	//�� ��ȣ
			}
		}
	}

	//������ ���� ũ���� ���� ���� ū ���� ã��
	for (int i = 0; i < first - 1; i++) {
		for (int j = i + 1; j < first; j++) {
			if (room_adj[i][j])
				third = max(third, room_big[i] + room_big[j]);
		}
	}

	cout << first << endl << second << endl << third << endl;

	return 0;
}