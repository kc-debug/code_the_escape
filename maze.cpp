#include <bits/stdc++.h>
using namespace std;

int n_rows, m_cols;
vector<string>maze_grid;
pair<int, int>start_coords,end_coords;

int dr[]={-1, 1, 0, 0};
int dc[]={0, 0, -1, 1};

bool isValid(int r,int c,const vector<vector<bool>>& visited) {
    if (r < 0 || r >= n_rows || c < 0 || c >= m_cols || maze_grid[r][c]=='0' || visited[r][c]) return false;
    return true;
}

vector<pair<int, int>> reconstructPath(const map<pair<int, int>,pair<int, int>>& parent_map,vector<string>& current_maze_copy){
    vector<pair<int, int>> path;
    pair<int, int> current=end_coords;
    while (current!=start_coords){
        path.push_back(current);
        if (current!=end_coords) current_maze_copy[current.first][current.second]='*';
        current=parent_map.at(current);
    }
    path.push_back(start_coords);
    current_maze_copy[start_coords.first][start_coords.second]='S';
    reverse(path.begin(), path.end());
    return path;
}

bool bfs(){
    cout<<"\n--- Running BFS ---"<<endl;
    vector<vector<bool>> visited(n_rows, vector<bool>(m_cols, false));
    map<pair<int, int>,pair<int, int>> parent_map;
    queue<pair<int,int>> q;

    q.push(start_coords);
    visited[start_coords.first][start_coords.second]=true;

    while (!q.empty()) {
        pair<int, int> current=q.front(); q.pop();
        if (current==end_coords){
            cout << "BFS: Path found!" << endl;
            vector<string> maze_copy=maze_grid;
            vector<pair<int, int>> path=reconstructPath(parent_map, maze_copy);
            cout << "Path (BFS): ";
            for (size_t i=0;i<path.size();++i) {
                cout << "(" << path[i].first << "," << path[i].second << ")" << (i< path.size()-1  ? " -> " : "");
            }
            cout<<endl<<"Maze with BFS path:"<<endl;
            for (int r = 0; r < n_rows; ++r) {
                for (int c = 0; c < m_cols; ++c) cout<< maze_copy[r][c];
                cout<<endl;
            }
            return true;
        }

        for (int i=0;i<4;++i) {
            int new_r=current.first+dr[i], new_c=current.second+dc[i];
            if (isValid(new_r,new_c,visited)){
                visited[new_r][new_c]=true;
                parent_map[{new_r, new_c}]=current;
                q.push({new_r, new_c});
            }
        }
    }
    cout << "BFS: No path found." << endl;
    return false;
}

bool dfs_recursive(int r,int c,vector<vector<bool>>& visited,map<pair<int, int>, pair<int, int>>& parent_map){
    visited[r][c]=true;
    if (r==end_coords.first && c==end_coords.second) return true;

    for (int i=0;i<4;++i) {
        int new_r= r + dr[i], new_c = c + dc[i];
        if (isValid(new_r, new_c, visited)){
            parent_map[{new_r, new_c}]={r,c};
            if (dfs_recursive(new_r, new_c, visited, parent_map)) return true;
        }
    }
    return false;
}

bool dfs() {
    cout << "\n--- Running DFS ---" << endl;
    vector<vector<bool>> visited(n_rows, vector<bool>(m_cols, false));
    map<pair<int, int>, pair<int, int>> parent_map;

    if (dfs_recursive(start_coords.first, start_coords.second, visited, parent_map)) {
        cout << "DFS: Path found!" << endl;
        vector<string> maze_copy = maze_grid;
        vector<pair<int, int>> path = reconstructPath(parent_map, maze_copy);
        cout << "Path (DFS): ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << "(" << path[i].first << "," << path[i].second << ")" << (i < path.size() - 1 ? " -> " : "");
        }
        cout<<endl<<"Maze with DFS path:"<<endl;
        for (int  r=0;r<n_rows;++r) {
            for(int c=0;c<m_cols;++c) cout<<maze_copy[r][c];
            cout<<endl;
        }
        return true;
    } else {
        cout <<"DFS: No path found."<< endl;
        return false;
    }
}

void printMaze() {
    cout<<"\nOriginal Maze:"<<endl;
    for(int r=0;r<n_rows;++r) {
        for(int c=0;c<m_cols;++c) cout<<maze_grid[r][c];
        cout<<endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout<<"Enter number of rows (n) and columns (m): ";cin >>n_rows>>m_cols;
    maze_grid.resize(n_rows);
    cout << "Enter the maze grid (" <<n_rows<<" rows, "<<m_cols<<" columns):\n";
    for(int r=0;r<n_rows;++r) {
        cin>>maze_grid[r];
        for(int c=0;c<m_cols;++c) {
            if(maze_grid[r][c]=='S') start_coords={r,c};
            else if (maze_grid[r][c]=='E') end_coords={r,c};
        }
    }
    printMaze();
    bfs();
    dfs();
    return 0;
}
