#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<string>
using namespace std;

stack<int>s;		//사용할 스택
queue<int> ary;		//주어지는 수열: 수서대로 참조만 하므로 큐 사용
string rst;			//결과가 저장될 문자열
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		ary.push(tmp);
	}

	int num = 1;	//1부터 N까지 순서대로 증가하며 push할 수

	//ary의 첫 번째 수까지 1부터 push
	while (num <= ary.front()) {
		s.push(num++);
		rst += '+';
	}

	//무조건 ary의 첫 번째 수는 pop된다
	rst += '-';
	s.pop();
	ary.pop();

	bool flag = true;	//중간에 끝나버리면 false
	while (1) {
		if (ary.empty())break;	//참조할 수열이 모두 끝나면 동작 끝

		int cur = ary.front();	//현재 참조할 값

		if (s.empty() || cur > s.top()) {	//스택이 비어있거나, top보다 참조할 값이 더 클 때
			s.push(num++);
			rst += '+';
		}
		else if (s.top() == cur) {	//top과 참조할 값이 같으면 pop
			rst += '-';
			ary.pop();
			s.pop();
		}
		else if (cur < s.top()) {	//top이 참조할 값보다 커버리면 불가능
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