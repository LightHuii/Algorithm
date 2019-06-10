#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 8
int ary[MAX];
int rst[MAX];
bool selected1[MAX];	//�迭�� �ε����� �ߺ��� ��Ÿ��
bool selected2[10001];	//�� ���� �ߺ��� ��Ÿ��
int N, M;

void dfs(int cnt, int idx) {
	if (cnt == M) {
		for (int i = 0; i < M; i++)
			printf("%d ", rst[i]);
		putchar('\n');
		return;
	}

	//�ڽ� ������ �Ѿ�� �������� ������ �ߺ��� üũ�Ѵ�
	memset(selected2, false, sizeof(selected2));
	
	for (int i = 0; i < N; i++) {
		if (!selected2[ary[i]] && !selected1[i]) {
			selected1[i] = true;	//�� ���ʿ� ���� �ߺ� üũ
			rst[cnt] = ary[i];

			dfs(cnt + 1, idx + 1);
			selected2[ary[i]] = true;	//���� ���̿� ���� �ߺ� üũ
			selected1[i] = false;
		}
	}

	//�θ� ������ �Ѿ�� ������ �ߺ��� üũ�Ѵ�
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