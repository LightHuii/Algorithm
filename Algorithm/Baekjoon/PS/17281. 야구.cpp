#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 50	//�ִ� �̴� ��
int hitter[MAX][10];	//�� �̴׿��� 1~9�� Ÿ���� ���
int ary[10];		//������ Ÿ�� ����
bool visited[10];	//Ÿ�� ���� üũ
int N;
int rst = 0;		//��� ��

//��� �̴��� ���� ������ ��� ���� �� ��� ���� ����
int inning() {
	int order = 1, hitter_num;	//���� Ÿ�� ����: 1~9, ������ ���� ���� ��ȣ
	int out_cnt = 0;	//�ƿ� ����
	bool base[4] = { 0, };	//1~3�� ���̽��� �ִ� ����
	int inning_num = 0;	//���� �̴� ��ȣ
	int score = 0;		//����

	while (inning_num < N) {
		while (out_cnt < 3) {
			hitter_num = ary[order];	//���� order�� Ÿ�� ��ȣ

			//�ƿ�
			if (hitter[inning_num][hitter_num] == 0)
				out_cnt++;
			//��Ÿ
			else if (hitter[inning_num][hitter_num] == 1) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				base[3] = base[2];
				base[2] = base[1];
				base[1] = true;
			}
			//2��Ÿ
			else if (hitter[inning_num][hitter_num] == 2) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				if (base[2]) {
					score++;
					base[2] = false;
				}
				base[3] = base[1];
				base[1] = false;
				base[2] = true;
			}
			//3��Ÿ
			else if (hitter[inning_num][hitter_num] == 3) {
				if (base[3])
					score++;
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				base[3] = true;
			}
			//Ȩ��
			else if (hitter[inning_num][hitter_num] == 4) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				score++;
			}

			order = (order + 1) % 10;
			if (order == 0)order++;		//���� ����
		}
		out_cnt = 0;
		for (int i = 1; i <= 3; i++)
			base[i] = false;

		inning_num++;	//���� �̴�
	}

	return score;
}

//Ÿ�� ���� ���ϱ�
void dfs(int cnt) {
	if (cnt >= 10) {
		int tmp = inning();
		rst = max(rst, tmp);
	
		return;
	}

	//4�� Ÿ�ڸ� ������ ��
	if (cnt == 4)
		dfs(5);
	else {
		for (int i = 2; i <= 9; i++) {
			if (!visited[i]) {
				visited[i] = true;
				ary[cnt] = i;

				dfs(cnt + 1);

				visited[i] = false;
			}
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 1; j <= 9; j++)
			cin >> hitter[i][j];

	//4�� ° ������ 1�� ����
	visited[1] = true;
	ary[4] = 1;

	dfs(1);

	cout << rst << endl;

	return 0;
}