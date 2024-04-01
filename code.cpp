#include<bits/stdc++.h>
using namespace std;

struct Graph
{
    int V; //Number of vertices
    vector<unordered_set<char>> adj; //Adjacency list

    Graph(int V) : V(V) 
    {
        adj.resize(V);
    }

    //Function to add an edge to the graph
    void addEdge(char u, char v) 
    {
        adj[u - 'a'].insert(v);
    }

    //Function to find pendant vertices
    set<char> findPendantVertices() 
    {
        set<char> pendantVertices;
        for (char u = 'a'; u < 'a' + V; ++u) {
            if (adj[u - 'a'].size() == 1) { // Check if vertex u is a pendant vertex
                pendantVertices.insert(u);
            }
        }
        return pendantVertices;
    }

    //Function to find the maximum degree vertex
    vector<char> findMaxDegreeVertex() {
        int maxDegree = 0;
        vector<char> maxDegreeVertices;

        for (char u = 'a'; u < 'a' + V; ++u)
        {
            if (adj[u - 'a'].size() > maxDegree) 
            {
                maxDegree = adj[u - 'a'].size();
                maxDegreeVertices.clear();
                maxDegreeVertices.push_back(u);
            } 
            else if(adj[u - 'a'].size() == maxDegree) 
            {
                maxDegreeVertices.push_back(u);
            }
        }
        return maxDegreeVertices;
    }

    // Function to remove a vertex and its incident edges from the graph
    void removeEdgeVertex(set<pair<char, char>> &E, char &u)
    {
        vector<pair<char, char>> toRemove;
        for(auto it:E)
        {
            if(it.first == u || it.second == u)
                toRemove.push_back(it);
        }
        for(auto it:toRemove)
        {
            E.erase(it);
        }

        for (char v : adj[u - 'a']) {
            adj[v - 'a'].erase(u);
        }
        adj[u - 'a'].clear();

    }

    //Function to compute the vertex cover using SD(G) algorithm
    set<char> findVertexCover() {
        set<char> VC; // Vertex cover
        set<pair<char, char>> E; // Set of remaining edges

        // Initialize E with all edges
        for (char u = 'a'; u < 'a' + V; ++u)
        {
            for (char v : adj[u - 'a'])
            {
                E.insert({u,v});
            }
        }

        set<char> P = findPendantVertices(); // Set of pendant vertices
        
        // Step 5: While P is not empty
        while(!P.empty())
        {
            // Step 7: Select any vertex u from P
            char u = *P.begin();
            // Step 8: Get an adjacent vertex v
            char v = *adj[u - 'a'].begin();
            // Step 9: Add v to VC
            VC.insert(v);
            /*
            cout<<"Added:"<<v<<endl;
            */
            // Step 10: Remove edges incident on v
            removeEdgeVertex(E, v);
            // Update P and E
            P = findPendantVertices();
        }

        // Step 13: While E is not empty
        while (!E.empty()) {
            // Step 15: Find maximum degree vertex
            vector<char> maxDegreeVertices = findMaxDegreeVertex();

            /*
            cout<<"Max degree vertices are: "<<endl;
            for(auto max: maxDegreeVertices){
            	cout<<max<<" ";
            }
            cout<<endl;
            */

            // Step 18: Choose the maximum degree vertex that covers a unique edge among all maximum degree vertices
			char m = maxDegreeVertices[0]; // Initialize with the first vertex in the list
			bool found = false;

			// Iterate over each maximum degree vertex
			for (char u : maxDegreeVertices)
            {
			    // Check if the current vertex covers a unique edge
			    bool uniqueEdge = false;
			    for (char i : adj[u-'a'])
                {
                    int flag = 1;
			        for(char v : maxDegreeVertices)
                    {
                        if(v != u && adj[v-'a'].find(i) != adj[v-'a'].end())
                        {
                            flag = 0;
                            break;
                        }
                    }

                    if(flag == 1)
                    {
                        uniqueEdge = true;
                        break;
                    }
			    }

			    // If the current vertex covers a unique edge, update the chosen vertex
			    if (uniqueEdge)
                {
			        m = u;
			        found = true;
			        break;
			    }
			}

			// If no maximum degree vertex covers a unique edge, choose the first vertex in the list
			if(!found)
            {
			    m = maxDegreeVertices[0];
            }

            // Step 19: Add m to VC
            VC.insert(m);
            cout<<"v:"<<m<<endl;

            // Step 20: Remove edges incident on m
            removeEdgeVertex(E, m);
        }

        return VC;
    }
};

int main()
{
    /*
    map<char,set<char>> mp = {
    {'a', {'b', 'e','f'}},
    {'b', {'a', 'f','c','g'}},
    {'c', {'b','d','g'}},
    {'d', {'c', 'h'}},
    {'e', {'a', 'f','i'}},
    {'f', {'a', 'b','e','g','i','j'}},
    {'g', {'b', 'c','f','h','k','l'}},
    {'h', {'g','d'}},
    {'i', {'e', 'f','j','m'}},
    {'j', {'f', 'i', 'm','n','k'}},
    {'k', {'g', 'j','l','n','o'}},
    {'l', {'g', 'k','p'}},
    {'m', {'i','j','n','q'}},
    {'n', {'j', 'm','r','k','o','s'}},
    {'o', {'k', 'n','s','p'}},
    {'p', {'l', 'o','t'}},
    {'q', {'m', 'r','u','v'}},
    {'r', {'q','n', 's'}},
    {'s', {'r','n','o','t','w','x','y'}},
    {'t', {'p','s', 'y'}},
    {'u', {'q'}},
    {'v', {'q'}},
    {'w', {'s'}},
    {'x', {'s'}},
    {'y', {'s','t'}}
    };
    */

    /*
    map<char,set<char>> mp = {
    {'a', {'f'}},
    {'b', {'e', 'g'}},
    {'c', {'f','d'}},
    {'d', {'e', 'f', 'c'}},
    {'e', {'b', 'f','d'}},
    {'f', {'a', 'c','e', 'd'}},
    {'g', {'b'}}
    };
    */

    /*
    map<char,set<char>> mp = {
    {'a', {'b'}},
    {'b', {'a', 'e'}},
    {'c', {'d'}},
    {'d', {'c', 'e'}},
    {'e', {'d', 'b','f', 'h'}},
    {'f', {'e','g'}},
    {'g', {'f'}},
    {'h', {'i', 'e'}},
    {'i', {'h'}}
    };
    */

   map<char,set<char>> mp = {
    {'a', {'b', 'c'}},
    {'b', {'a', 'd','e','g', 'f'}},
    {'c', {'a', 'h', 'i'}},
    {'d', {'b', 'j'}},
    {'e', {'b', 'k'}},
    {'f', {'b', 'l', 'm', 'n'}},
    {'g', {'b', 'o'}},
    {'h', {'c', 'p'}},
    {'i', {'c', 'q'}},
    {'j', {'d'}},
    {'k', {'e'}},
    {'l', {'f'}},
    {'m', {'f'}},
    {'n', {'f'}},
    {'o', {'g'}},
    {'p', {'h'}},
    {'q', {'i'}}
    };
    
    Graph g(mp.size());

    // Adding edges according to the provided map
    for(auto itr = mp.begin(); itr!=mp.end(); itr++){
        char u = itr->first;
        set<char> uset = itr->second;
        for(auto v:uset){
            g.addEdge(u,v);
        }
    }

    set<char> vertexCover = g.findVertexCover();

    cout<<"Vertex Cover: ";
    for(char v : vertexCover){
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
