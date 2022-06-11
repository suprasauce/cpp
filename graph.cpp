class graph{
    public:
        vector<vector<int>>adj;
        graph(int n){
            adj.resize(n);
        }
        void addEdge(int u, int v){
            // given the graph is undirected
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        void bfs(){
            queue<int>q;
            vector<bool>visited(adj.size(),false);
            visited[0] = true; // given that root is 0
            q.push(0);
            while(!q.empty()){
                int curr = q.front();
                //cout << curr + 1 << "\n";
                q.pop();
                for(auto i:adj[curr]){
                    if(!visited[i]){
                        q.push(i);
                        visited[i] = true;
                    }
                }
            }
        }

        void dfs(int root,vector<bool>&visited){
            visited[root] = true;
            for(auto i:adj[root]){
                if(!visited[i]){
                    dfs(i,visited);
                }
            }
            //cout << root+1 << "\n";
        }

};