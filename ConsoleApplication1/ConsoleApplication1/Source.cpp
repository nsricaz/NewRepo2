using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include<functional>
#include <limits> // for numeric_limits
#include<map>
#include<algorithm>
#include<functional>
#include<stdlib.h>
#include<Windows.h>
#include<list>
#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

using namespace std;
typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef vector<vector<neighbor> > adjacency_list_t;
typedef pair<weight_t, vertex_t> weight_vertex_pair_t;

void DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	vector<weight_t> &min_distance,
	vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	// we use greater instead of less to turn max-heap into min-heap
	priority_queue<weight_vertex_pair_t,
		vector<weight_vertex_pair_t>,
		greater<weight_vertex_pair_t> > vertex_queue;
	vertex_queue.push(make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.top().first;
		vertex_t u = vertex_queue.top().second;
		vertex_queue.pop();

		// Because we leave old copies of the vertex in the priority queue
		// (with outdated higher distances), we need to ignore it when we come
		// across it again, by checking its distance against the minimum distance
		if (dist > min_distance[u])
			continue;

		// Visit each edge exiting u
		const vector<neighbor> &neighbors = adjacency_list[u];
		for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.push(make_pair(min_distance[v], v));

			}

		}
	}
}


list<vertex_t> DijkstraGetShortestPathTo(
	vertex_t vertex, const vector<vertex_t> &previous)
{
	list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


struct Kordinate
{
	int x;
	int y;
	Kordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

void PRINT(map<int, Kordinate>&mm, list<int>&l, int KRAJ) {

	for (auto it = l.begin(); it != l.end(); it++)
	{
		int m = mm.at(*it).x;//redak
		int n = mm.at(*it).y;//stupac

		int k1 = mm.at(KRAJ).x;
		int k2 = mm.at(KRAJ).y;

		for (int i = 0; i < 20; i++)
		{

			for (int j = 0; j < 40; j++)
			{
				if (j == n && i == m)
				{
					cout << "A";
				}
				if (i == k1 && j == k2)
				{
					cout << "B";
				}
				else
				{
					cout << "*";
				}

			}
			cout << endl;

		}
		Sleep(0700);
		system("CLS");
	}

}
int main() {

	map<int, Kordinate> mp;

	list<int>l;
	int ki = 0;
	for (int i = 0; i < 800; i += 40)
	{
		l.push_back(i + ki);
		ki++;
	}
	/*for (auto  i = l.begin(); i !=l.end(); i++)
	{
	cout << *i << endl;
	}*/
	Kordinate t(0, 0);
	int koo = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			t.x = i;
			t.y = j;
			mp.insert(pair<int, Kordinate>(koo, t));
			koo++;
		}

	}
	/*cout << mp[35].x << endl;*/



	//	PRINT(mp, l);


	//for (int j = 39; j < 800; j+=40)
	//{
	//	PRINT(mp,l);
	//	Sleep(0700);
	//	system("CLS");
	//}



	/*Kordinate v(0, 1);
	mp.at(16).x = 0;
	mp.at(16).y = 1;*/

	//auto it=mp.find(41);
	//cout << it->second.x << endl;
	//cout << it->second.y << endl;

	// remember to insert edges both ways for an undirected graph
	adjacency_list_t adjacency_list(800);
	// 0 = a
	//adjacency_list[1].push_back(neighbor(2, 1));
	int k = 1;
	int m = 40;
	for (int i = 1; i <800; i += 40)
	{
		if (i>759)
		{
			adjacency_list[i - 1].push_back(neighbor(i, 1));
			adjacency_list[i - 1].push_back(neighbor(i - 39, 1));
			adjacency_list[i].push_back(neighbor(i + 1, 1));
			adjacency_list[i].push_back(neighbor(i - 1, 1));
			adjacency_list[i].push_back(neighbor(i - 40, 1));
			//cout << i - 1 << "-" << "ima susjede:" << i << "-"<<i-39<< endl;
			//cout << i << "-" << "ima susjede:" << i + 1 << "-"<<i-1<<"-" << i -40 << endl;

			for (int j = i + 1; j < m; j++)
			{

				if (m <= 40)
				{
					if (j == m - 1)
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 40, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << "-" << j + 40 << "-" << "-" << endl;

					}
					else
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 1, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << j + 1 << "-" << endl;

					}
				}



				else if (m>40)
				{
					if (j == m - 1)
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j - 40, 1));
						//	cout << j << "-" << "ima susjede:" << j - 1 << "-" << "-" << "-" << "-" << j - 40 << endl;

					}
					else
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 1, 1));
						adjacency_list[j].push_back(neighbor(j - 40, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << j + 1 << "-" << "-" << j - 40 << endl;
						//				cout << j+1 << "-" << "ima susjede:" << j + 1 << "-" << j - 40 << "-" << j + 40 << endl;
					}
				}
			}
		}

		else
		{
			adjacency_list[i - 1].push_back(neighbor(i + 1, 1));
			adjacency_list[i - 1].push_back(neighbor(i + 39, 1));
			adjacency_list[i].push_back(neighbor(i - 1, 1));
			adjacency_list[i].push_back(neighbor(i + 1, 1));
			adjacency_list[i].push_back(neighbor(i + 40, 1));
			//cout << i - 1 << "-" << "ima susjede:" << i + 1 << "-" << i + 39 << endl;
			//cout << i << "-" << "ima susjede:" << i - 1 << "-" << i + 1 << "-" << i + 40 << endl;

			for (int j = i + 1; j < m; j++)
			{

				if (m <= 40)
				{
					if (j == m - 1)
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 40, 1));
						adjacency_list[j].push_back(neighbor(j + 39, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << "-" << j + 40 << "-" << j + 39 << "-" << endl;

					}
					else
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 1, 1));
						adjacency_list[j].push_back(neighbor(j + 40, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << j + 1 << "-" << j + 40 << endl;

					}
				}



				else if (m>40)
				{
					if (j == m - 1)
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 40, 1));
						adjacency_list[j].push_back(neighbor(j + 39, 1));
						adjacency_list[j].push_back(neighbor(j - 40, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << "-" << j + 40 << "-" << j + 39 << "-" << j - 40 << endl;

					}
					else
					{
						adjacency_list[j].push_back(neighbor(j - 1, 1));
						adjacency_list[j].push_back(neighbor(j + 1, 1));
						adjacency_list[j].push_back(neighbor(j + 40, 1));
						adjacency_list[j].push_back(neighbor(j - 40, 1));
						//cout << j << "-" << "ima susjede:" << j - 1 << "-" << j + 1 << "-" << j + 40 << "-" << j - 40 << endl;
						//				cout << j+1 << "-" << "ima susjede:" << j + 1 << "-" << j - 40 << "-" << j + 40 << endl;
					}
				}
			}
		}
		m += 40;
	}

	vector<weight_t> min_distance;
	vector<vertex_t> previous;
	int POCETAK;
	int KRAJ;
	cout << "Krecemo od (0-799)-A ?";
	cin >> POCETAK;
	cout << "Cilj:-B ";
	cin >> KRAJ;
	DijkstraComputePaths(POCETAK, adjacency_list, min_distance, previous);
	//	cout << "Distance from 0 to 4: " << min_distance[0] << endl;
	list<vertex_t> path = DijkstraGetShortestPathTo(KRAJ, previous);
	//cout << "Path : ";
	//int ko = 0;
	//	map<int, Kordinate> mp;
	PRINT(mp, path, KRAJ);
	//copy(path.begin(), path.end(), ostream_iterator<vertex_t>(cout, " "));
	//cout << endl;


	return 0;
}