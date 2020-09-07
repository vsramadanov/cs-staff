// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.
// 
// author: Vasilii Ramadanov
// e-mail: finimpres@gmail.com
//
// tested on leetcode.com
// 2020
//

#include <vector>
#include <cmath>

struct int_implementation {
    constexpr static int Zero() { return 0; }
    constexpr static int Invalid() { return std::numeric_limits<int>::min(); }
    static int Op(int a, int b) { return a + b; }
};

template<typename T, typename Impl>
class segment_tree {
        
    const size_t size_;
    std::vector<T> st_;
    
    T build(size_t lo, size_t hi, size_t idx, std::vector<T>& data) {
        if (lo == hi) {
            st_[idx] = data[lo];
            return data[lo];
        }
    
        size_t mid = lo + (hi - lo) / 2;
        st_[idx] = Impl::Op(build(lo, mid, 2*idx + 1, data), 
                            build(mid + 1, hi, 2*idx + 2, data));
        return st_[idx];
    }
    
    T range(size_t l, size_t r, size_t lo, size_t hi, size_t idx) {
        if (r < lo || hi < l) {
            return Impl::Zero();
        }
        
        if (lo == hi) {
            return st_[idx];
        }
        
        if (l == lo && r == hi) {
            return st_[idx];
        }
        size_t mid = lo + (hi - lo)/2;
        return Impl::Op(range(l, r, lo, mid, 2*idx + 1),
                        range(l, r, mid + 1, hi, 2*idx + 2));
    }
    
    T update(size_t lo, size_t hi, size_t idx, size_t target, T value) {
        if (target < lo || hi < target) {
            return st_[idx];
        }
        
        if (lo == hi) {
            st_[idx] = value;
            return value;
        }
        
        size_t mid = lo + (hi - lo)/2;
        st_[idx] = Impl::Op(update(lo, mid, 2*idx + 1, target, value),
                            update(mid + 1, hi, 2*idx + 2, target, value));
        return st_[idx];
    }
    
  public:
    segment_tree(std::vector<T> data) : size_(data.size()) {
        if (size_ == 0)
            return;
        
        const size_t k = ceil(log2(size_));
        st_.resize(pow(2, k + 1) - 1, Impl::Invalid());
        
        build(0, size_ - 1, 0, data);
    }
    
    void update(size_t target, T value) {        
        update(0, size_ - 1, 0, target, value);
    }
    
    T range(int l, int r) {
        return range(l, r, 0, size_ - 1, 0);
    }
};
