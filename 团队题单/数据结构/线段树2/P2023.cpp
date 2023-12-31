#include <bits/stdc++.h>
#define int long long
using namespace std;
#define lson (id << 1)
#define rson (id << 1 | 1)
const int maxn = 1e5 + 5;
struct Node{
    int left, right;
    int sum, lc, la;
};
Node t[maxn << 2];
int a[maxn];
int n, m, p;
int len(int id){
    return t[id].right - t[id].left + 1;
}
void pushdown(int id){
    t[lson].sum = t[lson].sum * t[id].lc + (t[id].la * len(lson)); t[lson].sum %= p;
    t[rson].sum = t[rson].sum * t[id].lc + (t[id].la * len(rson)); t[rson].sum %= p;
    t[lson].lc *= t[id].lc; t[lson].lc %= p;
    t[rson].lc *= t[id].lc; t[rson].lc %= p;
    t[lson].la = (t[lson].la * t[id].lc % p + t[id].la); t[lson].lc %= p;
    t[rson].la = (t[rson].la * t[id].lc % p + t[id].la); t[rson].lc %= p;
    t[id].lc = 1; t[id].la = 0;
}
void buildtree(int id, int L, int R){
    t[id].left = L, t[id].right = R, t[id].lc = 1, t[id].la = 0;
    if (L == R){
        t[id].sum = a[L];
    }
    else{
        int mid = (L + R) >> 1;
        buildtree(id << 1, L, mid);
        buildtree(id << 1 | 1, mid + 1, R);
        t[id].sum = t[id << 1].sum + t[id << 1 | 1].sum;
    }
    t[id].sum %= p;
}
void changemul(int id, int L, int R, int val){
    if (t[id].right < L || t[id].left > R) return;
    if (t[id].left >= L && t[id].right <= R){
        t[id].sum *= val; t[id].sum %= p;
        t[id].la *= val; t[id].la %= p;
        t[id].lc *= val; t[id].lc %= p;
        return;
    }
    pushdown(id);
    changemul(lson, L, R, val);
    changemul(rson, L, R, val);
    t[id].sum = (t[lson].sum + t[rson].sum) % p;
}
void changeadd(int id, int L, int R, int val){
    if (t[id].right < L || t[id].left > R) return;
    if (t[id].left >= L && t[id].right <= R){
        t[id].la += val; t[id].la %= p;
        t[id].sum += val * len(id); t[id].sum %= p;
        return;
    }
    pushdown(id);
    changeadd(lson, L, R, val);
    changeadd(rson, L, R, val);
    t[id].sum = (t[lson].sum + t[rson].sum) % p;
}
int query(int id, int L, int R){
    if (t[id].right < L || t[id].left > R) return 0;
    if (t[id].left >= L && t[id].right <= R) return t[id].sum;
    pushdown(id);
    return (query(lson, L, R) + query(rson, L, R)) % p;
}
signed main(){
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int x, y, z, k;
    buildtree(1, 1, n);
    cin >> m;
    while(m--){
        cin >> x;
        cin >> y >> z;
        if (x == 1){
            cin >> k;
            changemul(1, y, z, k);
        }
        else if (x == 2){
            cin >> k;
            changeadd(1, y, z, k);
        }
        else{
           cout << query(1, y, z) << endl;
        };
    }
    // system("Pause");
    return 0;
}