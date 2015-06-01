#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// To store traffic table from file
struct traffic_s{
	int node1, node2;
	int load;
};

// To store node locations
struct location{
	int node, x, y;
};

//A link on MST
struct Link_s{
	int node1, node2, traffic;
	float weight;
	bool added2tree;
};

// To keep track of connected components in graph
struct Set_s{
	int val;
	int type;
};

// Distance between nodes
struct Dist_s{
	int mark;
	float val;
};

struct Children_s {
	int node;
	struct Children_s *next;
};
// Tree to trace path between a pair of nodes
struct Node_s{
	int parent;
	Children_s child;
};

enum type{VERTEX, SET};
enum mark{SEEN, NOT_SEEN};

Dist_s **edge_weight;
Set_s *set;
Link_s *link;
Node_s *nodes;
traffic_s *traffTable;
location *node_loc;
int trTable_sz = 0, num_nodes = 0, root;

// function declarations
void ComputeLinkLoad();
int FindPath(int n1, int n2, int *path);
void FindMST();
void MakeTree();
void MergeSets (int chosen_set, int other_set);
float FindAndMarkMinEdge(int *node1, int *node2);
int SearchLink(int node1, int node2);

int main()
{
	string line;
	int index;
	ifstream myfile;

	// read number of lines in each file
	myfile.open("traffictable.txt");
	while(getline(myfile,line))
		trTable_sz++;
	traffTable = new traffic_s[trTable_sz];
	myfile.close();
	myfile.clear();
	myfile.open("nodelocations.txt");
	while(getline(myfile,line))
		num_nodes++;
	node_loc = new location[num_nodes];
	myfile.close();
	myfile.clear();

	//parse both files. Store traffic table	and node locations
	myfile.open("traffictable.txt");
	index = 0;
	while( getline (myfile,line) && index < trTable_sz)
	{
		string substring;
		int pos = line.find_first_not_of("\t ", 0);
		int pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		traffTable[index].node1 = atoi(substring.c_str());

		pos = line.find_first_not_of("\t ",pos1);
		pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		traffTable[index].node2 = atoi(substring.c_str());

		pos = line.find_first_not_of("\t ",pos1);
		pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		traffTable[index].load = atoi(substring.c_str());
		index++;
	}
	myfile.close();
	myfile.clear();

	myfile.open("nodelocations.txt");
	index = 0;
	while( getline (myfile,line) && index < num_nodes)
	{
		string substring;
		int pos = line.find_first_not_of("\t ", 0);
		int pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		node_loc[index].node = atoi(substring.c_str());

		pos = line.find_first_not_of("\t ",pos1);
		pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		node_loc[index].x = atoi(substring.c_str());

		pos = line.find_first_not_of("\t ",pos1);
		pos1 = line.find_first_of("\t ", pos);
		substring = line.substr(pos,pos1-pos);
		node_loc[index].y = atoi(substring.c_str());
		index++;
	}
	myfile.close();

	// compute distances between nodes
	edge_weight = new Dist_s*[num_nodes];
	for(int i = 0; i < num_nodes; i++)
		edge_weight[i] = new Dist_s[num_nodes];

	for(int i = 0; i < num_nodes; i++)
		for(int j = 0; j < num_nodes; j++)
		{
			edge_weight[i][j].val = 0;
			edge_weight[i][j].mark = NOT_SEEN;
			// No need to populate entire 2-d array (i.e. dist[1][2] is same as dist[2][1], dist[1][1] is 0)
			if(i < j)
				// store distance
				edge_weight[i][j].val = pow(float(pow(float(node_loc[i].x - node_loc[j].x), (int)2) + pow(float(node_loc[i].y - node_loc[j].y), (int)2)), (float)0.5);
		}

	set = new Set_s[num_nodes];
	link = new Link_s[num_nodes-1];
	nodes = new Node_s[num_nodes];

	//Initialize arrays
	for(int i = 0; i < num_nodes-1; i++)
	{
		link[i].added2tree = false;
		link[i].traffic = 0;
	}
	for(int i = 0; i < num_nodes; i++)
	{
		nodes[i].parent = -1;
		nodes[i].child.next = NULL;
		nodes[i].child.node = -1;
	}

	FindMST();
	ComputeLinkLoad();

	// Compute and print link utilization
	printf("\n2. Link utilization:\n\n");
	float max_util = 0, av_util = 0;
	for(int i = 0; i < num_nodes -1; i++)
	{
		float utilz = ((float)link[i].traffic*100)/1544;
		av_util += utilz;
		if(utilz > max_util)
			max_util = utilz;
		printf("\t%2d %2d %4d Kbps %2.2f %%\n", link[i].node1 + 1, link[i].node2 + 1, link[i].traffic, utilz);
	}
	av_util /= (num_nodes -1);
	printf("\n\tMaximum Utilization = %0.2f %%\n", max_util);
	printf("\tAverage Utilization = %0.2f %%\n", av_util);

	//Compute and print load between each node pair
	int *path;
	path = new int[num_nodes];
	int hops = 0, link_index;
	int traffic_num = 0, traffic_den = 0;
	printf("\n3. Path Lengths:\n\n");
	for(int i = 0; i < num_nodes; i++)
	{
		for(int j = i+1; j < num_nodes; j++)
		{
			int load = 0;
			// Find path from node A to node B
			hops = FindPath(i, j, path);
			// Add load on each link between A and B, to find total load between A and B
			for(int j1 = 0; j1 < hops; j1++)
			{
				if((link_index = SearchLink(path[j1],path[j1+1])) != -1)
					load += link[link_index].traffic;
				else
					cout << "Error: Searchlink\n";
			}
			printf("\t%2d %2d %5d Kbps %2d hops\n", i+1, j+1, load, hops);
			traffic_num += load*hops;
			traffic_den += load;
		}
	}
	float av_hops = ((float)traffic_num)/traffic_den;
	printf("\n\tAverage Hops = %f\n", av_hops);
	printf("\tAverage Delay = %0.2f\n", (0.0027*av_hops)/(1-(max_util/100)));
	cin.get();
}

