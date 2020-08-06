#include <iostream>
using namespace std;

class Node
{ 
	int V2;
	int W;
	Node *Next;

	friend class List;
};


class List
{
	private:
		Node *Front;
		int n;

	public:
		List()				{ Front=NULL; n=0; }
		int Getn()			{ return n; }
		int Empty()			{ return Front == NULL; }
		Node* GetFront()	{ return Front; }

		void AddLast(int d , int e)
		{	n++;
			Node*a=new Node ;
			a->Next=NULL;
			a->V2=d;
			a->W=e;

			if( Empty() )
			{ Front=a; return; }	

			Node*p=Front;
			while(p->Next)
			p=p->Next;
			p->Next=a;
		}

		void Print(int i)
		{
			Node*p=Front;
			while(p)
			{
				cout<<p->V2<<") has the weight of "<<p->W<<endl;
				if(p->Next)
					cout<<endl<<"Edge ("<<i<<",";
				p=p->Next;
			}
		}
};
 
class Graph
{
	private:
		List *AdjList;
		int Nodes;

	public :
		Graph(int V)
		{	Nodes=V+1;
			AdjList= new List [Nodes];
		}

		void Add(int a , int b , int c )
		{   if (a>=Nodes) return;
				AdjList[a].AddLast(b,c);
		}

		void AdjListPrint()
		{   for (int i=1 ; i<Nodes ; i++)
			{   cout<<"Edge ("<<i<<",";
				AdjList[i].Print(i);
				cout<<endl;
			}
		}
};

//////////////////////////////////////////////////////

int find(int i, int *parent) 
{ 
    while ( parent[i] != i ) 
        i = parent[i]; 
    return i; 
} 

void unio(int i, int j, int *parent) 
{ 
    int a = find(i,parent); 
    int b = find(j,parent); 
    parent[a] = b; 
} 

void kruskal(int **matrix, int nodes) 
{ 
	int *parent = new int[nodes];
    int c=0, c2=0; 

    for (int i = 1; i <= nodes; i++) 
        parent[i] = i; 

    while (c2 < nodes - 1) { 
        int min=999, a=-1, b=-1; 
        for (int i = 1; i <= nodes; i++) 
		{	for (int j = 1; j <= nodes; j++) 
			{	if (find(i,parent) != find(j,parent) && matrix[i][j] < min) 
				{   min = matrix[i][j]; 
                    a = i; 
                    b = j; 
                } 
            } 
        } 
  
        unio(a,b,parent); 
		cout<<"("<<a<<","<<b<<")"<<endl;
		c2++;
        c+= min;

    } 
	cout<<"\nThe weight of the above network is: "<<c<<endl;
} 

//////////////////////////////////////////////////////

int minKey(int key[], bool mstSet[], int nodes) 
{
	int min = 999, min_index;

	for (int v = 1; v <= nodes; v++) 
		if (mstSet[v] == false && key[v] < min) 
			min = key[v], min_index = v;
	return min_index; 
}

void printMST(int parent[], int nodes, int **matrix) 
{
	int c=0;
	for (int i = 2; i <= nodes; i++)
		{
			cout<<"("<<parent[i]<<","<<i<<")"<<endl;
			c+=matrix[i][parent[i]];
		}
	cout<<"\nThe weight of the above network is: "<<c<<endl<<endl;
}

void prim(int **matrix, int nodes, int s) 
{ 
	int *parent = new int[nodes];
	int *key = new int[nodes];
	bool *mstSet = new bool[nodes];
  
    for (int i = 1; i <= nodes; i++) 
        key[i] = 999, mstSet[i] = false; 
  
	//key[1] = s;
    key[1] = 1;
    parent[1] = -1;

    for (int count = 1; count <= nodes-1; count++) 
    { 
        int u = minKey(key, mstSet, nodes); 
  
        mstSet[u] = true; 
        for (int v = 1; v <= nodes; v++) 
			if (matrix[u][v] && mstSet[v] == false && matrix[u][v] < key[v]) 
				parent[v] = u, key[v] = matrix[u][v]; 
    } 
    printMST(parent, nodes, matrix); 
} 

//////////////////////////////////////////////////////

