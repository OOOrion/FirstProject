#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <set>
#include <chrono>
#define ffor(i, a, b) for(int i = a; i<b; i++)

using namespace std;


int binarySearch(int arr[], int left, int right, int x, bool is_left=false) {
    if(!is_left) {
        while (left < right) {
            int mid = (left + right) / 2;
            if (x < arr[mid]) right = mid;
            else left = mid + 1;
        }
        return left;
    }
    else{
        while (left < right) {
            int mid = (left + right) / 2;
            if (x <= arr[mid]) right = mid;
            else left = mid + 1;
        }
        return left;
    }
}

int ord(char c){
    return (int) c;
}

void print(int list[], int n){
    ffor(i, 0, n) cout<<list[i]<<" ";
    cout<<endl;
}

void print(vector<int> list){
    for(int x: list) cout<<x<<" ";
    cout<<endl;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m)
{
    a = a%m;
    for (int x=1; x<m; x++)
        if ((a*x) % m == 1)
            return x;
}

template<typename K, typename V>
multimap<V,K> sortMap(std::map<K,V> const &map)
{
    std::multimap<V,K> multimap;

    for (auto const &pair: map) {
        multimap.insert(std::make_pair(pair.second, pair.first));
    }

    return multimap;
}

string reverseStr(string str)
{
    string result = str;
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(result[i], result[n - i - 1]);

    return result;
}

int parent[1000001];
int depth[1000001];

void make_set (int v) {
    parent[v] = v;
    depth[v] = 0;
}

int find_set (int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (depth[a] < depth[b])
            swap (a, b);
        parent[b] = a;
        if (depth[a] == depth[b])
            ++depth[a];
    }
}


int tree[32];

void build (int a[], int v, int left, int right) {
    if (left == right)
        tree[v] = a[left];
    else {
        int tm = (left + right) / 2;
        build (a, v*2, left, tm);
        build (a, v*2+1, tm+1, right);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

int sum (int v, int left, int right, int l, int r) {
    if (l > r)
        return 0;
    if (l == left && r == right)
        return tree[v];
    int tm = (left + right) / 2;
    return sum(v * 2, left, tm, l, min(r, tm))
           + sum(v * 2 + 1, tm + 1, right, max(l, tm + 1), r);

}

void update (int v, int left, int right, int pos, int new_val) {
    if (left == right)
        tree[v] = new_val;
    else {
        int tm = (left + right) / 2;
        if (pos <= tm)
            update (v*2, left, tm, pos, new_val);
        else
            update (v*2+1, tm+1, right, pos, new_val);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

void sbuild (int a[], int v, int left, int right) {
    if (left == right)
        tree[v] = a[left];
    else {
        int tm = (left + right) / 2;
        build (a, v*2, left, tm);
        build (a, v*2+1, tm+1, right);
        tree[v] = max(tree[v*2], tree[v*2+1]);
    }
}

int smax (int v, int left, int right, int l, int r) {
    if (l > r)
        return INT8_MAX;
    if (l == left && r == right)
        return tree[v];
    int tm = (left + right) / 2;
    return max(smax(v * 2, left, tm, l, min(r, tm)), smax(v * 2 + 1, tm + 1, right, max(l, tm + 1), r));

}

void supdate (int v, int left, int right, int pos, int new_val) {
    if (left == right)
        tree[v] = new_val;
    else {
        int tm = (left + right) / 2;
        if (pos <= tm)
            update (v*2, left, tm, pos, new_val);
        else
            update (v*2+1, tm+1, right, pos, new_val);
        tree[v] = max(tree[v*2], tree[v*2+1]);
    }
}


void bfs(vector<int> g[], bool used[]){
    queue<int> queue;
    queue.push(1);
    used[1] = true;
    while(!queue.empty()){
        int u = queue.front();
        queue.pop();
        for(size_t i = 0; i<g[u].size(); ++i){
            int u = g[u][i];
            if(!used[u]){
                used[u] = true;
                queue.push(u);
            }
        }
    }
}

int binpow (int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}


int main() {
    auto start = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, t;
    deque<int> dec;
    cin>>n>>t;
    int cl[n];
    int pos = 0;
    int mx = -1;
    ffor(i, 0, n){
        cin>>cl[i];
        if(cl[i]>mx){
            mx = cl[i];
            pos = i;
        }
        dec.push_back(cl[i]);
    }

    pair<int, int> dl[pos+1];

    ffor(i, 1, pos+1){
        int left = dec.front();
        dl[i].first = left;
        dec.pop_front();
        int right = dec.front();
        dl[i].second = right;
        dec.pop_front();

        if(left>right){
            dec.push_front(left);
            dec.push_back(right);
        }
        else{
            dec.push_front(right);
            dec.push_back(left);
        }
    }


    int pl[n-1];
    ffor(i, pos+1, n){
        pl[i-pos-1] = cl[i];
    }
    ffor(i, 0, pos){
        pl[i+n-pos-1] = cl[i];
    }

    long long m;

    ffor(i, 0, t){
        cin>>m;
        if(m<=pos){
            cout<<dl[m].first<<" "<<dl[m].second<<endl;
        }
        else{
            m = m-pos;
            long long k = m%(n-1);
            if(k==0) k = n-1;
            k--;
            cout<<mx<<" "<<pl[k]<<endl;
        }
    }


    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    //cout << "The time: " << elapsed_ms.count() << " ms\n";
    return 0;
}
