#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 50000
int N, T;
int height[MAX];

int main(void)
{
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> height[i];
		
		//�� ���� index
		int idx1 = 0, idx2 = 1;
		int rst = 0;
		while (idx1 < N && idx2 < N) {
			int left = 0, right = 0;

			//idx2 �����ϸ� ���� �κ� ���� ����
			while (idx2 < N && height[idx2 - 1] < height[idx2]) {
				left++;
				idx2++;
			}

			//��� ���� �� ���ǿ� ���� �ʴٸ�
			if (left == 0 || idx2 == N) {
				if (idx2 == N)break;
				else {
					idx1 = idx2;
					idx2 = idx1 + 1;
					continue;
				}
			}

			//���� ������ �´ٸ�
			idx1 = idx2 - 1;
			while (idx2 < N && height[idx2 - 1] > height[idx2]) {
				right++;
				idx2++;
			}

			//�ϴ� ������ �ϳ��� ������
			rst += left * right;

			//���� ���� ����� �ؾ� �Ѵٸ�
			if (idx2 < N) 
				idx1 = idx2 - 1;
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}
	return 0;
}