// Weighted_Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include<iostream>
#include<set>                   //to create empty set
#include<list>                  //to create empty list and store nodes
#include<algorithm>             //to use min_element function in dijkstra
#define infinity 1410065407;    //define max value

using namespace std;

typedef struct nodes {      //define nodes to hold destination and weight
    int end;
    int cost;
}node;

class Graph {               //class of graph
    int N;                  //number of nodes
    list<node>* head;       //pointer to follow list

private:
    void printList(int src, list<node> l) {     //function to print list

        list<node> ::iterator it;
        for (it = l.begin(); it != l.end(); it++) {
            cout << "source: " << src << "destination: " << (*it).end << "weight: " << (*it).cost;
        }
        cout << endl;
    }
public:
    
    Graph(int node_num) {           //constructor of graph
        N = node_num;               //assign number of nodes and pointer
        head = new list<node>[N];
    }

    void add_edge(int source, int end, int cost) {      //adding edge to graph
        node new_node;
        new_node.end = end;
        new_node.cost = cost;
        head[source].push_back(new_node);
    }

    void show_edges() {                   //printing all edges
        for (int i = 0; i < N; i++) {
            list<node> tempList = head[i];
            printList(i, tempList);
        }
    }

    friend void Dijkstra(Graph g, int* dist, int* prev, int start);     //friend class to access private and protected members of other class
};

void Dijkstra(Graph g, int* dist, int* prev, int start) {       //Dijkstra algorith to find shortest paths
    int n = g.N;
    for (int i = 0; i < n; i++) {
        dist[i] = infinity;             //set as infinity
        prev[i] = -1;                   //undefined previous
    }

    dist[start] = 0;                    //distance of start is 0
    set<int> Set;                       //create empty set and list
    list<int> List;

    for (int i = 0; i < n; i++) {
        List.push_back(i);              //add each node into queue
    }

    while (!List.empty()) {     // while List is not empty:

        list<int> ::iterator it;
        it = min_element(List.begin(), List.end());  //find minimum element from list
        int i = *it;        
        List.remove(i);     //remove min element from list
        Set.insert(i);      //insert minimum element to set

        list<node> ::iterator a;
        for (a = g.head[i].begin(); a != g.head[i].end(); a++) {   // for each neighbor nodes of i
            if ((dist[i] + (a->cost)) < dist[a->end]) { 
                dist[a->end] = (dist[i] + (a->cost));
                prev[a->end] = i;                   // Reorder nodes in the list
            }
        }
    }
    for (int i = 0; i < n; i++)     //print paths
        if (i != start)
            cout << start << " to " << i << ", Cost: " << dist[i] << " Previous: " << prev[i] << endl;
}


int main() {


    Graph graph(5);
    int dist[5], prev[5];

    graph.add_edge(0, 1, 3);        //Create edges of graph
    graph.add_edge(0, 3, 7);
    graph.add_edge(0, 4, 8);
    graph.add_edge(1, 3, 4);
    graph.add_edge(1, 2, 1);
    graph.add_edge(3, 2, 2);
    graph.add_edge(4, 3, 3);


    Dijkstra(graph, dist, prev, 0);     //print shortest paths from node 0 to all others
    cout << endl;
    Dijkstra(graph, dist, prev, 1);     //print shortest paths from node 1 to all others
    cout << endl;
    Dijkstra(graph, dist, prev, 2);     //print shortest paths from node 2 to all others
    cout << endl;
    Dijkstra(graph, dist, prev, 3);     //print shortest paths from node 3 to all others
    cout << endl;
    Dijkstra(graph, dist, prev, 4);     //print shortest paths from node 4 to all others
    cout << endl;

    return 0;
}
