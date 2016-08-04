#include <vector>
#include <algorithm>

int solution(std::vector<int> &a) {
    bool has_changed = false;
    do {
        std::sort(a.begin(), a.end());
        
        has_changed = false;
        
        for(int i=0; i<a.size()-1; i++) {
            if(a[i] >= 0) {
                if(a[i] == a[i+1]) {
                    a[i] = -1;
                    a[i+1]++;
                    has_changed = true;
                }
            }
        }
        std::cout << "!";
    } while(has_changed);
    
    int k=0;
    for(int i=0; i<a.size(); i++) {
        if(a[i]>0) k++;
    }
    
    return k;
}
