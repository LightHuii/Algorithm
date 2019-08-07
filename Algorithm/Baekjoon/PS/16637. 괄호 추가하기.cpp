#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int N;
int rst = INT32_MIN;

int cal(string str) {
	int n, idx;
	if (str[0] >= '0' && str[0] <= '9') {
		n = str[0] - '0';
		idx = 1;
	}
	else {
		n = 0;
		idx = 0;
	}
	
	int tmp = 0;	//계산 결과 임시 저장
	char op = 0;	//기호 임시 저장
	while (idx < (int)str.size()) {
		if (str[idx] >= '0' && str[idx] <= '9') {
			switch (op){
			case '+': n += str[idx] - '0'; break;
			case '-': n -= str[idx] - '0'; break;
			case '*': n *= str[idx] - '0'; break;
			case '/': n /= str[idx] - '0'; break;
			default:
				break;
			}
		}
		//괄호안의 값을 모두 계산
		else if (str[idx] == '(') {
			int idx2 = idx + 1;
			char op2 = 0;
			tmp = str[idx2] - '0';
			idx2++;

			while (str[idx2] != ')') {
				if (str[idx2] >= '0' && str[idx2] <= '9') {
					switch (op2) {
					case '+': tmp += str[idx2] - '0'; break;
					case '-': tmp -= str[idx2] - '0'; break;
					case '*': tmp *= str[idx2] - '0'; break;
					case '/': tmp /= str[idx2] - '0'; break;
					default:
						break;
					}
				}
				else
					op2 = str[idx2];
				idx2++;
			}

			//마무리
			idx = idx2;
			switch (op) {
			case '+': n += tmp; break;
			case '-': n -= tmp; break;
			case '*': n *= tmp; break;
			case '/': n /= tmp; break;
			default:
				n += tmp;
				break;
			}
		}
		//기호일 때
		else if(str[idx] == '+' || str[idx] == '-' || str[idx] == '*' || str[idx] == '/')
			op = str[idx];

		idx++;
	}

	return n;
}

void dfs(int idx, string str) {
	if (idx >= (int)str.length()) {
		//계산
		int tmp = cal(str);
		/*cout << str << endl;
		cout << "값: " << tmp << endl << endl;*/
		rst = max(rst, tmp);

		return;
	}

	//숫자라면
	if (str[idx] >= '0' && str[idx] <= '9') {
		//앞에 '(' 붙이기
		string tmp = str;
		tmp.insert(tmp.begin() + idx, '(');

		//괄호를 닫을 수 있다면 닫고 다음으로 넘기기
		if (idx + 4 <= (int)tmp.length()) {
			tmp.insert(tmp.begin() + idx + 4, ')');
			dfs(idx + 4, tmp);
		}

		//'(' 지우기
		tmp.erase(tmp.begin() + idx);
	}
	dfs(idx + 1, str);
}

int main()
{
	string str;
	cin >> N;
	cin >> str;

	dfs(0, str);

	cout << rst << endl;

	return 0;
}