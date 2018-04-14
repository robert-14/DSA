#include<cstdlib>
#include<iostream>
using namespace std;
void swap(int matrix_size,double *A,double *B){
	double temp;
	for(int i = 0;i < matrix_size;i++){
		temp = A[i];
		A[i] = B[i];
		B[i] = temp;		
	}
}
double ab_value(double a){
	if(a >= 0) return a;
	else return -a;	
}
int main (){
	double A[300][300],inverse[300][300] = {{0}},A_copy[300][300],result[300][300];
	double error;
	int n;
	cin>>n;
	for(int i = 0;i < n;i++){
		inverse[i][i] = 1;
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin>>A[i][j];	
		}
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			A_copy[i][j] = A[i][j];
		}
	}
	for(int i = 0;i < n;i++) {//choose the main row to do operation
		if(!A[i][i]){//to avoid the situation that the main col in main row is 0
			int num;
			for(num = i+1;num < n;num++){
				if(A[num][i]) break;
			}
			swap(n,A[i],A[num]);
			swap(n,inverse[i],inverse[num]);
		}
		for(int j = i + 1;j < n;j++){//to operate gauss elimination
			double mul = A[j][i]/A[i][i];
            for(int k = 0;k < n;k++){
                A[j][k] -= A[i][k]*mul;
                inverse[j][k] -= inverse[i][k]*mul;
            }
		}
	}
	for(int i = n-1;i > 0;i--){
		for(int j = i-1;j >= 0;j--){
			double mul = A[j][i]/A[i][i];	
			for(int k = 0;k < n;k++){
				A[j][k] -= A[i][k]*mul;	
				inverse[j][k] -= inverse[i][k]*mul;
			}
		}
		
	}	
	for(int i = 0;i < n;i++){
		double mul = A[i][i];
		A[i][i] /= mul;
		for(int j = 0;j < n;j++){
			inverse[i][j] /= mul;	
		}
	}	
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			for(int k = 0;k < n;k++){
				result[i][j] += A_copy[i][k]*inverse[k][j];
			}	
		}
	}
	for(int i = 0;i < n;i++){
		result[i][i] -= 1;
	}
	error = ab_value(result[0][0]);
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if( ab_value(result[i][j]) > error){
				error = ab_value(result[i][j]);
			}
		}
	}
	cout<<error<<"\n";
	for(int i = 0;i < n;i++){                         
		for(int j = 0;j < n;j++){
			if(j == n-1) cout<<inverse[i][j]<<endl;
			else cout<<inverse[i][j]<<" ";
		}
	}
	return 0;
}
