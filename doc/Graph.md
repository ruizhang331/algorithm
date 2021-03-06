<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Data structure](#data-structure)
  - [Edge List](#edge-list)
  - [Adjacency list](#adjacency-list)
  - [Matrix](#matrix)
  - [Access complexity](#access-complexity)
- [Traversal](#traversal)
  - [Build Graph: from edge list to adjacent List](#build-graph-from-edge-list-to-adjacent-list)
  - [DFS](#dfs)
    - [Check Graph Connection](#check-graph-connection)
    - [evaluate-division](#evaluate-division)
    - [reconstruct-itinerary](#reconstruct-itinerary)
    - [Check Valid Path](#check-valid-path)
    - [Walls and Gates](#walls-and-gates)
  - [BFS](#bfs)
    - [Shortest path](#shortest-path)
      - [Path with Obstable](#path-with-obstable)
    - [Minimum Height Tree](#minimum-height-tree)
    - [Common Ancestor](#common-ancestor)
- [Connected Component(Union Find, DFS, BFS)](#connected-componentunion-find-dfs-bfs)
  - [Basic idea](#basic-idea)
    - [Union find:](#union-find)
    - [DFS/BFS:](#dfsbfs)
    - [Number of island(DFS)](#number-of-islanddfs)
      - [Count number of islands(Union Find)](#count-number-of-islandsunion-find)
    - [Number of connected component(Union Find)](#number-of-connected-componentunion-find)
    - [Number of component with some step count](#number-of-component-with-some-step-count)
      - [Rotting Oranges](#rotting-oranges)
    - [Friends Circle(DFS/BFS)](#friends-circledfsbfs)
    - [Graph Valid Tree](#graph-valid-tree)
    - [Account Merge (Union find)](#account-merge-union-find)
    - [Making A Large Island](#making-a-large-island)
- [Topological Sort](#topological-sort)
  - [Top Sort](#top-sort)
      - [DFS](#dfs-1)
      - [BFS](#bfs-1)
      - [Detect Circle via Topo Sort](#detect-circle-via-topo-sort)
    - [Task/Course schedule](#taskcourse-schedule)
      - [Can finish all course](#can-finish-all-course)
      - [Find courses order](#find-courses-order)
      - [Find out all finish path](#find-out-all-finish-path)
      - [Parallel Courses(Max Depth in DAG)](#parallel-coursesmax-depth-in-dag)
    - [Alien dictionary](#alien-dictionary)
    - [Minimum Height Trees](#minimum-height-trees)
  - [Example](#example)
    - [Sequence Reconstruction](#sequence-reconstruction)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Data structure
There are three basic ways to represent a graph in memory (objects and pointers, matrix, and adjacency list.

## Edge List
One simple way to represent a graph is just a list, or array, of |E| edges, which we call an edge list.

It looks like
```
[ [0,1], [0,6], [0,8], [1,4], [1,6], [1,9], [2,4], [2,6], [3,4], [3,5],
[3,8], [4,5], [4,9], [7,8], [7,9] ]
```

## Adjacency list

Example is
```
[ [1, 6, 8],
  [0, 4, 6, 9],
  [4, 6],
  [4, 5, 8],
  [1, 2, 3, 5, 9],
  [3, 4],
  [0, 1, 2],
  [8, 9],
  [0, 3, 7],
  [1, 4, 7] ]
```
Vertex numbers in an adjacency list are not required to appear in any particular order, though it is often convenient to list them in increasing order, as in this example.
We can get to each vertex's adjacency list in constant time, because we just have to index into an array. To find out whether an edge (i,j) is present in the graph, we go to i's adjacency list in constant time and then look for j in i's adjacency list.

Code to visit each node and do some stuff
```CPP
for(int i=0;i<graph.size();i++){
  for(int j=0;j<graph[i].size();j++){
    do_stuff(graph[i][j])
  }
}

```

## Matrix

Entire matrix to represent it


## Access complexity
* Edge list
1.	Adding an edge – O(1);
2.	Deleting an edge – O(1);
3.	Answering the question “is there an edge between i and j” – O(1);
4.	Finding the successors of a given vertex – O(n);
5.	Finding (if exists) a path between two vertices – O(n2);

* Adjacent List

1.	Adding an edge – O(log(n));
2.	Deleting an edge – O(log(n));
3.	Answering the question “is there an edge between i and j” – O(log(n));
4.	Finding the successors of a given vertex – O(k), where “k” is the length of the lists containing the successors of i;
5.	Finding (if exists) a path between two vertices – O(n+m) – where m <= n;


# Traversal

## Build Graph: from edge list to adjacent List
```CPP
/*
Edge list to Graph
*/
//two commonly used data structure to build graph
//if no associated path is needed, key is some vertex, value is all vertexes linked to key
unordered_map<vertex, unordered_set<vertex>> m;
//key is some vertex, value is a map, with which vertex is vertex linked to key's vertex, and val is some parameter associated with path
unordered_map<vertex, unordered_map<vertex, val>> m;

for (int i = 0; i < edge.size(); i++) {
	//for first case
	m[edge[i].first].insert(edge[i].second);
	m[edge[i].second].insert(edge[i].first);
	//for second case
	m[edge[i].first].insert(make_pair(edge[i].second,val[i]));
	m[edge[i].second].insert(make_pair(edge[i].firsr, 1/val[i]));
}
```

## DFS

```CPP
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}
```

### Check Graph Connection

https://leetcode.com/problems/critical-connections-in-a-network/

There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some server unable to reach some other server.

Return all critical connections in the network in any order.

```

Example 1:

Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
```

```CPP
//Key idea is to find cycle, if node is in cycle then it is not in critical path


```


### evaluate-division
```CPP
//https://leetcode.com/problems/evaluate-division/
/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].
The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
According to the example above:
equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
*/

//method 1:
class Solution {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		//map: key is string, and value is vector of pair <string,float>
		//key: string
		//value: unordered_map<string,val> string is , value is dinomination
		int len = equations.size();
		vector<string> root(len);

		unordered_map<string, unordered_map<string, double>> m;
		for (int i = 0; i<len; i++) {
			string s1 = equations[i].first;
			string s2 = equations[i].second;

			pair<string, double> tmp;

			tmp.first = s2;
			tmp.second = values[i];
			m[s1].insert(tmp);
			//reverse way
			tmp.first = s1;
			tmp.second = 1 / values[i];
			m[s2].insert(tmp);

		}
		vector<double> ret;
		for (int i = 0; i<queries.size(); i++) {
			unordered_set<string> visited;
			//need to have a visited mark to record visited and avoid loop.
			double res = dfs(m, visited, queries[i].first, queries[i].second);
			if (res)
				ret.push_back(res);
			else
				ret.push_back(-1);
		}

		return ret;
	}


	double dfs(unordered_map<string, unordered_map<string, double>> &m, unordered_set<string>& visited, string s, string e) {
		if (m.find(s) == m.end())
			return -1.0;
		if (s == e)
			return 1.0;
		//found the direct
		if (m[s].find(e) != m[s].end()) {
			return m[s][e];
		}

		for (auto i : m[s]) {
			if (visited.find(i.first) == visited.end()) {
				visited.insert(i.first);
				double res = dfs(m, visited, i.first, e);
				if (res)
					return i.second*res;
			}
		}

		return 0;
	}
};

```

### reconstruct-itinerary


```CPP
//https://leetcode.com/problems/reconstruct-itinerary/
/*
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.
Note:
If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
*/

class Solution {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		vector<string> ret;
		//graph: key is airport and val is set of destination from its airport
		//use set to ensure the lexical order
		//need to use multiset in order to keep mutiple cases for airport
		unordered_map<string, multiset<string>> g;
		for (int i = 0; i<tickets.size(); i++) {
			pair<string, string> cur = tickets[i];
			string src = cur.first;
			string dest = cur.second;
			g[src].insert(dest);
		}
		dfs(ret, g, "JFK");
		reverse(ret.begin(), ret.end());
		return ret;
	}

	void dfs(vector<string> &ret, unordered_map<string, multiset<string>> &g, string src) {
		while (!g[src].empty()) {
			set<string>::iterator it = g[src].begin(); //lexical order: we only interested in first
			string dest = * it;
			g[src].erase(it);//visited, remove
			dfs(ret, g, dest);
		}
		ret.push_back(src);
	}
};
```

### Check Valid Path

### Walls and Gates

https://leetcode.com/problems/walls-and-gates/

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

```
Example: 

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
```

```CPP
class Solution {
    int row =0;
    int col = 0;
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        row=rooms.size();
        if(!row) return;
        col=rooms[0].size();
        if(!col) return;
        
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(rooms[i][j]==0){
                    //starting from gate and traversal whole matrix
                    DFS(rooms,i,j,0);
                }
            }
        }
  
    }
    
    void DFS(vector<vector<int>>& rooms, int i, int j, int path){
        if (i<0 || i >= row || j<0 || j >= col || path>rooms[i][j]) {
            return;
        }
        else {
            rooms[i][j] = path;
            DFS(rooms, i - 1, j, path + 1);
            DFS(rooms, i + 1, j, path + 1);
            DFS(rooms, i, j - 1, path + 1);
            DFS(rooms, i, j + 1, path + 1);
        }
        
    }
};
```

## BFS

```CPP
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}
```

### Shortest path

https://leetcode.com/problems/shortest-path-in-binary-matrix/

In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

```

Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
```

```CPP
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    if (grid[0][0]==1 || grid[row-1][col-1]==1)
        return -1;
    //possible to visit all 8 directions
    vector<vector<int>> directions = {{1,1}, {0,1},{1,0},{0,-1},{-1,0},{-1, -1},{1, -1},{-1, 1}};
    queue<pair<int,int>> q;
    //start count
    grid[0][0] =1;
    q.push(make_pair(0,0));
    
    while(!q.empty()){
        auto cur = q.front();
        int x = cur.first, y = cur.second;
        if( x == row -1 && y == col -1) 
            return grid[x][y];

        for(auto direction : directions){
            int nx = x + direction[0];
            int ny = y + direction[1];
            if(nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 0){
                q.push(make_pair(nx,ny));
                grid[nx][ny] = grid[x][y] + 1;
            }
        }
        q.pop();
    }
    
    return -1;
    
}
```

#### Path with Obstable

https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

 
```
Example 1:

Input: 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10. 
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
 

Example 2:

Input: 
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
Output: -1
Explanation: 
We need to eliminate at least two obstacles to find such a walk.
```

```CPP
int shortestPath(vector<vector<int>>& grid, int k) {
        //set to keep track of already visited paths
        int ret =0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dirs= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        // min obstacles elimination from (0,0) to (x, y)
        vector<vector<int>> obs(m, vector<int>(n,INT_MAX));

        //x,y, and how many obstable moved
        queue<vector<int>> q;
        q.push({0,0,0});
        obs[0][0]=0;
        
        while(!q.empty()){
            int size = q.size();
            //level by level
            while(size-->0){
                vector<int> cur = q.front();
                q.pop();
                //to end
                if(cur[0]==m-1 && cur[1]==n-1){
                    return ret;
                }
                for(auto dir: dirs){
                    int x = dir[0] + cur[0];
                    int y = dir[1] + cur[1];
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        continue;
                    }
                    //either +1 for obstable or same as previous
                    int o = grid[x][y] + cur[2];
                    //
                    if (o >= obs[x][y] || o > k) {
                        continue;
                    }
                    obs[x][y] = o;
                    q.push({x,y,o});
                }
            }
            //for all this level in queue, only +1 for step
            ++ret;
        }
        
        return -1;
    }
```

### Minimum Height Tree
```CPP
//https://leetcode.com/problems/minimum-height-trees/
/*
For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.
Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
Example 1:
Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
return [1]
Example 2:
Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
return [3, 4]
*/

class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vector<int> ret;
		//key is int and value is its direct linked node
		unordered_map<int, unordered_set<int>> g;
		for (int i = 0; i<edges.size(); i++) {
			g[edges[i].first].insert(edges[i].second);
			g[edges[i].second].insert(edges[i].first);
		}
		vector<int> cur;
		//corner case
		if (n == 1) {
			cur.push_back(0);
			return cur;
		}

		// Create first leaf layer
		for (int i = 0; i < g.size(); ++i) {
			if (g[i].size() == 1) {
				cur.push_back(i);
			}
		}
		// BFS the graph
		while (true) {
			vector<int> next;
			for (int node : cur) {
				for (int neighbor : g[node]) {
					g[neighbor].erase(node);
					if (g[neighbor].size() == 1)
						next.push_back(neighbor);
				}
			}
			if (next.empty())
				return cur;
			cur = next;
		}
	}
};


```

### Common Ancestor

Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique integer identifier.

For example, in this diagram, the earliest ancestor of 6 is 14, and the earliest ancestor of 15 is 2. 

```

         14
         |
  2      4
  |    / | \
  3   5  8  9
 / \ / \     \
15  6   7    11
```


```CPP
int findEarliestAncestor(vector<pair<int, int>> parentChildPairs, int a, int b){
  
  unordered_map<int, vector<int>> m; //k is child, v is parent
  unordered_map<int, int> parent;  //record all parents/distance from particular node 
  
    for(int i=0;i<parentChildPairs.size();i++){
    int child = parentChildPairs[i].second;
    int parent = parentChildPairs[i].first;
    m[child].push_back(parent);
  }
  
  queue<int> q; //1 parent, 2 is distance
  
  int step = 1;
  for(auto j: m[a]){
    q.push(j);
    parent[j] = step;
  }
  
    //BFS all node a's ancestor
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    step++;
    for(auto j: m[cur]){
      q.push(j);
      parent[j] = step;
    }
    
  }
  //BFS all node b's 
  int earilest = 0;
  int ret = -1;
  
  for(auto j: m[b]){
      if(parent.find(j)!=parent.end()){
        if(parent[j]>earilest){
          earilest = parent[j];
          ret = j;
        }
      }
      
      q.push(j);

  }
  
  
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    for(auto j: m[cur]){
      q.push(j);
      if(parent.find(j)!=parent.end()){
        if(parent[j]>earilest){
          earilest = parent[j];
          ret = j;
        }
      }
    }
    
  }
  
  return ret;
  
}


bool hasCommonAncestor(vector<pair<int, int>> parentChildPairs, int a, int b){
  unordered_map<int, vector<int>> m; //k is child, v is parents vector
  for(int i=0;i<parentChildPairs.size();i++){
    int child = parentChildPairs[i].second;
    int parent = parentChildPairs[i].first;
    m[child].push_back(parent);
  }
  
  unordered_set<int> s;  //record all parents from node a
  
  if(m[a].size()==0 || m[b].size()==0){
    return false;
  }
  
  queue<int> q;
  for(auto j: m[a]){
    q.push(j);
    s.insert(j);
  }
  
  //BFS all node a's ancestor
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    for(auto j: m[cur]){
      q.push(j);
      s.insert(j);
    }
    
  }
  
  //check b's 
    for(auto j: m[b]){
      if(s.find(j)!=s.end()){
        return true;
      }
      
      q.push(j);

    }
  
    //BFS all node b's ancestor
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    for(auto j: m[cur]){
      if(s.find(j)!=s.end()){
        return true;
      }
      
      q.push(j);
    }
    
  }
  
  return false;
  
}


vector<vector<int>> findNodesWithZeroAndOneParents(vector<pair<int, int>> parentChildPairs){
  unordered_map<int, vector<int>> m; //k is child, v is parents vector
  unordered_set<int> s;  //record all parents
  
  for(int i=0;i<parentChildPairs.size();i++){
    int child = parentChildPairs[i].second;
    int parent = parentChildPairs[i].first;
    m[child].push_back(parent);
    s.insert(parent);
  }
  
  vector<int> zeroParents;
  vector<int> oneParent;
  vector<vector<int>> ret;
  
  for(auto j: s){
    if(m.find(j)==m.end()){
      zeroParents.push_back(j);
    }
  }
  
  for(auto n: m){
   if(n.second.size()==1){
      oneParent.push_back(n.first);
    }
  }
  ret.push_back(zeroParents);
  ret.push_back(oneParent);
  
  return ret;
  
}
```

# Connected Component(Union Find, DFS, BFS)

## Basic idea

### Union find: 

Basic idea is to find root/parents of certain node, and union if same parents. have a log complexity way to find root for each node

### DFS/BFS:  

from one item(item in vector or point in 2-D matrix)
	* search all surrounding via DFS/BFS
	* mark visited(through either some visited mark, or change original value)

### Number of island(DFS)

https://leetcode.com/problems/number-of-islands/

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 
```
Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

```CPP
int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    eraseIslands(grid, i, j);
                }
            }
        }
        return islands;
    }
    
    void eraseIslands(vector<vector<char>>& grid, int i, int j){
         int m = grid.size(), n = grid[0].size();
        if (i < 0 || i == m || j < 0 || j == n || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        eraseIslands(grid, i - 1, j);
        eraseIslands(grid, i + 1, j);
        eraseIslands(grid, i, j - 1);
        eraseIslands(grid, i, j + 1);
    }
```

#### Count number of islands(Union Find)

https://leetcode.com/problems/number-of-islands-ii/

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

```
Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]
Explanation:

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
```

```CPP
vector<int> roots;

vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    vector<int> res;
    roots = vector<int>(m * n, -1);
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int island = 0;
    for (auto pos : positions) {
        int x = pos.first, y = pos.second;
        int idx_p = x * n + y;
        roots[idx_p] = idx_p;
        ++island;
        for (auto dir : dirs) {
            int row = x + dir.first, col = y + dir.second;
            int idx_new = row * n + col;
            //find there is cluster has been set
            if (row >= 0 && row < m && col >= 0 && col < n && roots[idx_new] != -1) {
                int rootNew = findRoot(idx_new);
                int rootPos = findRoot(idx_p);
                //link two components/islands
                if (rootPos != rootNew) {
                    roots[rootPos] = rootNew;
                    --island;
                }
            }
        }
        res.push_back(island);
    }
    return res;
}


int findRoot(int idx) {
    while(idx != roots[idx]) {
        roots[idx] = roots[roots[idx]]; 
        idx = roots[idx];
    }
    return idx;
}
```

### Number of connected component(Union Find)

https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

```CPP

/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.
Example 1:

0          3
|          |
1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
0           4
|           |
1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
*/

class Solution {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {

		//find root for each node, if same root, link together by union find

		vector<int> root(n, 0);
		for (int i = 0; i<n; i++) {
			root[i] = i;
		}

		for (int i = 0; i<edges.size(); i++) {
			int v1 = edges[i].first;
			int v2 = edges[i].second;
			int root1 = find(root, v1);
			int root2 = find(root, v2);
			if (root1 != root2) {//union two parts into one
				root[root1] = root2;
			}

		}

		int cnt = 0;
		for (int i = 0; i<root.size(); i++) {
			if (root[i] == i)
				cnt++;
		}

		return cnt;
	}

	int find(vector<int> root, int v) {
		while (root[v] != v) {//until find root is itself, not more parent node/root.
			root[v] = root[root[v]]; //path compression, directly find the final root
			v = root[v];
		}
		return v;
	}
};

```

> DFS soltution

```CPP
int countComponents(int n, vector<vector<int>>& edges) {

    int ret =0;
    vector<vector<int>> g(n);
    //convert the edge into graph 
    for(int i=0;i<edges.size();i++){
        g[edges[i][0]].push_back(edges[i][1]);
        g[edges[i][1]].push_back(edges[i][0]);
    }
    
    vector<int> visited(n,0);
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i] =1;
            dfs(g,visited, i);
            ret++;
        }
    }
    
    return ret;
}

void dfs(vector<vector<int>>& g, vector<int>& visited, int cur){
    for(auto j: g[cur]){
        if(visited[j]==0){
            visited[j] =1;
            dfs(g,visited, j);
        }
    }
}
```

> BFS

```CPP
int countComponents(int n, vector<vector<int>>& edges) {
    
        int ret =0;
        vector<vector<int>> g(n);
        //convert the edge into graph 
        for(int i=0;i<edges.size();i++){
            g[edges[i][0]].push_back(edges[i][1]);
            g[edges[i][1]].push_back(edges[i][0]);
        }
        
        vector<int> visited(n,0);
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            visited[i] = 1;
            q.push(i);

            while (!q.empty()) {
                int cur = q.front(); 
                q.pop();
                for (auto node : g[cur]) {
                    if (visited[node] ==0) {
                        visited[node] = 1;
                        q.push(node);
                    }
                }
            }
            ret++;
        }
        
        return ret;
    }

```

### Number of component with some step count

#### Rotting Oranges

https://leetcode.com/problems/rotting-oranges/

In a given grid, each cell can have one of three values:

the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.

 
```
Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
```

```CPP
int orangesRotting(vector<vector<int>>& grid) {
    int fresh=0, res=-1;
    queue<pair<int,int>> q;
    vector<vector<int>> dir={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i=0;i<grid.size();i++) {
        for(int j=0;j<grid[0].size();j++) {
            if(grid[i][j]==1) 
                fresh++;
            if(grid[i][j]==2) 
                q.push({i, j});
        }
    }
    while(!q.empty()) {
        res++;
        int size = q.size();
        //each layer we have some count/res
        for(int k=0;k<size;k++) {
            pair<int,int> cur=q.front();
            
            q.pop();
            for(int i=0;i<4;i++) {
                int x=cur.first+dir[i][0], y=cur.second+dir[i][1];
                if(x>=grid.size()||x<0||y>=grid[0].size()||y<0||grid[x][y]!=1) 
                    continue;
                grid[x][y]=2;
                q.push({x, y});
                fresh--;
            }
        }
    }
    if(fresh==0) 
        return max(0, res);
    return -1;
    
}
```




### Friends Circle(DFS/BFS)

https://leetcode.com/problems/friend-circles/

There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.
```
Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.
Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
```


```CPP
//DFS
int findCircleNum(vector<vector<int>>& M) {
    //visited[i] means i-th node is visited and undergoing DFS
    vector<int> visited(len,0);
    int ret=0;
    
    for(int i=0;i<len;i++){
        //if visited[i] == 1. means it has been visited by last DFS
        if(visited[i]==0){
            dfs(M,visited,i,len);
            ret++;
        }
    }
    
    return ret;
}

void dfs(vector<vector<int>>& M, vector<int> &visited, int i, int len){
    //dfs for a particular node index i only
    for(int j=0;j<len;j++){
        if(M[i][j]==1 && visited[j]==0){
            visited[j]=1;
            dfs(M,visited,j,len);
        }
    }
}
```


```CPP
//BFS
int findCircleNum(vector<vector<int>>& M) {
        //visited[i] means i-th node is visited and undergoing DFS
        int len = M.size();
        vector<int> visited(len,0);
        int ret=0;
        queue<int> q;
        for(int i=0;i<len;i++){
            if(visited[i]==0){
                q.push(i);
                while(!q.empty()){
                    int cur = q.front();
                    visited[cur] = 1;
                    q.pop();
                    //only push those not visited, start from current index
                    for(int j=0;j<len;j++){
                        if(M[cur][j]==1 && visited[j] == 0){
                            q.push(j);
                        }
                    }
                }
                ret++;
            }
        }
        
        
        return ret;
    }

```



### Graph Valid Tree

```CPP
//https://leetcode.com/problems/graph-valid-tree/
/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
*/
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		/*
		Make sure there is no cycle in the graph - this has to be a none-cyclic graph;
		Make sure every node is reached - this has to be a connected graph;

		To test cyclic, we can make an array for each node (as array index), and the array will store the parent of the node (as array index). Every time we fetch a new pair of nodes, we trace the root node (the deepest parent node) of these two nodes, if it has the same root, then is will be a cycle; otherwise, we set the parent of second node to be the first node;
		After we make sure there is node cycle in the graph, we simple test if there is enough edges to make this graph connected.
		*/
		vector<int> root(n, 0);
		for (int i = 0; i<n; i++) {
			root[i] = i;
		}
		int len = edges.size();
		for (int i = 0; i<len; i++) {
			int v1 = edges[i].first;
			int v2 = edges[i].second;
			while (root[v1] != v1) {
				root[v1] = root[root[v1]]; //search for deepest root.
				v1 = root[v1];
			}
			while (root[v2] != v2) {
				root[v2] = root[root[v2]]; //search for deepest root.
				v2 = root[v2];
			}
			if (root[v1] == root[v2])
				return false;
			root[v1] = v2;
		}

		return len == n - 1;
	}
};

```

### Account Merge (Union find)

https://leetcode.com/problems/accounts-merge/

Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

```
Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
```

```CPP
int find(vector<int> &account_union, int ind) {
        while(account_union[ind] != ind)
            ind = account_union[ind];
        return ind;
    }
    
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    /*
    idea is to use union find
    each email, we need to union them to some parent, which is account
    like link graph component
    */
    
    unordered_map<string, int> m; //email : parent_id(account id)
    vector<int> account_union(accounts.size(), 0);
    unordered_map<int, vector<string>> res_map;
    for (int i = 0; i < accounts.size(); i++) {
        //assign identical id for each account
        account_union[i] = i;
        for (int j = 1; j < accounts[i].size(); j++) {
            //find same email exists in another account vector(component)
            if (m.find(accounts[i][j]) != m.end()) {
                int root1 = find(account_union, i);
                int root2 = find(account_union, m[accounts[i][j]]);
                account_union[root1] = root2;
            }
            else
                m[accounts[i][j]] = account_union[i];
        }
    }
    for (auto it : m) {
        //for same account id, push all email
        int ind = find(account_union, it.second);
        res_map[ind].push_back(it.first);
    }
    vector<vector<string>> res;
    for (auto it : res_map) {
        vector<string> email = it.second;
        sort(email.begin(), email.end());
        email.insert(email.begin(), accounts[it.first][0]); //get from index the account name
        res.push_back(email);
    }
    return res;
}
```

### Making A Large Island

https://leetcode.com/problems/making-a-large-island/

In a 2D grid of 0s and 1s, we change at most one 0 to a 1.

After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).

```
Example 1:

Input: [[1, 0], [0, 1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: [[1, 1], [1, 0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: [[1, 1], [1, 1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
```

```CPP

/*
Explore every island using DFS, count its area, give it an island index and save the result to a {index: area} map.
Loop every cell == 0, check its connected islands and calculate total islands area.
*/

int N;
int largestIsland(vector<vector<int>>& grid) {
    N = grid.size();
    //DFS every island and give it an color of island (>1)
    int color = 2, res = 0;
    unordered_map <int, int>area;  //area color index is K, num of 1 is value
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            if (grid[x][y] == 1) {
                area[color] = dfs(grid, x, y, color);
                res = max(res, area[color++]);
            }
        }
    }
    //traverse every 0 cell and count biggest island it can conntect
    for (int x = 0; x < N; ++x)
        for (int y = 0; y < N; ++y)
            if (grid[x][y] == 0) {
                unordered_set<int> seen = {};
                int cur = 1;
                //only search grid close to color
                for (auto p : move(x, y)) {
                    color = grid[p.first][p.second];
                    //for already connected components marked by color, and not visited
                    if (color > 1 && seen.count(color) == 0) {
                        seen.insert(color);
                        cur += area[color];
                    }
                }
                res = max(res, cur);
            }
    return res;
}

int dfs(vector<vector<int>>& grid, int x, int y, int color) {
    int area = 0;
    grid[x][y] = color;
    for(auto p : move(x, y))
        if (grid[p.first][p.second] == 1)
            area += dfs(grid, p.first, p.second, color);
    return area + 1;
}

vector<pair<int, int>> move(int x, int y) {
    vector<pair<int, int>> res;
    for (auto p : vector<vector<int>> {{1, 0}, { -1, 0}, {0, 1}, {0, -1}}) {
        if (valid(x + p[0], y + p[1]))
            res.push_back(make_pair(x + p[0], y + p[1]));
    }
    return res;
}

int valid(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}
```


# Topological Sort

In the field of computer science, a topological sort (sometimes abbreviated toposort[1]) or topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG). Any DAG has at least one topological ordering, and algorithms are known for constructing a topological ordering of any DAG in linear time.
Given an directed graph, a topological order of the graph nodes is defined as follow:
* For each directed edge A -> B in graph, A must before B in the order list.
* The first node in the order can be any node in the graph with no nodes direct to it.
Find any topological order for the given graph.

## Top Sort

#### DFS
https://www.youtube.com/watch?v=ddTC4Zovtbc

https://www.cs.usfca.edu/~galles/visualization/TopoSortDFS.html

The idea is to explore nodes and its neighbors recursively, using a set to check whether node has been visited

```CPP
/**
* Definition for Directed graph.
* struct DirectedGraphNode {
*     int label;
*     vector<DirectedGraphNode *> neighbors;
*     DirectedGraphNode(int x) : label(x) {};
* };
*/
class Solution {
public:
    /**
    * @param graph: A list of Directed graph node
    * @return: Any topological order for the given graph.
    */
    vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
        // write your code here
        set<DirectedGraphNode*> visit;
        vector<DirectedGraphNode*> ret;
        for (int i = 0; i<graph.size(); i++) {
            if (visit.find(graph[i]) == visit.end()) {
                Toposort_DFS(visit, graph[i], ret, graph);
            }
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    void Toposort_DFS(set<DirectedGraphNode*> &visit, DirectedGraphNode* node, vector<DirectedGraphNode*> &ret, vector<DirectedGraphNode*> graph) {
        visit.insert(node);
        for (int i = 0; i<node->neighbors.size(); i++) {
            if (visit.find(node->neighbors[i]) == visit.end()) {
                Toposort_DFS(visit, node->neighbors[i], ret, graph);
            }
        }
        //go to end, no direct child node, sink
        ret.push_back(node);
    }
};

```



#### BFS

https://www.educative.io/courses/grokking-the-coding-interview/m25rBmwLV00

```CPP
static vector<int> sort(int vertices, const vector<vector<int>>& edges) {
    vector<int> sortedOrder;


    // a. Initialize the graph
    unordered_map<int, int> inDegree;       // count of incoming edges for every vertex
    unordered_map<int, vector<int>> graph;  // adjacency list graph
    for (int i = 0; i < vertices; i++) {
      inDegree[i] = 0;
      graph[i] = vector<int>();
    }

    // b. Build the graph
    for (int i = 0; i < edges.size(); i++) {
      int parent = edges[i][0];
      int child = edges[i][1];
      graph[parent].push_back(child);  // put the child into it's parent's list
      inDegree[child]++;               // increment child's inDegree
    }

    // c. Find all sources i.e., all vertices with 0 in-degrees
    queue<int> sources;
    for (auto entry : inDegree) {
      if (entry.second == 0) {
        sources.push(entry.first);
      }
    }

    // d. For each source, add it to the sortedOrder and subtract one from all of its children's
    // in-degrees if a child's in-degree becomes zero, add it to the sources queue
    while (!sources.empty()) {
      int vertex = sources.front();
      sources.pop();
      sortedOrder.push_back(vertex);
      vector<int> children =
          graph[vertex];  // get the node's children to decrement their in-degrees
      for (auto child : children) {
        inDegree[child]--;
        if (inDegree[child] == 0) {
          sources.push(child);
        }
      }
    }

    if (sortedOrder.size() !=
        vertices) {  // topological sort is not possible as the graph has a cycle
      return vector<int>();
    }

    return sortedOrder;
  }
```



#### Detect Circle via Topo Sort

```
L = Empty list that will contain the sorted elements
S = Set of all nodes with no incoming edge

while S is non-empty do
    remove a node n from S
    add n to tail of L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S

if graph has edges then
    return error   (graph has at least one cycle)
else 
    return L   (a topologically sorted order)
```

To better understand the above algorithm, we summarize a few points here:

* In order to find a global order, we can start from those nodes  indegree of node is zero, we then incrementally add new nodes to the global order, following the dependencies (edges).
* Once we follow an edge, we then remove it from the graph.
* With the removal of edges, there would more nodes appearing with indegree 0, in addition to the initial list in the first step.
* The algorithm would terminate when we can no longer remove edges from the graph. There are two possible outcomes:

1. If there are still some edges left in the graph, then these edges must have formed certain cycles, which is similar to the deadlock situation. It is due to these cyclic dependencies that we cannot remove them during the above processes.

2. Otherwise, i.e. we have removed all the edges from the graph, and we got ourselves a topological order of the graph.


### Task/Course schedule

#### Can finish all course

https://leetcode.com/problems/course-schedule/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

 
```
Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
```

```CPP
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses,0);
        //build graph
        for(auto edge : prerequisites)
        {
            graph[edge[1]].push_back(edge[0]); //from node -> dest graph
            ++indegree[edge[0]]; 
        }
        queue<int> Q;
        for(int i = 0;i < numCourses;i++)
            if(indegree[i] == 0)
                Q.push(i);
        int counter = 0;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            ++counter;
            for(auto v : graph[u])
            {
                if(--indegree[v] == 0)
                    Q.push(v);
            }
        }
        return counter == numCourses;
    }
```

#### Find courses order

https://leetcode.com/problems/course-schedule-ii/

There are a total of n courses you have to take labelled from 0 to n - 1.

Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi] this means you must take the course bi before the course ai.

Given the total number of courses numCourses and a list of the prerequisite pairs, return the ordering of courses you should take to finish all courses.

If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.



```CPP
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> ret;

        // a. Initialize the graph
        vector<int> inDegree(numCourses, 0);       // count of incoming edges for every vertex
        unordered_map<int, vector<int>> graph;  // adjacency list graph
        for (int i = 0; i < numCourses; i++) {
          graph[i] = vector<int>();
        }

        // b. Build the graph
        for (int i = 0; i < prerequisites.size(); i++) {
          int parent = prerequisites[i][1], child = prerequisites[i][0];
          graph[parent].push_back(child);  // put the child into it's parent's list
          inDegree[child]++;               // increment child's inDegree
        }

        // c. Find all sources i.e., all vertices with 0 in-degrees
        queue<int> q;
        for(int i = 0;i < numCourses;i++)
            if(inDegree[i] == 0)
                q.push(i);

        // d. For each source, add it to the ret and subtract one from all of its children's
        // in-degrees if a child's in-degree becomes zero, add it to the sources queue
        while (!q.empty()) {
          int vertex = q.front();
          q.pop();
        //no prerequest courses, we can take it and add to return vector
          ret.push_back(vertex); 

          for (auto child : graph[vertex]) {
            if (--inDegree[child] == 0) {
              q.push(child);
            }
          }
        }
        
        return ret.size()==numCourses?ret: vector<int>{};
    }
```

#### Find out all finish path

https://www.educative.io/courses/grokking-the-coding-interview/q2YmVjQMMr3

There are ‘N’ tasks, labeled from ‘0’ to ‘N-1’. Each task can have some prerequisite tasks which need to be completed before it can be scheduled. Given the number of tasks and a list of prerequisite pairs, write a method to print all possible ordering of tasks meeting all prerequisites.

```
Example 1:

Input: Tasks=3, Prerequisites=[0, 1], [1, 2]
Output: [0, 1, 2]
Explanation: There is only possible ordering of the tasks.
Example 2:

Input: Tasks=4, Prerequisites=[3, 2], [3, 0], [2, 0], [2, 1]
Output: 
1) [3, 2, 0, 1]
2) [3, 2, 1, 0]
Explanation: There are two possible orderings of the tasks meeting all prerequisites.
```

```CPP
static void printOrders(int tasks, vector<vector<int>> &prerequisites) {
    vector<int> sortedOrder;
    if (tasks <= 0) {
      return;
    }

    // a. Initialize the graph
    unordered_map<int, int> inDegree;       // count of incoming edges for every vertex
    unordered_map<int, vector<int>> graph;  // adjacency list graph
    for (int i = 0; i < tasks; i++) {
      inDegree[i] = 0;
      graph[i] = vector<int>();
    }

    // b. Build the graph
    for (int i = 0; i < prerequisites.size(); i++) {
      int parent = prerequisites[i][0], child = prerequisites[i][1];
      graph[parent].push_back(child);  // put the child into it's parent's list
      inDegree[child]++;               // increment child's inDegree
    }

    // c. Find all sources i.e., all vertices with 0 in-degrees
    vector<int> sources;
    for (auto entry : inDegree) {
      if (entry.second == 0) {
        sources.push_back(entry.first);
      }
    }

    printAllTopologicalSorts(graph, inDegree, sources, sortedOrder);
  }

static void printAllTopologicalSorts(unordered_map<int, vector<int>> &graph,
                                   unordered_map<int, int> &inDegree,
                                   const vector<int> &sources, vector<int> &sortedOrder) {
    if (!sources.empty()) {
      for (int vertex : sources) {
        sortedOrder.push_back(vertex);
        vector<int> sourcesForNextCall = sources;
        // only remove the current source, all other sources should remain in the queue for the next
        // call
        sourcesForNextCall.erase(
            find(sourcesForNextCall.begin(), sourcesForNextCall.end(), vertex));

        vector<int> children =
            graph[vertex];  // get the node's children to decrement their in-degrees
        for (auto child : children) {
          inDegree[child]--;
          if (inDegree[child] == 0) {
            sourcesForNextCall.push_back(child);  // save the new source for the next call
          }
        }

        // recursive call to print other orderings from the remaining (and new) sources
        printAllTopologicalSorts(graph, inDegree, sourcesForNextCall, sortedOrder);

        // backtrack, remove the vertex from the sorted order and put all of its
        // children back to consider the next source instead of the current vertex
        sortedOrder.erase(find(sortedOrder.begin(), sortedOrder.end(), vertex));
        for (auto child : children) {
          inDegree[child]++;
        }
      }
    }

    // if sortedOrder doesn't contain all tasks, either we've a cyclic dependency between tasks, or
    // we have not processed all the tasks in this recursive call
    if (sortedOrder.size() == inDegree.size()) {
      for (int num : sortedOrder) {
        cout << num << " ";
      }
      cout << endl;
    }
}
```

#### Parallel Courses(Max Depth in DAG)

https://leetcode.com/problems/parallel-courses/

There are N courses, labelled from 1 to N.

We are given relations[i] = [X, Y], representing a prerequisite relationship between course X and course Y: course X has to be studied before course Y.

In one semester you can study any number of courses as long as you have studied all the prerequisites for the course you are studying.

Return the minimum number of semesters needed to study all courses.  If there is no way to study all the courses, return -1.

 
```
Example 1:

Input: N = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: 
In the first semester, courses 1 and 2 are studied. In the second semester, course 3 is studied.
Example 2:



Input: N = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: 
No course can be studied because they depend on each other.
```

```CPP
int minimumSemesters(int N, vector<vector<int>>& relations) {
        //basically MAX distance in DAG
        unordered_map<int, vector<int>> g; // key: prerequisite, value: course list. 
        int len = relations.size();
        vector<int> indegree(N+1,0); // inDegree[i]: number of prerequisites for i.
        for (auto r : relations) {
            g[r[0]].push_back(r[1]); // construct graph.
            ++indegree[r[1]]; // count prerequisites for r[1].
        }
        queue<int> q; // save current 0 in-degree vertices.
        for (int i = 1; i <= N; ++i)
            if (indegree[i] == 0)
                q.push(i);
        int semester = 0;
        while(!q.empty()) {
            int n=q.size();
            semester++;
            for(int i=0;i<n;i++) {
                int cur=q.front();
                q.pop();
                for(int v:g[cur]) {
                    //prerequisite studied, all course with prerequisite can be studied in next round
                    
                    if(--indegree[v]==0) {
                        q.push(v);
                    }
                }
            }
        }

        //cycle present, not possible
        for(int in:indegree) 
            if(in>0)  
                return -1;

        return semester;

    }
```

### Alien dictionary

https://leetcode.com/problems/alien-dictionary/

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

```
Example 1:

Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

Output: "wertf"
Example 2:

Input:
[
  "z",
  "x"
]

Output: "zx"
Example 3:

Input:
[
  "z",
  "x",
  "z"
] 

Output: "" 

Explanation: The order is invalid, so return "".
```

```CPP
string alienOrder(vector<string>& words) {
        if (words.size() == 0) 
            return "";
        unordered_map<char, int> indegree;
        unordered_map<char, unordered_set<char>> graph;
        
        // initialize graph
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                char c = words[i][j];
                indegree[c] = 0; 
            }
        }
        
        // build graph and record indegree
        for (int i = 0; i < words.size() - 1; i++) {
            string cur = words[i];
            string next = words[i + 1];
            int len = min(cur.size(), next.size());
            for (int j = 0; j < len; j++) {
                //we get different char on same pos of two adjacent words
                if (cur[j] != next[j]) {
                    unordered_set<char> set = graph[cur[j]];
                    if (set.find(next[j]) == set.end()) {
                        graph[cur[j]].insert(next[j]); // build graph
                        indegree[next[j]]++; // add indegree
                    }
                    break;                        
                }
                //not able to alphabetic order
                if (j == len - 1 && cur.size() > next.size()) 
                    return "";
            }
        }
        
        // topoligical sort
        string ans;
        queue<char> q;
        for (auto& e : indegree) {
            if (e.second == 0) {
                q.push(e.first);
            }
        }
        while(!q.empty()) {
            char cur = q.front();
            q.pop();
            ans += cur;
            
            if (graph[cur].size() != 0) {
                for (auto& e : graph[cur]) {
                    indegree[e]--;
                    if (indegree[e] == 0) {
                        q.push(e);
                    }
                }
            }            
        }
        
        // tell if it is cyclic
        return ans.length() == indegree.size() ? ans : "";
    }
```

### Minimum Height Trees

https://leetcode.com/problems/minimum-height-trees/

https://www.educative.io/courses/grokking-the-coding-interview/7nDN8y7JKVA

A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

```CPP
/*
leaves can’t give us MHT, we can remove them from the graph and remove their edges too. Once we remove the leaves, we will have new leaves. Since these new leaves can’t give us MHT, we will repeat the process and remove them from the graph too. We will prune the leaves until we are left with one or two nodes which will be our answer and the roots for MHTs.
*/

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    vector<int> ret;
    //key is int and value is its direct linked node
    unordered_map<int,unordered_set<int>> g;
    for(int i=0;i<edges.size();i++){
        g[edges[i][0]].insert(edges[i][1]);
        g[edges[i][1]].insert(edges[i][0]);
    }
    vector<int> cur;
    //corner case
     if (n == 1) {
      cur.push_back(0);
      return cur;
    }
    
    // Create first leaf layer
    for (int i = 0; i < g.size(); ++i) {
      if (g[i].size() == 1) {
        cur.push_back(i);
      }
    }
   // BFS the graph
    while (true) {
      vector<int> next;
    //from all leave layer
      for (int node : cur) {
        for (int neighbor : g[node]) {
          g[neighbor].erase(node); //remove layers
          if (g[neighbor].size() == 1) //found until leave
            next.push_back(neighbor);
        }
      }
      if (next.empty()) 
        return cur;
      cur = next;
    }
}
```


## Example

### Sequence Reconstruction

https://leetcode.com/problems/sequence-reconstruction/

Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

 
```
Example 1:

Input: org = [1,2,3], seqs = [[1,2],[1,3]]
Output: false
Explanation: [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input: org = [1,2,3], seqs = [[1,2]]
Output: false
Explanation: The reconstructed sequence can only be [1,2].
Example 3:

Input: org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
Output: true
Explanation: The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input: org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
Output: true
```


```CPP
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.size() == 0) return false;
        int n = org.size(), count = 0;
        unordered_map<int, unordered_set<int>> graph;   // record parents
        vector<int> degree(n+1, 0); // record out degree
        for (auto s : seqs) {   // build graph
            for (int i = s.size()-1; i >= 0; --i) {
                if (s[i] > n or s[i] < 0) 
                    return false; // in case number in seqs is out of range 1-n
                if (i > 0 and graph[s[i]].find(s[i-1])==graph[s[i]].end()) {
                    graph[s[i]].insert(s[i-1]);
                    if (degree[s[i-1]]++ == 0) count ++;
                }
            }
        }
        if (count != n-1) 
            return false; // all nodes should have degree larger than 0 except the last one
        for (int i = n-1; i >= 0; --i) {    // topological sort
            if (degree[org[i]] > 0) return false;   // the last node should have 0 degree
            for (auto p : graph[org[i]]) 
                if (--degree[p] == 0 and p != org[i-1]) // found a node that is not supposed to have 0 degree
                    return false;
        }
        return true;        
    }
```





