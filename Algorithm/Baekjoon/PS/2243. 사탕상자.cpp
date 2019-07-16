#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 2100000
int tree[MAX] = { 0, };
int n, A, B, C;

int main(void)
{
	scanf("%d", &n);
	int deg = 0;	//����
	int two = 1;

	//���� ���ϱ�
	while (1000000 > two) {
		two *= 2;
		deg++;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &A);

		//���� ����
		if (A == 1) {
			scanf("%d", &B);
			int curr = 1;
			while (1) {
				if (tree[curr * 2] >= B) {
					//���� 0�̸� �ٸ� �������� �̵�
					if (tree[curr * 2] == 0)curr = curr * 2 + 1;
					else
						curr *= 2;	//���� �ڽ����� �̵�
				}
				else {
					//���� 0�̸� �ٸ� �������� �̵�
					if (tree[curr * 2 + 1] == 0)curr = curr * 2;
					else {
						//���� �� �ڽ����� �̵��Ѵ�. �� ���� ��ǥ ���� ���� �ڽ� ���� ���༭ ������ �ڽĿ��� �ٷ� ���� �� �ְ� ���ش�.
						B -= tree[curr * 2];
						curr = curr * 2 + 1;
					}
				}
				//���� ��忡 �����ϸ� ��
				if (curr >= two && curr < two * 2)break;
			}

			//��� �� ����
			printf("%d\n", curr - two + 1);
			while (curr > 0) {
				tree[curr]--;
				curr /= 2;
			}
		}
		//���� �ֱ� or ����
		else {
			scanf("%d %d", &B, &C);

			int curr = two + B - 1;
			while (curr > 0) {
				tree[curr] += C;
				curr /= 2;
			}
		}
	}

	return 0;
}
