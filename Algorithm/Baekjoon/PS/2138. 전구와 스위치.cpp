#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int N;
string s1;
string target, str;

//����ġ ���� �Լ�
void switch_ball(int idx) {
	if (s1[idx] == '0')	s1[idx] = '1';
	else s1[idx] = '0';

	if (idx > 0) {
		if (s1[idx - 1] == '0')	s1[idx - 1] = '1';
		else s1[idx - 1] = '0';
	}

	if (idx < N - 1) {
		if (s1[idx + 1] == '0')	s1[idx + 1] = '1';
		else s1[idx + 1] = '0';
	}
}

int main() {
	int rst = INT32_MAX;
	int cnt = 0;
	cin >> N >> str >> target;

	//idx0 �κ� �ٲٰ� ����
	s1 = str;

	switch_ball(0);
	cnt = 1;	//�� �� ���������Ƿ� 1

	//1���� ���� idx�� target�� �ٸ��� �����ϰ�, �ƴϸ� ��������
	for (int i = 1; i < N; i++) {
		if (target[i - 1] != s1[i - 1]) {
			switch_ball(i);
			cnt++;
		}
	}
	
	//target�� ������ Ȯ��
	bool flag = true;
	for (int i = 0; i < N; i++) {
		if (s1[i] != target[i])
			flag = false;
	}

	if (flag)
		rst = min(rst, cnt);

	//idx0 �ٲ��� �ʰ� ����
	s1 = str;
	cnt = 0;
	flag = true;

	for (int i = 1; i < N; i++) {
		if (target[i - 1] != s1[i - 1]) {
			switch_ball(i);
			cnt++;
		}
	}

	flag = true;
	for (int i = 0; i < N; i++) {
		if (s1[i] != target[i])
			flag = false;
	}

	if (flag)
		rst = min(rst, cnt);
	
	if (rst == INT32_MAX)cout << -1 << endl;
	else
		cout << rst << endl;

	return 0;
}