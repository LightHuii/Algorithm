#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<vector>
#include<string>
using namespace std;

#define MAX 100
#define gap 'a' - 'A'
char map[MAX][MAX];
bool visited[MAX][MAX];
bool key[200];		//������ ����
int T, w, h;
vector<pair<int, int>>st;	//���尡�� ���� ��
int doc;	//��ģ ������ ��
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//���踦 ��´ٸ� true �׷��� �ʴٸ� false
bool bfs(int y, int x) {
	int ty = y, tx = x;
	queue<pair<int, int>>q;
	//���������� �� �� �ִ� �ĺ���
	//���� ���, ���谡 �ִ� ��츸 ����Ѵ�
	if ((map[y][x] == '.') || (map[y][x]=='$')||(map[y][x] >= 'A' && map[y][x] <= 'Z' && (key[(int)(map[y][x] + gap)])))
		q.push(make_pair(y, x));
	memset(visited, false, sizeof(visited));

	bool ret = false;
	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		visited[y][x] = true;
		q.pop();

		if (map[y][x] == '$') {
			doc++;
			map[y][x] = '.';
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= h || nx < 0 || nx >= w)continue;
			if (visited[ny][nx] || map[ny][nx] == '*')continue;
			//���̶��
			if (map[ny][nx] >= 'A' && map[ny][nx] <= 'Z'){
				if (!key[(int)(map[ny][nx] + gap)])
					continue;	//���谡 ���ٸ�
			}
			//������
			else if (map[ny][nx] >= 'a' && map[ny][nx] <= 'z') {
				ret = true;
				key[(int)map[ny][nx]] = true;
				map[ny][nx] = '.';
			}
			//�������
			else if (map[ny][nx] == '$') {
				doc++;
				map[ny][nx] = '.';
			}

			visited[ny][nx] = true;
			q.push(make_pair(ny, nx));			
		}
	}

	return ret;
}

int main()
{
	cin >> T;
	int Ttmp = T;

	while (Ttmp--) {
		cin >> h >> w;
		//�ʱ�ȭ
		memset(key, false, sizeof(key));
		st.clear();
		doc = 0;

		//�Է�
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if ((i == 0 || i == h - 1 || j == 0 || j == w - 1) && map[i][j] != '*')
					st.push_back(make_pair(i, j));
			}
		}
		string str;
		cin >> str;
		for (int i = 0; i < (int)str.size(); i++)	//�Էµ� ���� ǥ��
			key[(int)str[i]] = true;

		while (1) {
			bool flag = false;
			for (int i = 0; i < (int)st.size(); i++) {
				int y = st[i].first;
				int x = st[i].second;
				flag |= bfs(y, x);
			}
			//��� �������� �ƹ��ϵ� �Ͼ�� �ʾҴٸ� ������
			if (!flag)break;
		}
		cout << doc << endl;
	}

	return 0;
}