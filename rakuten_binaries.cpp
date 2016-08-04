/*
 * Company: Rakuten
 * Task title: Binaries
 *
 * int n,  1 <= n <= 10^5
 * vector<int> a, where 0 <= a[i] <= 10^4
 * 
 * binarie(a) = sum pow2(a[i])
 *
 * problem: for given a[] find the shortest vector<int> b, such that binarie(b) == binarie(a)
 * 
 * example: a = [0,0,1,2,0,3,0,1]
 * binarie(a) = 2^0 + 2^0 + 2^1 + 2^2 + 2^0 + 2^3 + 2^0 + 2^1 = 1 + 1 + 2 + 4 + 1 + 8 + 1 + 2 = 20
 * b = [4,2], because binarie(b) = 2^4 + 2^2 = 16 + 4 = 20
 * and there is no shorter answer (following out of binary representation of number 20 = 1100).
 *
 * NOTE: there is 3 solutions: 3 - simpliest, 2 - optimized using a Map, 1 - optimized (and don't uses) Map, but has big (static) memory requirements.
 */
 
#include <vector>
#include <iostream>
#include <map>

#include <stdlib.h>

#define MAXAI 100000*3/2

long int bin(std::vector<int> &a) {
    return 0;
    
//    long int s = 0;
//    for (int i=0; i<a.size(); i++) { // (don't look here, I'm lazy...)
//        long int t = 1, k = a[i];
//        for(int j=0; j<k; j++) t*= 2;
//        s += t;
//    }
//    return s;
}

long int pow2(long int n) {
    int r = 1;
    for (int i=0; i<n; i++) {
        r *= 2;
    }
    return r;
}

std::vector<int> solution1(std::vector<int> &a) {
    int uniq[MAXAI] = {0};
    std::set<int> active_indexes;
    for(int i=0; i<a.size(); i++) {
        uniq[a[i]]++;
        if (uniq[a[i]] == 1) {
            active_indexes.insert(a[i]);
        }
    }
    int it_count = 0, op_count = 0;
    bool has_changed;
    do {
        has_changed = false;
        std::set<int> active_indexes2;
        for(std::set<int>::iterator it=active_indexes.begin(); it!=active_indexes.end(); it++) {
            int i = *it;
            op_count++;
            if(uniq[i]>1) {
                long int x,y,t,z;
                x = uniq[i];
                t = 0;
                while(x >= 2) {
                    x /= 2;
                    t++;
                }
                x = pow2(t);
                y = uniq[i] - x;
                z = t + i;
                uniq[i]= (int)y;
                uniq[z]++;
                has_changed=true;
                
                if (uniq[i]>0) {
                    active_indexes2.insert(i);
                }
                if (uniq[z]>0) {
                    active_indexes2.insert((int)z);
                }
            }
        }
        it_count++;
        active_indexes = active_indexes2;
    } while(has_changed);
    
    int k = 0;
    std::vector<int> b;
    for(int i=0; i<MAXAI; i++){
        if(uniq[i]>0) {
            b.push_back(i);
            k++;
        }
    }
    
    std::cout << "iterations: " << it_count << ", operations count: " << op_count << std::endl;

    return b;
}

std::vector<int> solution2(std::vector<int> &a) {
    std::map<int, int> uniq;
    std::map<int, int>::iterator it;
    
    for(int i=0; i<a.size(); i++) {
        int t = a[i];
        it = uniq.find(t);
        if(it != uniq.end()) {
            it->second++;
        } else {
            uniq[t] = 1;
        }
    }
    
    int it_count = 0, op_count = 0;
    bool has_changed;
    do {
        has_changed = false;
        
        std::vector<int> must_delete, to_inc;
        for(it = uniq.begin(); it != uniq.end(); it++){
            op_count++;
            long int key = it->first, value = it->second;
            if(value > 1) {
                long int x,y,t,z;
                x = value;
                t = 0;
                while(x >= 2) {
                    x /= 2;
                    t++;
                }
                x = pow2(t);
                y = value - x;
                z = key + t;

                it->second = (int)y;
                to_inc.push_back((int)z);
                has_changed = true;
            }
        }
        
        for(int i=0; i<to_inc.size(); i++){
            int z = to_inc[i];
            it = uniq.find(z);
            if(it != uniq.end()) {
                it->second += 1;
            } else {
                uniq[z] = 1;
            }
        }
        
        for(it = uniq.begin(); it != uniq.end(); it++){
            if(it->second == 0) { // mark key for deletion
                must_delete.push_back(it->first);
            }
        }
        for(int i=0; i<must_delete.size(); i++){
            uniq.erase(must_delete[i]);
        }
        it_count++;
    } while(has_changed);
    
    std::vector<int> b;
    for(it = uniq.begin(); it != uniq.end(); it++){
        b.push_back(it->first);
    }
    std::cout << "iterations: " << it_count << ", operations count: " << op_count << std::endl;

    return b;
}

std::vector<int> solution3(std::vector<int> &a) {
    bool has_changed = false;
    for(int i=0; i<a.size(); i++) {
        a[i]++;
    }
    int it_count = 0, op_count = 0;
    do {
        std::sort(a.begin(), a.end());
        
        has_changed = false;
        
        for(int i=0; i<a.size()-1; i++) {
            op_count++;
            if(a[i] > 0) {
                if(a[i] == a[i+1]) {
                    a[i] = 0;
                    a[i+1]++;
                    has_changed = true;
                }
            }
        }
        it_count++;
    } while(has_changed);
    

    int k=0;
    std::vector<int> b;
    for(int i=0; i<a.size(); i++) {
        if(a[i]>0) {
            b.push_back(a[i]-1);
            k++;
        }
    }

    std::cout << "iterations: " << it_count << ", operations count: " << op_count << std::endl;

    return b;
}

int main() {
    int n = 100000;
    std::vector<int> a(n);
    clock_t t;

    srand((unsigned int)time(NULL));
    for (int i=0; i<n; i++) {
        a[i] = rand() % 10000;
    }
    long int bina = bin(a);
    std::cout << "bin(a) = " << bina << std::endl;
    std::vector<int> b1, b2, b3;
    
    t = clock();
    b1 = solution1(a);
    t = clock() - t;
    std::cout << "s1 time: " << t << std::endl;
    
    t = clock();
    b2 = solution2(a);
    t = clock() - t;
    std::cout << "s2 time: " << t << std::endl;
    
    t = clock();
    b3 = solution3(a);
    t = clock() - t;
    std::cout << "s3 time: " << t << std::endl;

    std::cout << "s1: " << b1.size() << std::endl;
    std::cout << "s2: " << b2.size() << std::endl;
    std::cout << "s3: " << b3.size() << std::endl;

    if (bin(b1) != bina) {
        std::cout << "s1 incorrect" << std::endl;
    }
    if (bin(b2) != bina) {
        std::cout << "s2 incorrect" << std::endl;
    }
    if (bin(b3) != bina) {
        std::cout << "s3 incorrect" << std::endl;
    }
    
    return 0;
}

/* 
std::cout:
```
iterations: 13, operations count: 31196
s1 time: 23577
iterations: 17, operations count: 102447
s2 time: 46898
iterations: 7, operations count: 699993
s3 time: 11973
s1: 4931
s2: 4931
s3: 4931
```
*/
