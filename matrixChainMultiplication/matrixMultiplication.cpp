#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
typedef int boolean;
class MatrixOrderOptimization{
  int n, *p, **m, **s;
public:
  void read(){
    cin>> n;
    p = new int[n];
    for (int i = 0; i < n; i++)
      cin>>p[i];
  }
  int matrixChainOrder() {
    /* For simplicity of the program, one extra row and one
       extra column are allocated in m[][].  0th row and 0th
       column of m[][] are not used */
   m = new int*[n];
   s = new int*[n];
   for(int i = 0; i < n; ++i){
     s[i] = new int[n];
     m[i] = new int[n];
   }

    int i, j, k, L, q;

    /* m[i,j] = Minimum number of scalar multiplications needed
       to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
       dimension of A[i] is p[i-1] x p[i] */

    // cost is zero when multiplying one matrix.
    for (i=1; i<n; i++)
        m[i][i] = 0;

    // L is chain length.
    for (L=2; L<n; L++)
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]){
                  m[i][j] = q;
                  s[i][j] = k;
                }
            }
    }
    return m[1][n-1];
  }
  void printOptimalParenthesizations() {
        boolean *inAResult = new boolean[n];
        string str = printOptimalParenthesizations(s, 1, n - 1, inAResult, "");
        cout<<str<<endl;
  }
  string printOptimalParenthesizations(int** s, int i, int j, boolean* inAResult, string str) {
        if(i==j)
            return "";
        string str1 = printOptimalParenthesizations(s, i, s[i][j], inAResult, str);
        string str2 = printOptimalParenthesizations(s, s[i][j] + 1, j, inAResult, str);
        // cout<<"str1 : " <<str1<<endl;
        // cout<<"str2 : " <<str2<<endl;
        string istr = inAResult[i] ? "" : std::to_string(i);
        string jstr = inAResult[j] ? "" : std::to_string(j);
        str = "(" + istr + str1 + jstr + str2 + ")";
        // cout<<str<<endl;
        inAResult[i] = 1;
        inAResult[j] = 1;
        return str;
    }
};

int main(int argc, char const *argv[]) {


  MatrixOrderOptimization m;
  m.read();
  cout<<"Minimum number of multiplications is " << m.matrixChainOrder()<<endl;
  m.printOptimalParenthesizations();
  return 0;
}
