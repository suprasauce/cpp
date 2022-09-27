class BIT{
    vector<ll>tree;
    vector<ll>org;
    ll get_lastbit_pos(ll num){
        return log2((num&(-num)));
    }
    void create_tree(){
        tree[0] = 0;
        for(ll i = 1;i<tree.size();++i){
            ll low = i - (1 << get_lastbit_pos(i)) + 1;
            tree[i] = org[i-1] + get_sum(i-1) - get_sum(low-1); 
        }
    }
    public:
    BIT(vector<ll>&v){
        org = v;
        tree.resize(v.size()+1);
        create_tree();
    }
    ll get_sum(ll i){
        ll sum = 0;
        while(i > 0){
            sum += tree[i];
            i -= (i&(-i));
        }
        return sum;
    }
    void update(ll i, ll num){
        ll val = num - org[i-1];
        org[i-1] += val;
        while(i <= org.size()){
            tree[i] += val;
            i += (i&(-i));
        }
    }
};
