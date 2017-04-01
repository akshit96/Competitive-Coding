#include <bits/stdc++.h>
 
using namespace std;

// ukonnen's algorithm for suffix trees.

// awesome explaination at http://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english/9513423#9513423

// time / space compexity O(n)

/* some properties 
The tree has exactly n leaves numbered from 1 to n.
Except for the root, every internal node has at least two children.
Each edge is labeled with a non-empty substring of S.
No two edges starting out of a node can have string-labels beginning with the same character.
The string obtained by concatenating all the string-labels found on the path from the root to leaf i spells out suffix S[i..n], for i from 1 to n.
*/
/*  
    note:
    1.It's advisable (not mandatory) to append '$' at the end of string, if you're working on string in a offline way.
    2. Although the above step should not be done if the string is dynamic.
    3. if len[i] is large (> s.size()) => the node runs down from fipos[i] to end of string.
    4. nodes of interest [1,sz-1].
    5. suffix links : in general link to largest suffix of the string under consideration , which is present in the tree. In suffix tree that becomes the suffix that is one character shorter.
    6. suffix link of root points to root itself. 

    ** if you are dealing with dynamic strings..(not appending '$' at end) **
    1. the last remain (remainder) suffixes will not have leaves in the suffix tree
*/
// suffix tree implementation taken from http://ideone.com/sT8Vd1

const int inf = 1e9;
const int maxn = 4*1e5 + 5; // 4 times length taken to account for constant factor in space complexity.
char s[maxn];
unordered_map<int, int> to[maxn];
int len[maxn], fipos[maxn], link[maxn]; // fipos = idx of first pos from current node,len = length of suffix from fipos , link = suffix link
// len for leaf nodes as inf

int node, pos; // node = active node , pos = active length
int sz = 1, n = 0;
int remain = 0 ; // remainder

int make_node(int _pos, int _len){
    fipos[sz] = _pos;
    len [sz] = _len;
    return sz++;
}
 
void go_edge(){
    while(pos > len[to[node][s[n - pos]]]){
        node = to[node][s[n - pos]];
        pos -= len[node];
    }
}
 
void add_letter(int c){
    s[n++] = c;
    pos++;
    int last = 0;
    remain++ ;

    while(pos > 0){ // 1.If pos = 0, then all suffixes are added. Return. 
        go_edge();//find the vertex after which new suffix will be added (it is not neccessarily node because edge from node may be too short)
        int edge = s[n - pos];
        int &v = to[node][edge];
        int t = s[fipos[v] + pos - 1];
        if(v == 0){ // If we do not have needed outgoing edges at this node, we simply create a new vertex and hung it to the current one.
            remain-- ;
            v = make_node(n - pos, inf);
            link[last] = node;
            last = 0;
        }
        else if(t == c){//If there is an edge and a suffix that we want to add lies entirely on it then this and further suffixes are not unique. Return.
            link[last] = node;
            return;
        }
        else{//If there is an edge and suffix doesn't lie entirely on it then it differs in only one character(latest one), this means that we need to create a new vertex in the middle of the edge and then create another one new vertex (which will be new suffix) and hung it to the vertex in the middle of splitted edge
            remain-- ;
            int u = make_node(fipos[v], pos - 1);
            to[u][c] = make_node(n - 1, inf);
            to[u][t] = v;
            fipos[v] += pos - 1;
            len [v] -= pos - 1;
            v = u;
            link[last] = u;
            last = u;
        }
        /*
            If you have not returned on the previous step, go to the next suffix. If node is root, then we reduce the pos with 1, otherwise we just follow the suffix link node = link(node) without changing pos. After that, we go to step 1.
        */
        if(node == 0)
            pos--;
        else
            node = link[node];
    }
}
 
int main(){
    freopen("inp.txt" , "r" , stdin) ;
    len[0] = inf;
    string str;
    cin >> str;
    // str += '$' ;
    int ans = 0;
    for(int i = 0; i < str.size(); i++){
        add_letter(str[i]);
        cout << "@@ rem = " << remain << endl ;
    }
    cout << "## sz = " << sz << endl ;
    for(int i = 1 ; i < sz ; i++){
        cout << fipos[i] << " , " << len[i] << endl ;
    }

    for(int i = 1; i < sz; i++)
        ans += min((int)str.size() - fipos[i], len[i]);
    cout << ans << "\n";
    return 0 ;
}