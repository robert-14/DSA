#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
vector<int>  r_data[30],c_data[30],temp_r[30],temp_c[30],r_left[30],c_left[30];
int map[32][32] = {{0}},m,n;
int build(int p,int temp){
	int r = p/n + 1,c = p%n + 1;
	printf("p = %d r = %d c = %d temp = %d\n ",p,r,c,temp);
	if( temp ){
		if( map[r-1][c] ){
			temp_c[c - 1][temp_c[c - 1].size() - 1]++;
		}
		else{
			temp_c[c - 1].push_back(1);
		}
		if( map[r][c-1] ){
			temp_r[r - 1][temp_r[r - 1].size() - 1]++;
		}
		else{
			temp_r[r - 1].push_back(1);
		}
		map[r][c] = 1;
	}
	else {
		map[r][c] = 0;
	}
	int flag = 0;
	int r_size = temp_r[r - 1].size(),c_size = temp_c[c - 1].size();
	if(r_size > 0){
		if( (temp_r[r - 1][r_size - 1] > r_data[r - 1][r_size - 1] ) || (r_size > r_data[r - 1].size()) ){
			printf("get out 1\n");
			flag = 1;
		}	
	}
	if(c_size > 0){
		if( (temp_c[c - 1][c_size - 1] > c_data[c - 1][c_size - 1]) || (c_size > c_data[c - 1].size() )){
			flag = 1;
			printf("get out1\n");
		}
	}
	if(c == n){						//check when it comes to the last element in the row 
		if(temp_r[r-1].size() != r_data[r-1].size()){
			flag = 1;
			printf("r_end get out\n");
		}
		int flag1 = 0;
		for(int i = 0;i < r_size;i++){
			if( temp_r[r-1][i] != r_data[r-1][i] ){
				flag1 = 1;
				printf("r_end get out\n");
				break;
			}	
		}
		if(flag1){
			flag = 1;
		}
	}
	if(r == m){
		if(temp_c[c-1].size() != c_data[c-1].size()){
			flag = 1;
			printf("c_end get out\n");
		}
		int flag2 = 0;
		for(int i = 0;i < c_size;i++){
			if( temp_c[c-1][i] != c_data[c-1][i] ){
				flag2 = 1;
				printf("c_end get out\n");
				break;
			}	
		}
		if(flag2){
			flag = 1;
		}
	}
	if( temp ){	
		//printf("r_size = %d\n",r_size );
		//printf("c_size  = %d\n",c_size );
		if( r_size < r_data[r - 1].size() ){
			if( (n - c) < ( r_left[r - 1][r_size] ) ){
				flag = 1;
				printf("get out3 : not enough\n");
			}
		}	
		if(c_size < c_data[c - 1].size() ){
			if( (m - r) < ( c_left[c - 1][c_size] ) ){
				flag = 1;
				printf("get out 3: not enough\n");
			}
		}	
	}
	else {
		if( r_size < r_data[r-1].size() ){
			if( (n - c) < r_left[r - 1][r_size] ){	
				flag = 1;
				printf("get out 4\n");
			}
		}	
		if( c_size < c_data[c-1].size() ){
			if( (m - r) < ( c_left[c - 1][c_size]) ){		
				flag = 1;
				printf("get out 4\n");
			}
		}	
	}
	if(flag){
		if(temp){
			if( temp_r[r - 1][r_size - 1] > 1){
				temp_r[r - 1][r_size - 1]--;
			}
			else{
				temp_r[r - 1].erase( temp_r[r - 1].end() - 1);
			}	
			if( temp_c[c - 1][c_size - 1] > 1){
				temp_c[c - 1][c_size - 1]--;
			}
			else{
				temp_c[c - 1].erase( temp_c[c - 1].end() - 1);
			}
			map[r][c] = 0;
			return 0;	
		}
		else{
			return 0;
		}	
	}
	if(p == m*n - 1){
		return 1;
	}
	if( build(p+1,1) ){
		return 1;
	}
	else if( build(p+1,0) ){
		return 1;
	}
	else { 
		if(temp){
			if( temp_r[r - 1][r_size - 1] > 1){
				temp_r[r - 1][r_size - 1]--;
			}
			else{
				temp_r[r - 1].erase( temp_r[r - 1].end() - 1);
			}
			if( temp_c[c - 1][c_size - 1] > 1){
				temp_c[c - 1][c_size - 1]--;
			}
			else{
				temp_c[c - 1].erase( temp_c[c - 1].end() - 1);
			}
			map[r][c] = 0;
			return 0;
		}	
		else{	
			return 0;
		}
	}
}

int main(){
	cin>>m>>n;
	printf("\nanswer: \n");
	for(int i = 0;i < m;i++){
		int temp;
		char c;	
		while( scanf("%d%c",&temp,&c) ){
			r_data[i].push_back(temp);
			if( c == '\n' ) break;
		}
	}
	for(int i = 0;i < n;i++){
		int temp;
		char c;
		while( scanf("%d%c",&temp,&c) ){
			c_data[i].push_back(temp);
			if( c == '\n' ) break;
		}
	}
	for(int i = 0;i < m;i++){
		int size = r_data[i].size();
		for(int j = 0;j < size;j++){
			int temp = size - 1 - j;
			for(int k = j;k < size;k++){
				temp += r_data[i][k];
			}
			r_left[i].push_back(temp);
		}
	}
	for(int i = 0;i < n;i++){
		int size = c_data[i].size();
		for(int j = 0;j < size;j++){
			int temp = size - 1 - j;
			for(int k = j;k < size;k++){
				temp += c_data[i][k];
			}
			c_left[i].push_back(temp);
		}
	}
	
	if( build(0,1) ){
		for(int i = 1;i <= m;i++){
			for(int j = 1;j <= n;j++){
				if(map[i][j]) printf("#");
				else printf(".");	
				if(j == n) printf("\n");
			}
		}
		
	}
	else if( build(0,0) ){
		for(int i = 1;i <= m;i++){
			for(int j = 1;j <= n;j++){
				if(map[i][j]) printf("#");
				else printf(".");	
				if(j == n) printf("\n");
			}
		}
		
	}	
	else{
		printf("cowbe");
	}
	return 0;	
}