/*
 * Search for the link which has node1 and node2 as it's ends
 */
int SearchLink(int node1, int node2)
{
	for(int i1 = 0; i1 < num_nodes-1; i1++)
		if((node1 == link[i1].node1 && node2 == link[i1].node2) ||
				(node1 == link[i1].node2 && node2 == link[i1].node1))
					return i1;
	return -1;
}

/*
 * Find the route between a node pair
 * input: nodes (n1,n2), *path - to store nodes traversed from n1 to n2
 * output: number of hops between n1 and n2
 */
int FindPath(int n1, int n2, int *path)
{
	int *path1, *path2;
	path1 = new int[num_nodes];
	path2 = new int[num_nodes];
	int cnt1 = 0, cnt2 = 0;
	int myparent = nodes[n1].parent;
	int index1 = 0, index2 = 0;
	bool found = false;

	// Find path from n1 to root node
	path1[cnt1] = n1;
	cnt1++;
	while(myparent != -1)
	{
		path1[cnt1] = myparent;
		myparent = nodes[myparent].parent;
		cnt1++;
	}

	// Find path from n2 to root node
	myparent = nodes[n2].parent;
	path2[cnt2] = n2;
	cnt2++;
	while(myparent != -1)
	{
		path2[cnt2] = myparent;
		myparent = nodes[myparent].parent;
		cnt2++;
	}

	// Find the lowest common ancester
	for(int j = 0; j < cnt1; j++)
	{
		for(int k = 0; k < cnt2; k++)
		{
			if(path2[k] == path1[j])
			{
				index1 = j;
				index2 = k;
				found = true;
				break;
			}
		}
		if(found == true)
			break;
	}
	if(found == false)
		cout << "ERROR: no common ancester\n";

	// Store the total path from n1 to n2 in path
	for(int j = 0; j < index1; j++)
		path[j] = path1[j];
	for(int j = index2,i=0; j >= 0; j--,i++)
		path[i+index1] = path2[j];
	return index1+index2;
}

/*
 * Use traffic table to compute load each link in MST
 * *** Not considering the direction of traffic ****
 */
void ComputeLinkLoad()
{	int *path;
	path = new int[num_nodes];
	int index;
	for(int i = 0; i < trTable_sz; i++)
	{
		// Find path between nodes
		index = FindPath(traffTable[i].node1-1, traffTable[i].node2-1, path);
		// compute load on each link in the path
		for(int j = 0; j < index; j++)
		{
			int link_index;
			if((link_index = SearchLink(path[j], path[j+1])) != -1)
				link[link_index].traffic += traffTable[i].load;
			else
				cout << "Error: Searchlink\n";
		}
	}
}

/*
 * Find Minimum Spanning Tree
 */
void FindMST()
{
	int node1, node2;
	int link_cnt = 0;

	//Initialize set array
	for(int i = 0; i < num_nodes; i++)
	{
		set[i].type = VERTEX;
		set[i].val = i;
	}
	while(1)
	{
		// Find the minimum weight edge which has not been looked at yet
		// node1 and node2 are the two ends of the minimum edge
		float weight = FindAndMarkMinEdge(&node1,&node2);
		// Check if an unseen min edge was returned
		if(weight == -1)
			break;
		// None of the nodes belong to a connected set
		if (set[node1].type == VERTEX && set[node2].type == VERTEX)
		{
			// Add the nodes to one set
			int set_num = node1 < node2 ? node1 : node2;
			set[node1].type = SET;
			set[node2].type = SET;
			set[node1].val = set_num;
			set[node2].val = set_num;
		} else if (set[node1].type == VERTEX && set[node2].type == SET) {
			// If one node belongs to connected set and other does not, add other node to this set too
			set[node1].type = SET;
			set[node1].val = set[node2].val;
		} else if (set[node1].type == SET && set[node2].type == VERTEX) {
			// If one node belongs to connected set and other does not, add other node to this set too
			set[node2].type = SET;
			set[node2].val = set[node1].val;
		} else if (set[node1].type == SET && set[node2].type == SET) {
			// Do not add link if both nodes are part of the same set
			if(set[node1].val != set[node2].val) {
				MergeSets(set[node1].val, set[node2].val);
			}
			else {
				// avoid loop: link not added
				continue;
			}

		}
		if(link_cnt >= num_nodes-1)
		{
			cout << "ERROR: link count\n";
			break;
		}
		// This link is be added to MST.
		link[link_cnt].node1 = node1;
		link[link_cnt].node2 = node2;
		link[link_cnt].weight = weight;
		link_cnt++;

		int in = 0, set_num = -1;
		// Continue till all nodes are connected
		// 1. All nodes belong to a set AND
		// 2. All nodes to belong to the same set (or are connected)
		for(int in = 0; in < num_nodes; in++)
		{
			if(set[in].type != SET)
				break;
			if(set_num == -1)
				set_num = set[in].val;
			else if(set[in].val != set_num)
				break;
		}
		// done. All nodes are connected (part of the same set)
		if (in == num_nodes)
			break;
	}

	// print out MST
	float sum = 0;
	printf("1. Minimum spanning tree (MST):\n\n");
	for(int i = 0; i < num_nodes-1; i++)
	{
		printf("\t%2d %2d %3.2f\n",link[i].node1+1, link[i].node2+1, link[i].weight);
		sum += link[i].weight;
	}
	printf("\n\tMST Weight = %f\n", sum);
	// Create tree for finding path between nodes
	MakeTree();
}

