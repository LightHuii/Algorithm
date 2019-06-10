#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 8
int ary[MAX];
int rst[MAX];
bool selected1[MAX];	//배열의 인덱스의 중복을 나타냄
bool selected2[10001];	//각 수의 중복을 나타냄
int N, M;

void dfs(int cnt, int idx) {
	if (cnt == M) {
		for (int i = 0; i < M; i++)
			printf("%d ", rst[i]);
		putchar('\n');
		return;
	}

	//자식 순서로 넘어가기 전까지만 숫자의 중복을 체크한다
	memset(selected2, false, sizeof(selected2));
	
	for (int i = 0; i < N; i++) {
		if (!selected2[ary[i]] && !selected1[i]) {
			selected1[i] = true;	//한 차례에 대한 중복 체크
			rst[cnt] = ary[i];

			dfs(cnt + 1, idx + 1);
			selected2[ary[i]] = true;	//같은 깊이에 대한 중복 체크
			selected1[i] = false;
		}
	}

	//부모 순서로 넘어가기 전까지 중복을 체크한다
	memset(selected2, false, sizeof(selected2));
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &ary[i]);

	sort(ary, ary + N);

	dfs(0, 0);

	return 0;
}