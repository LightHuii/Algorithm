#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;

#define MAX 1100000
int n, m;
bool flag = false;
int parent[MAX] = { 0, };

int find(int a) {
	if (parent[a] == a)
		return a;
	else
		//�׷� ��ǥ�� ã����, parent �迭�� �����Ѵ�.
		//���� ������ �ݺ��� �� O(1)�� ���� ����
		return parent[a] = find(parent[a]);
}

int main()
{
	int cmd, a, b;
	scanf("%d %d", &n, &m);

	//�ڱ� �ڽ��� parent�� ����
	for (int i = 0; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &cmd, &a, &b);
		if (cmd == 0) {
			//unite
			int p1 = find(a);
			int p2 = find(b);
			parent[p2] = p1;
		}
		else {
			//�θ� ���ٸ� == ���� �׷��̶��
			if (find(a) == find(b))
				printf("yes\n");
			else
				printf("no\n");
		}
	}

	return 0;
}