/*
 * Create Tree of using nodes and edges in MST
 */
void MakeTree()
{
	bool repeat = false;

	// Start by selecting a link and marking one node as root and other as it's child
	root = link[0].node1;
	nodes[link[0].node1].parent = -1;
	nodes[link[0].node1].child.node = link[0].node2;
	nodes[link[0].node2].parent = root;
	nodes[link[0].node2].child.node = -1;
	nodes[link[0].node2].child.next = NULL;
	link[0].added2tree = true;
	do
	{
		// repeat till all nodes are added to tree
		repeat = false;
		for(int i = 1; i < num_nodes-1; i++)
		{
			// Skip if link is already added
			if(link[i].added2tree == true)
				continue;
			else
			{
				Children_s *other_child, *temp;
				int mynode, otherNode;
				// Check if either one of the end nodes of the link are added to tree.
				// If so, add the other node as this node's child
				if(nodes[link[i].node1].parent != -1 || nodes[link[i].node1].child.node != -1)
				{
					// This node is part of the tree
					mynode = link[i].node1;
					if(nodes[link[i].node2].parent != -1 || nodes[link[i].node2].child.node != -1)
					{
						cout << "Error: Loop detected\n";
						break;
					}
					else
						otherNode = link[i].node2;

				}
				else if(nodes[link[i].node2].parent != -1 || nodes[link[i].node2].child.node != -1)
				{
					mynode = link[i].node2;
					if(nodes[link[i].node1].parent != -1 || nodes[link[i].node1].child.node != -1)
					{
						cout << "Error: Loop detected\n";
						break;
					}
					else
						otherNode = link[i].node1;
				}
				// One node must be in the tree to link the other node to tree
				// None of the nodes are in the tree yet. skip and revisit later in next cycle.
				else
				{
					// Will need to repeat the scanning of links
					repeat = true;
					continue;
				}
				// If the node in the tree already has a child, add the other node as additional children (*next)
				if(nodes[mynode].child.node != -1)
				{
					// mynode has atleast one child
					temp = &nodes[mynode].child;
					other_child = nodes[mynode].child.next;
					while(other_child != NULL)
					{
						temp = other_child;
						other_child = other_child->next;
					}
					other_child = temp;
					other_child->next = new Children_s;
					other_child->next->node = otherNode;
					other_child->next->next = NULL;
				}
				else
				{
					nodes[mynode].child.node = otherNode;
					nodes[mynode].child.next = NULL;
				}
				// Set the node already in tree as parent of the other node
				nodes[otherNode].parent = mynode;
				nodes[otherNode].child.node = -1;
				nodes[otherNode].child.next = NULL;
				link[i].added2tree = true;
			}
		}
	}while(repeat == true);
}

/*
 * Connect two disconnected graphs/sets
 */
void MergeSets (int chosen_set, int other_set)
{
	for(int i = 0; i < num_nodes; i++)
		if(set[i].val == other_set)
			set[i].val = chosen_set;
}

/*
 * Find the minimum distance edge and mark it as seen/visited
 */
float FindAndMarkMinEdge(int *node1, int *node2)
{
	int index_i = 0, index_j=0;
	float min = 9999;
	for(int i = 0; i < num_nodes-1; i++)
	{
		for(int j = 1+i; j < num_nodes; j++)
		{
			if(edge_weight[i][j].val < min && edge_weight[i][j].mark == NOT_SEEN)
			{
				min = edge_weight[i][j].val;
				index_i = i;
				index_j = j;
			}
		}
	}
	if(index_i == 0 && index_j == 0)
		return -1;
	edge_weight[index_i][index_j].mark = SEEN;
	*node1 = index_i;
	*node2 = index_j;
	return edge_weight[index_i][index_j].val;
}
