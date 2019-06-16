#include<iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;

char str[3000];
char chk[100];
int str_len, chk_len;

int main() {
	fgets(str, 3000, stdin);
	fgets(chk, 100, stdin);
	int cnt = 0;

	str_len = strlen(str) - 1;
	chk_len = strlen(chk) - 1;

	for (int i = 0; i < str_len; i++) {
		//다르면 스킵
		if (str[i] != chk[0]) continue;
		
		//같다면
		bool flag = true;
		int idx = i;
		for (int j = 1; j < chk_len; j++) {
			idx++;
			if (str[idx] != chk[j]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			cnt++;
			i = idx;
		}
	}

	cout << cnt << endl;

	return 0;
}