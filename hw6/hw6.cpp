#include <stdio.h>
#include <vector>
using namespace std;
vector<float> pitch,note;
vector<int> answer;
float Dp_table[1000][100];
float abs(float num){
	if( num >= 0) return num;
	else return -num;
}
void Dp(int  a,int  b){
	if(a<0 || b< 0) printf("fuxk");
	if( a == 0 && b == 0){
		Dp_table[a][b] = abs(pitch[a] - note[b]);
	}
	else if( a == b ){
		if(!Dp_table[a-1][b-1]){
			Dp(a-1,b-1);
			Dp_table[a][b] = abs(pitch[a] - note[b]) + Dp_table[a-1][b-1];
		}
		else{
			Dp_table[a][b] = abs(pitch[a] - note[b]) + Dp_table[a-1][b-1];
		}
	}
	else if(!b){
		if(!Dp_table[a-1][b]){
			Dp(a-1,b);
			Dp_table[a][b] = abs(pitch[a] - note[b]) +Dp_table[a-1][b];
		}
		else{
			Dp_table[a][b] = abs(pitch[a] - note[b]) +Dp_table[a-1][b];
		}
	}
	else{
		if(!Dp_table[a-1][b]){
			Dp(a-1,b);
		}
		if(!Dp_table[a-1][b-1]){
			Dp(a-1,b-1);
		}
		if(Dp_table[a-1][b] < Dp_table[a-1][b-1]){
			Dp_table[a][b] = abs(pitch[a] - note[b]) +Dp_table[a-1][b];
		}
		else{
			Dp_table[a][b] = abs(pitch[a] - note[b]) +Dp_table[a-1][b-1];
		}
	}
}
int main(){
	int m,n;
	scanf("%d",&m);
	float temp;
	for(int i = 0;i < m;i++){
		scanf("%f",&temp);
		pitch.push_back(temp);
	}
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		scanf("%f",&temp);
		note.push_back(temp);	
	}
	for(int i = 0;i < n;i++){
		Dp(m-1,i);
	}
	float min = 0;
	int num;	
	for(int i = 0;i < n;i++){
		if(!i){
			min = Dp_table[m-1][i];
			num = i;
			continue;
		}
		if(Dp_table[m-1][i] < min){
			min = Dp_table[m-1][i];
			num = i;
		}
	}
	int a = m-1,b = num;
	while( a != 0){
		if(a == b){
			for(int i = a;i >= 1;i--){
					answer.push_back(i);
			}
			break;
		}
		if(!b){
			break;
		}
		if(Dp_table[a-1][b] < Dp_table[a-1][b-1]){
			a--;
		}
		else{
			answer.push_back(a);
			a--;
			b--;
		}
	}
	printf("%f\n",min);
	printf("0 ");
	for(int i = answer.size() -1;i >= 0;i--){
		if(!i){
			printf("%d\n",answer[i]);	
		}	
		else{
			printf("%d ",answer[i]);
		}
	}
	return 0;
}
