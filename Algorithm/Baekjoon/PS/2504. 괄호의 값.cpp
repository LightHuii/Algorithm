#include<iostream>
#include<algorithm>
#include<stack>
#include<string>
using namespace std;

int main() {
	stack<pair<char, int>>s;	//����, ����: ���ڸ� ���ڴ� 0, ���ڸ� ���ڴ� '.'
	string str;

	cin >> str;

	bool flag = true;	//��ȣ���� �ùٸ��� �Ǵ�
	int size = str.size();

	//�Էµ� ���ڿ� ������� ����
	for (int i = 0; i < size; i++) {

		//���� ��ȣ��� Ǫ��
		if (str[i] == '(' || str[i] == '[')
			s.push(make_pair(str[i], 0));
		else {
			//�ݴ� ��ȣ�ε� ��� ������ ����
			if (s.empty()) {
				flag = false;
				break;
			}

			//��� ���� ���� ���
			if (str[i] == ')') {
				//�ٷ� ������ ���
				if (s.top().first == '(') {
					s.pop();
					s.push(make_pair('.', 2));
				}
				//�ٷ� ������ �ʴ� ��� �� ������ ���ڸ� ��� ���ϰ� 2�� �����ش�
				else {
					int tmp = 0;
					while (!s.empty() && s.top().first != '(') {
						if (s.top().first == '[') {
							flag = false;
							break;
						}
						tmp += s.top().second;
						s.pop();
					}

					if (!flag || s.empty()) {
						flag = false;
						break;
					}
					s.pop();
					s.push(make_pair('.', tmp * 2));
				}
			}
			else if (str[i] == ']') {
				if (s.top().first == '[') {
					s.pop();
					s.push(make_pair('.', 3));
				}
				else {
					int tmp = 0;
					while (!s.empty() && s.top().first != '[') {
						if (s.top().first == '(') {
							flag = false;
							break;
						}
						tmp += s.top().second;
						s.pop();
					}

					if (!flag || s.empty()) {
						flag = false;
						break;
					}
					s.pop();
					s.push(make_pair('.', tmp * 3));
				}
			}
		}
	}

	//�� �����µ� ������ ũ�Ⱑ 2�̻��̶�� -> ���ڰ� ���� ���̱� ������ ��� �����ش�.
	int tmp = 0;
	if (s.size() >= 2) {
		while (!s.empty()) {
			if (!s.empty() && s.top().first == '(' || s.top().first == '[') {
				flag = false;
				break;
			}

			tmp += s.top().second;
			s.pop();
		}
	}
	//�ϳ��� ���Ҵٸ� ����
	else if (s.size() == 1) {
		tmp = s.top().second;
	}

	if (flag)
		cout << tmp << endl;
	else
		cout << 0 << endl;

	return 0;
}
