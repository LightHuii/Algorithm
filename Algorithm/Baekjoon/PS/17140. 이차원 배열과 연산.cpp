#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

#define MAX 101
int inital_map[4][4] = { 0, };	//ó������ ���� ��
int R, C;	//������ ��, ���� ����
int r, c, k;

int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			cin >> inital_map[i][j];

	int rst = 0;
	R = 3;		//�� ������ �ִ밪
	C = 3;		//�� ������ �ִ밪

	priority_queue<pair<int, int>>pq[101];	//���Ŀ� ���

	int whatcal;	//������ � �������� ǥ��

	while (1) {
		int map[MAX][MAX] = { 0, };

		//ó������ ���
		if (rst == 0) {
			for (int i = 1; i <= 3; i++)
				for (int j = 1; j <= 3; j++)
					map[i][j] = inital_map[i][j];
		}
		//���ĺ��� ���
		else {
			//pq������ map�� ����
			//������ R�����̶��
			if (whatcal == 1) {
				//R(�ִ� �� ����)��ŭ �ݺ�
				for (int i = 1; i <= R; i++) {
					int size = pq[i].size();
					int idx =1;

					for (int j = 0; j < size; j++) {
						int cnt = -pq[i].top().first;
						int num = -pq[i].top().second;
						pq[i].pop();

						map[i][idx++] = num;
						map[i][idx++] = cnt;

						if (idx > 100 && !pq[i].empty()) {
							int size2 = pq[i].size();
							while (size2--)
								pq[i].pop();
						}
					}
				}
			}
			//������ C�����̶��
			else if (whatcal == 2) {
				//C(�ִ� �� ����)��ŭ �ݺ�
				for (int i = 1; i <= C; i++) {
					int size = pq[i].size();
					int idx = 1;
					//ma = max(ma, size * 2);

					for (int j = 0; j < size; j++) {
						int cnt = -pq[i].top().first;
						int num = -pq[i].top().second;
						pq[i].pop();

						map[idx++][i] = num;
						map[idx++][i] = cnt;

						if (idx > 100 && !pq[i].empty()) {
							int size2 = pq[i].size();
							while (size2--)
								pq[i].pop();
						}
					}
				}
			}
		}

		//�Ǵ�
		if (map[r][c] == k)break;
		else if (rst > 100) {
			rst = -1;
			break;
		}

		//R ���� 
		if (R >= C) {
			int ma = 0;		//�ִ� ���� ���� ����

			for (int i = 1; i <= R; i++) {
				int cnt_num[MAX] = { 0, };		//�� ���� �� üũ
				for (int j = 1; j <= C; j++)
					if (map[i][j] > 0)
						cnt_num[map[i][j]]++;
				
				for (int j = 1; j <= 100; j++)
					if (cnt_num[j] > 0)
						pq[i].push(make_pair(-cnt_num[j], -j));

				ma = max(ma, (int)pq[i].size() * 2);
			}
			C = ma;
			whatcal = 1;
		}
		//C����
		else {
			int ma = 0;		//�ִ� ���� ���� ����

			for (int i = 1; i <= C; i++) {
				int cnt_num[MAX] = { 0, };		//�� ���� �� üũ
				for (int j = 1; j <= R; j++)
					if (map[j][i] > 0)
						cnt_num[map[j][i]]++;

				for (int j = 1; j <= 100; j++)
					if (cnt_num[j] > 0)
						pq[i].push(make_pair(-cnt_num[j], -j));

				ma = max(ma, (int)pq[i].size() * 2);
			}
			R = ma;
			whatcal = 2;
		}

		rst++;
	}

	cout << rst << endl;

	return 0;
}