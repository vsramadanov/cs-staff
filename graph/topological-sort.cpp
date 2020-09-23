class topological_sort {
    vector<vector<int>> adj;
    vector<bool> marked;
    vector<bool> on_stack;
    std::stack<int> seq;
    bool has_cycle_ = false;
    
    bool dfs(int v) {
        marked[v] = true;
        
        if (has_cycle_)
            return false;
        
        on_stack[v] = true;
        for (int n : adj[v]) {
            if (on_stack[n]) {
                has_cycle_ = true;
                return false;
            }
            if (!marked[n])
                if(!dfs(n))
                    return false;
        }
        on_stack[v] = false;
        
        seq.push(v);
        return true;
    }
    
  public:
    topological_sort(int v_max, const vector<vector<int>>& edges) {
        adj.resize(v_max);
        marked.resize(v_max, false);
        on_stack.resize(v_max, false);
        
        for (const auto& edge : edges)
            adj[edge[1]].push_back(edge[0]);
        
        for (int v = 0; v < v_max; v++)
            if (!marked[v]) dfs(v);
    }
    
    bool has_cycle() { return has_cycle_; }
    std::stack<int>& result() { return seq; }
};
