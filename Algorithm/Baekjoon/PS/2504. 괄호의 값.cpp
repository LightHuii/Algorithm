#include<iostream>
#include<algorithm>
#include<stack>
#include<string>
using namespace std;

int main() {
	stack<pair<char, int>>s;	//문자, 숫자: 문자면 숫자는 0, 숫자면 문자는 '.'
	string str;

	cin >> str;

	bool flag = true;	//괄호열이 올바른지 판단
	int size = str.size();

	//입력된 문자열 순서대로 진행
	for (int i = 0; i < size; i++) {

		//여는 괄호라면 푸쉬
		if (str[i] == '(' || str[i] == '[')
			s.push(make_pair(str[i], 0));
		else {
			//닫는 괄호인데 비어 있으면 종료
			if (s.empty()) {
				flag = false;
				break;
			}

			//비어 있지 않을 경우
			if (str[i] == ')') {
				//바로 닫히는 경우
				if (s.top().first == '(') {
					s.pop();
					s.push(make_pair('.', 2));
				}
				//바로 닫히지 않는 경우 그 사이의 숫자를 모두 더하고 2를 곱해준다
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

	//다 끝났는데 스택의 크기가 2이상이라면 -> 숫자가 여러 개이기 때문에 모두 더해준다.
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
	//하나만 남았다면 정답
	else if (s.size() == 1) {
		tmp = s.top().second;
	}

	if (flag)
		cout << tmp << endl;
	else
		cout << 0 << endl;

	return 0;
}
