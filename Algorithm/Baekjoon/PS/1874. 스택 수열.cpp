#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<string>
using namespace std;

stack<int>s;		//����� ����
queue<int> ary;		//�־����� ����: ������� ������ �ϹǷ� ť ���
string rst;			//����� ����� ���ڿ�
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		ary.push(tmp);
	}

	int num = 1;	//1���� N���� ������� �����ϸ� push�� ��

	//ary�� ù ��° ������ 1���� push
	while (num <= ary.front()) {
		s.push(num++);
		rst += '+';
	}

	//������ ary�� ù ��° ���� pop�ȴ�
	rst += '-';
	s.pop();
	ary.pop();

	bool flag = true;	//�߰��� ���������� false
	while (1) {
		if (ary.empty())break;	//������ ������ ��� ������ ���� ��

		int cur = ary.front();	//���� ������ ��

		if (s.empty() || cur > s.top()) {	//������ ����ְų�, top���� ������ ���� �� Ŭ ��
			s.push(num++);
			rst += '+';
		}
		else if (s.top() == cur) {	//top�� ������ ���� ������ pop
			rst += '-';
			ary.pop();
			s.pop();
		}
		else if (cur < s.top()) {	//top�� ������ ������ Ŀ������ �Ұ���
			flag = false;
			break;
		}
	}

	if (flag) {
		for (int i = 0; i < (int)rst.size(); i++)
			printf("%c\n", rst[i]);
	}
	else {
		printf("NO\n");
	}
	return 0;
}