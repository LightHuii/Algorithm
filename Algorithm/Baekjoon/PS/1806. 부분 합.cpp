#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MAX 100000
long long ary[MAX] = { 0, };
long long tmp[MAX] = { 0, };
int N, S;

int main() {
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> ary[i];

	int rst = INT32_MAX;
	int s = 0, e = 0;
	long long sum = ary[0];

	while (1) {
		// ���� ���� ���� �����ϹǷ�
		if (sum < S) {
			e++;	//���� ���� ������
			if (e >= N)break;	//�ε����� ������ ����
			sum += ary[e];
		}
		else {
			rst = min(rst, e - s + 1);	//���� �ĺ�
			sum -= ary[s];		//���� ���� ���ش�.
			s++;
			if (s >= N)break;
		}
	}

	if (rst == INT32_MAX)
		cout << 0 << endl;
	else
		cout << rst << endl;

	return 0;
}