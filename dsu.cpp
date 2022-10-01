class dsu{
    vector<int>parent, size;
    public:
    dsu(int n){
        parent.resize(n);
        size.resize(n);
    }
    void make(int x){
        parent[x] = x;
        size[x] = 1;
    }
    int find(int x){
        // path compression
        if(x == parent[x]) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }
    void Union(int x, int y){
        int p_x = find(x);
        int p_y = find(y);
        if(size[p_x] < size[p_y]) swap(p_x, p_y);
        // p_x will always be the greator sized tree, thus union by size
        parent[p_y] = p_x;
        size[p_x] += size[p_y];  
    }
};
