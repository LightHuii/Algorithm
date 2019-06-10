#include<iostream>
#include<algorithm>
#include<stack>
#include<string>
using namespace std;

int main() {
	string str;
	stack<char>s;
	int cnt = 0;	//결과 값
	bool flag = true;	//true: 레이저를 발사하는 순간: 직전에 '(', false: 직전에 ')'
	
	cin >> str;
	
	int size = str.length();

	for (int i = 0; i < size; i++) {
		// '('가 나오면 
		if (str[i] == '(') {
			flag = true;
			s.push('(');
		}
		else {
			if (flag) {
				flag = false;
				cnt += s.size() - 1;	//현재 스택의 사이즈 - 1 만큼 더해준다.
				s.pop();
			}
			else {
				cnt += 1;	//막대가 끝났으므로 1만 더해준다
				s.pop();
			}
		}
	}

	cout << cnt << endl;

	return 0;
}