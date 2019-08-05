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
bool key[200];		//열쇠의 유무
int T, w, h;
vector<pair<int, int>>st;	//가장가리 시작 점
int doc;	//훔친 문서의 수
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//열쇠를 얻는다면 true 그렇지 않다면 false
bool bfs(int y, int x) {
	int ty = y, tx = x;
	queue<pair<int, int>>q;
	//시작점으로 될 수 있는 후보들
	//문의 경우, 열쇠가 있는 경우만 허용한다
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
			//문이라면
			if (map[ny][nx] >= 'A' && map[ny][nx] <= 'Z'){
				if (!key[(int)(map[ny][nx] + gap)])
					continue;	//열쇠가 없다면
			}
			//열쇠라면
			else if (map[ny][nx] >= 'a' && map[ny][nx] <= 'z') {
				ret = true;
				key[(int)map[ny][nx]] = true;
				map[ny][nx] = '.';
			}
			//문서라면
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
		//초기화
		memset(key, false, sizeof(key));
		st.clear();
		doc = 0;

		//입력
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if ((i == 0 || i == h - 1 || j == 0 || j == w - 1) && map[i][j] != '*')
					st.push_back(make_pair(i, j));
			}
		}
		string str;
		cin >> str;
		for (int i = 0; i < (int)str.size(); i++)	//입력된 열쇠 표시
			key[(int)str[i]] = true;

		while (1) {
			bool flag = false;
			for (int i = 0; i < (int)st.size(); i++) {
				int y = st[i].first;
				int x = st[i].second;
				flag |= bfs(y, x);
			}
			//모든 지점에서 아무일도 일어나지 않았다면 끝내기
			if (!flag)break;
		}
		cout << doc << endl;
	}

	return 0;
}