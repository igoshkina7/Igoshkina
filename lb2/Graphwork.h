#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include "CKS.h"
#include "CTruba.h"



struct id_in_pipe
{
	int id;
	int id_in;
};
id_in_pipe createStruct(int& id, int& id_in)
{
	id_in_pipe new_pair;
	new_pair.id = id;
	new_pair.id_in = id_in;
	return new_pair;
}

bool dfspr(int v, unordered_map<int, vector<id_in_pipe>>& gr, unordered_map<int, bool> used, unordered_map<int, int> p, int& cycle_st, vector<int>& ans) 
{
	 used[v] = true;
	vector<id_in_pipe> maxv;
	maxv = gr[v];

	for (auto& i : maxv) 
	{
		int to = i.id_in;
		if (!used[to])
		{
			p[to] = v;
			if (dfspr(to, gr, used, p, cycle_st, ans))
				return true;
		}
		else if (used[to] == true)
		{
			cycle_st = to;
			return true;
		}

	}
	ans.push_back(v);
	used[v] = 2;
	int k = 0;
	int n = ans.size();
	for (int j = 0; j < n; j++)
		if (ans[j] == v)
			k = k + 1;
	if (k == 0) ans.push_back(v);
	return false;

}

void topol_sort(unordered_map<int, vector<id_in_pipe>>& gr, vector<int>& ans) 
{
	ans.clear();
	unordered_map<int, bool> used;
	unordered_map<int, int> p;
	for (auto& i : gr)
	{
		used[i.first] = false;
		p[i.first] = -1;
	}
	int cycle_st = -1;
	for (auto& el : used)
	{
		if (dfspr(el.first, gr, used, p, cycle_st, ans))
			break;
	}

	if (cycle_st == -1)
		reverse(ans.begin(), ans.end());
	else cout << "Cycle";
}


unordered_map<int, vector<id_in_pipe>> Graph(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, CKS>& mapKS, unordered_map <int, Truba>& mapTruba, unordered_set<int>id_ks)
{
	graph.clear();
	if (mapTruba.size() != 0)
		for (auto it = mapTruba.begin(); it != mapTruba.end(); ++it)
		{
			if (it->second.get_id_in() != 0 && it->second.get_remont() == false)
			{
				int id = it->second.get_id();
				int id_in = it->second.get_id_in();
				int id_out = it->second.get_id_out();
				graph[id_out].push_back(createStruct(id, id_in));
				id_ks.insert(id_in);
				id_ks.insert(id_out);
			}
		}
	return graph;
}


template <typename T>
void PrintGraph(T graph)
{
	for (auto& i : graph)
	{
		cout << "KS ID " << i.first << " connected by Truba ID ";
		for (auto j = i.second.begin(); j != i.second.end(); j++)
		{
			cout << j->id << " wiht KS ID " << j->id_in;
			if (j + 1 != i.second.end()) cout << ", ";
		}
		cout << endl;
	}
}




void addEdge(int u, int v, int cap, int onEnd[100], int& edgeCount, int nextEdge[100], int firstEdge[100], int capacity[100])
{
	
	onEnd[edgeCount] = v;                   
	nextEdge[edgeCount] = firstEdge[u];     
	firstEdge[u] = edgeCount;               
	capacity[edgeCount++] = cap;            

	
	onEnd[edgeCount] = u;                   
	nextEdge[edgeCount] = firstEdge[v];     
	firstEdge[v] = edgeCount;               
	capacity[edgeCount++] = 0;				
}

int findFlow(int u, int flow, int destinationVertex, int* visited, int* firstEdge, int* nextEdge, int* onEnd, int* capacity) {
	if (u == destinationVertex) return flow; 
	visited[u] = true;
	for (int edge = firstEdge[u]; edge != 0; edge = nextEdge[edge]) {
		int to = onEnd[edge];
		if (!visited[to] && capacity[edge] > 0) {
			int minResult = findFlow(to, min(flow, capacity[edge]), destinationVertex, visited, firstEdge, nextEdge, onEnd, capacity); 
			if (minResult > 0) {                    
				capacity[edge] -= minResult;   
				//capacity[edge ^ 1] += minResult;   
				return minResult;
			}
		}
	}
	return 0; 
}

