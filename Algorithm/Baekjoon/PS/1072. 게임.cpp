#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1000000001		//10��
long long X, Y, Z;

int main(void)
{
	cin >> X >> Y;
	Z = (Y * 100) / X;	//ó�� �־����� �·�
	if (Z >= 99) {		//�·��� 99% �̻��̸� ���̻� �ٲ� �� ����
		cout << -1 << endl;
		return 0;
	}

	//�̺�Ž��
	long long l = 0, r = MAX;
	long long mid = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		long long z = ((Y + mid) * 100) / (X + mid);

		//������ �Ǵ� �·� Z���� ũ�� �ִ� ������ ���δ�.
		if (z > Z)
			r = mid - 1;
		//�·� Z�� ���ų� ������, �ּ� ������ �ø���.
		else
			l = mid + 1;
	}

	cout << l << endl;
	
	return 0;
}