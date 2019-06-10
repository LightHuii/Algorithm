#include<iostream>
#include<algorithm>
#include<stack>
#include<string>
using namespace std;

int main() {
	string str;
	stack<char>s;
	int cnt = 0;	//��� ��
	bool flag = true;	//true: �������� �߻��ϴ� ����: ������ '(', false: ������ ')'
	
	cin >> str;
	
	int size = str.length();

	for (int i = 0; i < size; i++) {
		// '('�� ������ 
		if (str[i] == '(') {
			flag = true;
			s.push('(');
		}
		else {
			if (flag) {
				flag = false;
				cnt += s.size() - 1;	//���� ������ ������ - 1 ��ŭ �����ش�.
				s.pop();
			}
			else {
				cnt += 1;	//���밡 �������Ƿ� 1�� �����ش�
				s.pop();
			}
		}
	}

	cout << cnt << endl;

	return 0;
}