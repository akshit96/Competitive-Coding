#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void io(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(15);
}

// matrix expo
const int MAXD = 101 ;
long long A[MAXD][MAXD] ;
long long C[MAXD][MAXD] ;
void matMul(long long A[MAXD][MAXD],long long B[MAXD][MAXD],long long res[MAXD][MAXD],int n){
    for(int i = 0 ; i <= n; i++){
        for(int j = 0 ; j <= n ; j++){
            C[i][j] = 0 ;
        }
    }
    for(int i = 1; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            for(int k = 1 ; k <= n ; k++){
                C[i][j] = C[i][j] + (A[i][k]*B[k][j])%MOD ;
                if(C[i][j] >= MOD){
                    C[i][j] -= MOD ;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n ; j++){
            res[i][j] = C[i][j] ;
        }
    }
}
void matExpo(long long A[MAXD][MAXD],long long b,long long res[MAXD][MAXD],int n){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            res[i][j] = (i == j) ;
        }
    }
    while(b){
        if(b&1){
            matMul(res,A,res,n) ;
        }
        matMul(A,A,A,n) ;
        b = b/2ll ;
    }
}
int main(int argc,char* argv[]) { 
    io() ;
    
    return 0 ; 
}