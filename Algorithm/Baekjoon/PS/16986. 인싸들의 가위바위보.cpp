#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 10
int A[MAX][MAX];
bool selected[MAX];
int order[4][20];		//����, ����, ��ȣ�� ����
int N, K;
bool rst = false;

int func(int a, int b, int n1, int n2) {
	if (A[n1][n2] == 2)return a;
	else if (A[n1][n2] == 0)return b;
	//����� ��
	else {
		if (a < b)return b;
		else return a;
	}
}

//���������� ���� ��� ������ ������� �ƴ��� ����
bool RPS() {
	int win_cnt[4] = { 0, };	//�� ��� Ƚ�� ���� ����:1, ����:2, ��ȣ:3
	
	bool jiwoo = false;
	int do_cnt[4] = { 0, };		//�� ���������� ���� ����
	int won = 1;	//���� ���� ��ȣ
	int next = 2;	//���� �ºο� �������� ���� ����� ��ȣ

	//�� ���̶� �¼��� ��� ä��� break
	while (1) {
		int winner = func(won, next, order[won][do_cnt[won]++], order[next][do_cnt[next]++]);
		win_cnt[winner]++;	//������ �¼� ����

		//�̹� ���ڰ� �¼��� ä���� ��
		if (win_cnt[winner] >= K) {
			if (winner == 1)jiwoo = true;	//�콼�ڰ� ������
			break;
		}
		next = (won + next) % 4;
		if (next == 0)next = 2;
		won = winner;

		//������ ������ ������ ��
		if (do_cnt[1] >= N)break;
	}

	return jiwoo;
}

//������ ������ ���� ��, ���������� �����Ͽ� ���� ��¿��� �Ǵ�
void dfs(int cnt) {
	//�̹� ���찡 ���������, ���̻� �������� �ʴ´�
	if (rst)return;
	if (cnt >= N) {
		//���������� �����Ͽ� ���찡 ����ߴ��� �Ǵ�
		rst = RPS();
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (!selected[i]) {
			selected[i] = true;
			order[1][cnt] = i;
			dfs(cnt + 1);

			selected[i] = false;
		}
	}

}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> A[i][j];
	for (int i = 2; i <= 3; i++)
		for (int j = 0; j < 20; j++)
			cin >> order[i][j];
	
	dfs(0);
	cout << rst << endl;

	return 0;
}