int minDistance(int *dist, bool *sptSet, int V) 
{ 
    int min = 999, min_index; 
    for (int v = 1; v <= V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
    return min_index; 
} 

void printPath(int parent[], int j) 
{ 
    if (parent[j] == -1) 
        return;

    printPath(parent, parent[j]);
	cout<<j<<" ";
} 

void printSolution(int dist[], int V,  int parent[], int src) 
{ 
    for (int i = src+1; i <= V; i++) 
    { 
		cout<<endl<<"The shortest path from "<<src<<" to "<<i<<" is: '  "<<src<<" ";
        printPath(parent, i); 
		cout<<"\t'  and has the length of "<<dist[i];
    } 
	cout<<endl<<endl;
} 

void dijkstra(int **matrix, int src , int V) 
{ 
	int *dist = new int[V];
	int *parent = new int[V];
	bool *sptSet = new bool[V];

    for (int i = 1; i <= V; i++) 
    { 
        parent[src] = -1; 
        dist[i] = 999; 
        sptSet[i] = false; 
    } 

    dist[src] = 0; 
    for (int count = 1; count <= V - 1; count++) 
    { 
        int u = minDistance(dist, sptSet, V); 
        sptSet[u] = true; 
        for (int v = 1; v <= V; v++) 
            if (!sptSet[v] && matrix[u][v] && 
                dist[u] + matrix[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + matrix[u][v]; 
            }  
    } 
    printSolution(dist, V, parent, src); 
} 

//////////////////////////////////////////////////////
void main()
{
		int Enter=0,nodes=0,edges=0;
		
		cout<<endl<<"Please enter the number of nodes: ";
		cin>>nodes;
		
		cout<<endl;
		
		cout<<"Please enter the number of edges: ";
		cin>>edges;

		//////////////////////////////////
		/****************************/
		struct SGraph { int v1,v2,w; };
		SGraph* one = new SGraph[edges];
		/****************************/
		int ve1=0,ve2=0,we=0;
		//int n=nodes+1;

		int **matrix = new int*[nodes];
		for(int i=1 ; i<=nodes ; i++)
			matrix[i] = new int[nodes];

		for(int i=1 ; i<=nodes ; i++)
			for(int j=1 ; j<=nodes ; j++)
				matrix[i][j] = 999;
		/****************************/
		int V1,V2,W;
		Graph X(nodes);
		/****************************/

		for(int i=1 ; i<=edges ; i++)
		{
			cout<<endl<<"Please enter edge"<<i<<" and its weight in the order (vertex, vertex, weight):"<<endl;
			cin>>one[i].v1;
			cin>>one[i].v2;
			cin>>one[i].w;
			cout<<endl;

			ve1=one[i].v1;
			ve2=one[i].v2;
			we=one[i].w;

			V1=one[i].v1;
			V2=one[i].v2;
			W=one[i].w;

			while(one[i].v1>nodes || one[i].v2>nodes || one[i].v1<1 || one[i].v2<1)
			{
				cout<<endl<<"Incorrect Vertex, Please Enter again"<<endl;
				cout<<endl<<"Please enter edge"<<i<<" and its weight in the order (vertex, vertex, weight):"<<endl;
				cin>>one[i].v1;
				cin>>one[i].v2;
				cin>>one[i].w;
				cout<<endl;

				ve1=one[i].v1;
				ve2=one[i].v2;
				we=one[i].w;

				V1=one[i].v1;
				V2=one[i].v2;
				W=one[i].w;
			}

			matrix[ve1][ve2] = we;
			matrix[ve2][ve1] = we;
			cout<<endl;

			X.Add(V1,V2,W);
			X.Add(V2,V1,W);
		}
		//////////////////////////////////

		while ( Enter>=0 && Enter<=6 )
		{
			cout<<endl<<endl;
			cout<<"Please select one of the following: "<<endl;
			cout<<"1- Output the graph from the array of structures "<<endl;
			cout<<"2- Output the graph from the matrix "<<endl;
			cout<<"3- Output the graph from the array of linked lists "<<endl;
			cout<<"4- Apply Kruskal Algorithm "<<endl;
			cout<<"5- Apply Prims Algorithm "<<endl;
			cout<<"6- Apply Dijkstras Shortest Path Algorithm "<<endl;
			cout<<"7- Exit program "<<endl<<endl;
			cout<<"Enter a # : " ;
			cin>>Enter;

			cout<<endl;

			/*******************************************/

			if(Enter==1)
			{
				cout<<"The edges are: "<<endl;
				for(int i=1 ; i<=edges ; i++)
				{
					cout<<"Edge ("<<one[i].v1<<","<<one[i].v2<<") has the weight of "<<one[i].w<<endl;
					cout<<"Edge ("<<one[i].v2<<","<<one[i].v1<<") has the weight of "<<one[i].w<<endl;
				}
				cout<<endl<<endl;
			}

			/*******************************************/

			if(Enter==2)
			{
				cout<<"The edges are: "<<endl;
				for(int i=1 ; i<=nodes ; i++)
					for(int j=1; j<=nodes ; j++)
						if(matrix[i][j]!=999)
							cout<<"Edge ("<<i<<","<<j<<") has the weight of "<<matrix[i][j]<<endl;

				cout<<endl<<endl;
			}

			/*******************************************/

			if(Enter==3)
			{
				X.AdjListPrint();
			}

			/*******************************************/

			if(Enter==4)
			{
				
				/*for(int i=1 ; i<=nodes ; i++)
				{	cout<<endl;
					for(int j=1 ; j<=nodes ; j++)
						cout<<matrix[i][j]<<" ";
				}
				*/
				cout<<endl;
				kruskal(matrix,nodes);
			}

			/*******************************************/

			if(Enter==5)
			{
				int s;
				cout<<"Please choose a starting node to apply Prim’s algorithm: ";
				cin>>s;

				cout<<endl<<endl;
				prim(matrix,nodes,s);
			}

			/*******************************************/

			if(Enter==6)
			{
				int sn;
				cout<<"Please enter the source node to find the shortest paths (Dijkstra):  ";
				cin>>sn;

				cout<<endl<<endl;
				dijkstra(matrix, sn, nodes);
			}

			/*******************************************/

		}
}