#pragma once
#include "myfunc.h"

using namespace std;


//vvv STL 사용 작성부분

//const int INTINF = 1 << 30;
//using PATHDIST = pair<int, int>;     //dist, ed V
//
//int vDist[20000];                    //shortest dist    V -> V-1
//list<PATHDIST> adjList[20000];
//priority_queue<PATHDIST, vector<PATHDIST>, greater<PATHDIST>> Q;
//
//void Q1()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(0);
//
//    bool visited[20000] = { 0 };
//    PATHDIST top;
//
//    int V, E, ST;
//    int s, e, w, cur;
//
//    cin >> V >> E >> ST;
//    ST--;
//
//    for (int i = 0; i < V; i++)
//    {
//        vDist[i] = INTINF;
//        if (i != ST) { Q.emplace(vDist[i], i); }
//    }
//
//    vDist[ST] = 0;
//    Q.emplace(0, ST);
//
//    for (int i = 0; i < E; i++)
//    {
//        cin >> s >> e >> w;
//        adjList[s - 1].emplace_back(w, e - 1);
//    }
//
//    for (int i = 0; i < V; i++)
//    {
//        do
//        {
//            top = Q.top();
//            Q.pop();
//        } while (visited[top.second]);
//
//        cur = top.second;
//        visited[top.second] = true;
//        for (auto& it : adjList[cur])
//        {
//            if (vDist[it.second] > vDist[cur] + it.first)
//            {
//                vDist[it.second] = vDist[cur] + it.first;
//                Q.emplace(vDist[it.second], it.second);
//            }
//        }
//    }
//
//    for (int i = 0; i < V; i++)
//    {
//        if (vDist[i] != INTINF) { cout << vDist[i] << '\n'; }
//        else { cout << "INF\n"; }
//    }
//}

//^^^ STL 사용 작성부분


const int INTINF = 1 << 30;

struct PathDist
{
	int d, v;
	PathDist() {};
	PathDist(int d, int v) : d(d), v(v) {}
};

void heapify(PathDist* arr, int& len, int idx)
{
	int left = idx * 2;
	int right = idx * 2 + 1;
	int min = idx;
	PathDist temp;

	if (right <= len && arr[right].d < arr[min].d) { min = right; }

	if (left <= len && arr[left].d < arr[min].d) { min = left; }

	if (idx != min)
	{
		temp = arr[min];
		arr[min] = arr[idx];
		arr[idx] = temp;

		heapify(arr, len, min);
	}
}

PathDist extractMin(PathDist* arr, int& len)
{
	PathDist ret = arr[1];

	arr[1] = arr[len--];
	heapify(arr, len, 1);

	return ret;
}

void push(PathDist* arr, PathDist target, int& len)
{
	arr[++len] = target;
	int idx = len;
	PathDist temp;

	while (idx != 1)
	{
		if (arr[idx].d < arr[idx / 2].d)
		{
			temp = arr[idx];
			arr[idx] = arr[idx / 2];
			arr[idx / 2] = temp;

			idx = idx / 2;
		}
		else { break; }
	}
}

int vDist[20001];
bool visited[20001];
list<PathDist> adjList[20001];

void Q1()
{
	int V, E, ST;
	int s, e, w, len;
	len = 0;

	cin >> V >> E >> ST;

	PathDist minHeap[30000];
	PathDist cur;

	for (int i = 1; i <= V; i++)
	{
		vDist[i] = INTINF;
	}

	for (int i = 0; i < E; i++) 
	{ 
		cin >> s >> e >> w; 
		adjList[s].push_back(PathDist(w, e));
	}
	
	vDist[ST] = 0;
	push(minHeap, PathDist(0, ST), len);

	while(len)
	{
		do
		{
			cur = extractMin(minHeap, len);
		} while (visited[cur.v]);
		
		for (list<PathDist>::iterator::value_type& it : adjList[cur.v])
		{
			if (vDist[it.v] > cur.d + it.d)
			{
				vDist[it.v] = cur.d + it.d;
				push(minHeap, PathDist(vDist[it.v], it.v), len);
			}
		}
	}

	for (int i = 1; i <= V; i++)
	{
		if (vDist[i] != INTINF) { cout << vDist[i] << '\n'; }
		else { cout << "INF\n"; }
	}
}
