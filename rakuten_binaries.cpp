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
 */
 
#include <map>
#include <vector>
#include <iostream>

int solution(std::vector<int> &a) {
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
    
    bool has_changed;
    do {
        has_changed = false;
        
        std::vector<int> must_delete, to_inc;
        for(it = uniq.begin(); it != uniq.end(); it++){
            int key = it->first, value = it->second;
            if(value > 1) {
                it->second = value % 2;
                to_inc.push_back(key + value / 2);
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

    } while(has_changed);
    
    std::cout << "b: [ ";
    for(it = uniq.begin(); it != uniq.end(); it++){
        std::cout << it->first << " ";
    }
    std::cout << "]" << std::endl;

    return (int)uniq.size();
}

int main() {
    std::vector<int> a(8);
    
    a[0]=8;
    a[1]=8;
    a[2]=4;
    a[3]=4;
    a[4]=2;
    a[5]=2;
    a[6]=1;
    a[7]=1;
    
    // finding a binarie
    long int s = 0;
    for (int i=0; i<a.size(); i++) { // (don't look here, I'm lazy...)
        long int t = 1, k = a[i];
        for(int j=0; j<k; j++) t*= 2;
        s += t;
    }
    
    std::cout << "bin(a) = " << s << std::endl;
    
    int r = solution(a);
    
    std::cout << "answer: " << r << std::endl;
    
    return 0;
}
