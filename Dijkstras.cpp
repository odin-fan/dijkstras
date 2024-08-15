#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

class Pair
{
	public:
		int name;
		int value;
		Pair(const int& n, const int v): name(n), value(v) {}
};

class Nodeinfo
{
public:
	int name;
	int val;
	
	Nodeinfo(){}
	Nodeinfo(const int& s, const int v): name(s), val(v) {} 
};

class NodeinfoComp
{
	public:
	bool operator() (const Nodeinfo& a, const Nodeinfo& b)
	{
		return a.val > b.val;
	}
};

void findyourplace(map<string,int>& a,string& s, int& token)
{
	if(a.find(s) == a.end())
	{
		a[s] = token;
		token++;		
	}
}

void explore(const int num,vector < list < Pair > >& graph, priority_queue<Nodeinfo, vector<Nodeinfo>, NodeinfoComp>& heap, vector<int>& arr)
{
	list<Pair>::iterator it;
	for(it = graph[num].begin();it != graph[num].end(); it++)
	{
		if((*it).value + arr[num] < arr[(*it).name])
		{
			arr[(*it).name] = (*it).value + arr[num];
			heap.push(Nodeinfo((*it).name,arr[(*it).name]));
		}
		else
		continue;
	}
}

int main()
{
	int numofplaces;
	priority_queue<Nodeinfo, vector<Nodeinfo>, NodeinfoComp> heap;
	vector < list < Pair > > graph;
	map<string,int> a;
	cin>>numofplaces;
	for(int k = 0;k<numofplaces;k++)
	{
		int token = 0,z;
		int numofnodes,links,cost;
		string nodename,node,conn;
		list<Pair>::iterator it;
		cin >> nodename >> numofnodes;
		vector<int> arr(numofnodes,INT_MAX);	
		graph.resize(numofnodes);
		for(int i = 0;i<numofnodes;i++)
		{	
			cin>>nodename>>links;
			findyourplace(a,nodename,token);	
			for(int j = 0 ;j<links;j++)
			{
				cin>>conn>>cost;
				findyourplace(a,conn,token);	
				z = a.find(conn)->second;
				graph[i].push_back( Pair(z,cost) );		
			}
		}

		heap.push(Nodeinfo(0,0));		
		arr[0] = 0;
		
		while(!heap.empty())	
		{
			Nodeinfo temp;
			temp = heap.top();		
			explore(temp.name,graph,heap,arr);		
			heap.pop();		
		}
		cout<<"The shortest distance to the last node is "<<endl;
		cout<<"#"<<k+1<<" : "<<nodename<<", "<<arr[arr.size()-1]<<" tokens."<<endl;
		a.clear();		
		graph.clear();
		arr.clear();
	}
}
