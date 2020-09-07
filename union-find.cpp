// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.
// 
// author: Vasilii Ramadanov
// e-mail: finimpres@gmail.com
//
// tested on leetcode.com
// 2020
//

class union_find {

    std::vector<int> id;
    std::vector<int> sz;

    int root(int n) {
        while (n != id[n]) {
			// id[n] = id[id[n]]; // path compression
            n = id[n];
		}
        return n;
    }

  public:    
    void make_union(int n, int m) {
        int root_n = root(n);
        int root_m = root(m);
        if (root_n == root_m)
            return;
            
        if (sz[root_n] > sz[root_m]) {
            id[root_m] = root_n;
            sz[root_n] += sz[root_m];
        } else {
            id[root_n] = root_m;
            sz[root_m] += sz[root_n];
        }
    }
    
    bool connected(int n, int m) {
        return root(n) == root(m);
    }
    
    void reset(size_t capasity) {
		id.resize(capasity);
		sz.resize(capasity);
        for (int k = 0; k < capasity; k++) {
            id[k] = k;
            sz[k] = 1;
        }
    }
};