void Potok(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, CKS>& kss, unordered_map <int, Truba>& pipe, unordered_set<int>idks)
{
	size_t n = pipe.size();
	int* capacity = new int[n];
	int* onEnd = new int[n];
	int* nextEdge = new int[n];
	int* firstEdge = new int[n];
	int* visited = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		capacity[i] = 0;
		onEnd[i] = 0;
		nextEdge[i] = 0;
		firstEdge[i] = 0;
		visited[i] = 0;
	}
	int edgeCount = 1;

	int numOfVertex = idks.size();
	//int numOfEdge = 0;
	int sourceVertex, destinationVertex;
	cout << "Istok: ";
	cin >> sourceVertex;
	cout << "Stok: ";
	cin >> destinationVertex;   
	if (destinationVertex == sourceVertex)
		cout << "This KS as start and finish" << endl;
	else if ((kss.find(sourceVertex) == kss.end()) || (kss.find(destinationVertex) == kss.end()))
		cout << "Have not this KSs or one of this KSs";
	else
	{
		for (auto it = pipe.begin(); it != pipe.end(); ++it) {
			int u, v, cap;
			if (it->second.get_id_in() != 0 && it->second.get_remont() == false)
			{
				u = it->second.get_id_out();
				v = it->second.get_id_in();
				cap = it->second.get_propusk();
				addEdge(u, v, cap, onEnd, edgeCount, nextEdge, firstEdge, capacity);
			}
		}
		
		int maxFlow = 0;
		int iterationResult = 0;
		while ((iterationResult = findFlow(sourceVertex, 1000000, destinationVertex, visited, firstEdge, nextEdge, onEnd, capacity)) > 0)
			maxFlow += iterationResult;
		
		cout << maxFlow << endl;
	}
}






struct item 
{ 
	int s, c; 
	int v; 
};
item CreateItem(int s, int c, int v)
{
	item newitem;
	newitem.s = s;
	newitem.c = c;
	newitem.v = v;
	return newitem;
}



int find(int s, int c, vector<item>map) 
{ 
	for (int i = 0; i < map.size(); i++)
		if (map[i].s == s && map[i].c == c) return map[i].v;
	return 0;
}


void step(int s, int f, int p, vector<item>map, bool& found, int& len, int c_len, int waylen, vector<int>& way, vector<int>road, int n, vector<bool>incl) 
{ 
	if (s == f)  
	{
		way.clear();
		found = true; 
		len = c_len;
		waylen = p; 
		for (int i = 0; i < waylen; i++)
			way.push_back(road[i]); 
	}
	else { 
		for (int i = 0; i < map.size(); i++) { 
			int w = find(s, map[i].c, map); 
			if (w > 0 && !incl[p] && (len == 0 || c_len + w < len)) { 
				road[p] = map[i].c; 
				incl[p] = true; 
				c_len += w; 
				step(map[i].c, f, p + 1, map, found, len, c_len, waylen, way, road, n, incl); 
				road[p] = 0; 
				incl[p] = false;
				c_len -= w;
			}
		}
	}
}



void Puti(unordered_map<int, vector<id_in_pipe>>& graph, unordered_map <int, CKS>& kss, unordered_map <int, Truba>& pipe, unordered_set<int>idks)
{
	vector<item>map;
	int n = idks.size(); 
	vector<int>road;
	vector<bool>incl; 
	vector<int> way; 
	int waylen; 
	int start, finish; 
	bool found;
	int len; 
	int c_len; 
	for (auto it = pipe.begin(); it != pipe.end(); ++it) {
		int s, c, v;
		if (it->second.get_id_in() != 0)
		{
			s = it->second.get_id_out();
			c = it->second.get_id_in();
			v = it->second.get_length();
			map.push_back(CreateItem(s, c, v));
		}
	}
	for (int i = 0; i < n; i++) {
		incl.push_back(false);
		road.push_back(0);
	}
	len = c_len = waylen = 0;
	cout << "Start: ";
	cin >> start;
	cout << "Finish: ";
	cin >> finish;
	if (start == finish)
		cout << "This KS as start and finish" << endl;
	else if ((kss.find(start) == kss.end()) || (kss.find(finish) == kss.end()))
		cout << "Have not this KSs or one of this KSs";
	else if (idks.count(start) == 0 || idks.count(finish) == 0)
		cout << "Have not a way" << endl;
	else
	{
		road[0] = start; 
		incl[0] = true; 
		found = false; 

		step(start, finish, 1, map, found, len, c_len, waylen, way, road, n, incl); 

		if (found == true)
		{
			cout << "Way is";
			for (int i = 0; i < way.size(); i++) cout << "   >    " << way[i];
			cout << "     weight is " << len;
		}
		else cout << "Way not found!";
		cout << endl;
	}
}
