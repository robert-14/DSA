#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <string>
#define INT_MAX 2147483647
using namespace std;
typedef struct Data{
	int user;
	int item;
	int time;
	int result;
}Data;
vector<Data> v_user,v_item;
vector<int> Us;
int n_data;
bool compare_int (const int a,const int b){
	return a < b; 
}
bool compare_by_user(const Data a,const Data b){
	if(a.user != b.user){
		return a.user < b.user;
	}
	else if(a.item != b.item){
		return a.item < b.item;
	}
	else if(a.time != b.time){
		return a.time < b.time;
	}
	else if(a.result != b.result){
		return a.result < b.result;
	}
}
bool compare_by_item(const Data a,const Data b){
	if(a.item != b.item){
		return a.item < b.item;
	}
	else if(a.user != b.user){
		return a.user < b.user;
	}
	else if(a.time != b.time){
		return a.time < b.time;
	}
	else if(a.result != b.result){
		return a.result < b.result;
	}
}
void accept(int user,int item,int time){
	vector<Data>::iterator low;
	Data standard = {user,item,time,-2};
	low = lower_bound(v_user.begin(),v_user.end(),standard,compare_by_user);
	if(low->user == user && low->item == item && low->time == time && low != v_user.end()){	
		cout<<low->result<<endl;
	}
	else{
		cout<<"0"<<endl;
	} 
}
void items(int u1,int u2){
	vector<Data>::iterator low1,low2,up1,up2;
	Data standard_low1 = {u1,-2,-2,-2};
	Data standard_up1 = {u1,INT_MAX,INT_MAX,INT_MAX};
	Data standard_low2 = {u2,-2,-2,-2};
	Data standard_up2 = {u2,INT_MAX,INT_MAX,INT_MAX};
	low1 = lower_bound(v_user.begin(),v_user.end(),standard_low1,compare_by_user);
	up1 = upper_bound(v_user.begin(),v_user.end(),standard_up1,compare_by_user);	
	low2 = lower_bound(v_user.begin(),v_user.end(),standard_low2,compare_by_user);
	up2 = upper_bound(v_user.begin(),v_user.end(),standard_up2,compare_by_user);
	int pre = -1;
	vector<int> item; 
	while(low1 != up1  && low2 != up2 ){
		if(low1->item == low2->item){
			if(low1->item == pre){
				low1++;
				low2++;
			}
			else {
				item.push_back(low1->item);
				pre = low1->item;
				low1++;
				low2++;
			}
		}
		else {
			if(low1->item < low2->item){
				low1++;
(		}
			else{
				low2++;
			}
		}
	}
	for(int i = 0;i < item.size();i++){
		cout<<item[i]<<endl;
	}
}
void users(int i1,int i2,int t1,int t2){
	vector<Data>::iterator low1,low2,up1,up2;
	Data standard_low1 = {-2,i1,-2,-2};
	Data standard_up1 = {INT_MAX,i1,INT_MAX,INT_MAX};
	Data standard_low2 = {-2,i2,-2,-2};
	Data standard_up2 = {INT_MAX,i2,INT_MAX,INT_MAX};
	low1 = lower_bound(v_item.begin(),v_item.end(),standard_low1,compare_by_item);
	up1 = upper_bound(v_item.begin(),v_item.end(),standard_up1,compare_by_item);	
	low2 = lower_bound(v_item.begin(),v_item.end(),standard_low2,compare_by_item);
	up2 = upper_bound(v_item.begin(),v_item.end(),standard_up2,compare_by_item);
	int pre = -1;
	vector<int> user; 
	while(low1 != up1  && low2 != up2 ){
		if( low1->user == low2->user && low1->time >= t1 && low1->time <= t2 && low2->time >= t1 && low2->time <= t2){
			if(low1->user == pre){
				low1++;
				low2++;
			}
			else {
				user.push_back(low1->user);
				pre = low1->user;
				low1++;
				low2++;
			}
		}
		else {
			if(low1->user < low2->user){
				low1++;
			}
			else{
				low2++;
			}
		}
	}
	for(int i = 0;i < user.size();i++){
		cout<<user[i]<<endl;
	}
}
void ratio(int item,int threshold){
	int n = 0;//count the number of being recommended
	int pre = -1;// check the same user
	int total = 0;
	int accept = 0;
	int flag = 0;	
	int size = v_user.size();
	/*if( v_user[0].item == item && v_user[0].result == 1) {
		flag = 1;
	}*/
	for(int i = 0;i < size;i++){
		if( v_user[i].user != pre){
			if(n > threshold){
				total++;
				if(flag){
					accept++;
				}
			}
			n = 1;
			flag = 0;
			pre = v_user[i].user;
		}
		else {
			n++;
		}
		if( v_user[i].item == item && v_user[i].result == 1) {
			flag = 1;
		}
		if(i == size - 1){
			if(n > threshold){
				total++;
				if(flag){
					accept++;
				}
			}
		}
	}
	printf("%d/%d\n",accept,total);
}
void findtime_items(int item){
	vector<Data>::iterator low,up;
	Data lower_standard = {-2,item,-2,-2};
	Data up_standard = {INT_MAX,item,INT_MAX,INT_MAX};	
	low = lower_bound(v_item.begin(),v_item.end(),lower_standard,compare_by_item);
	up = upper_bound(v_item.begin(),v_item.end(),up_standard,compare_by_item);
	int size = Us.size();
	int i = 0;
	vector<int> time;
	while( i != size && low != up){
		if( Us[i] == low->user ){
			time.push_back(low->time);
			i++;
			low++;	
		}	
		else if( Us[i] > low->user ){
			low++;	
		}
		else if( Us[i] < low->user ){
			i++;
		}
	}
	sort(time.begin(),time.end(),compare_int);
	int size_time = time.size();
	int pre = -1;
	for(int j = 0;j < size_time;j++){
		if( time[j] != pre){
			pre = time[j];
		}
		else {
			time.erase(time.begin() + j);
		}
	}
	for(int j = 0;j < size_time;j++){
		printf("%d\n",time[j]);
	}
}
int main(){
	FILE *fp;
	fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","r");
	assert(fp != NULL);
	Data temp;
	while( fscanf(fp,"%d %d %d %d",&temp.user,&temp.item,&temp.result,&temp.time) != EOF){   //question
		v_user.push_back(temp);
		v_item.push_back(temp);
		n_data++;
	}		
	fclose(fp);
	sort(v_user.begin(),v_user.end() ,compare_by_user);
	sort(v_item.begin(),v_item.end(),compare_by_item);
	int size = v_user.size();
	Data pre = {-1,-1,-1,-1};
	for(int i = 0;i < size;i++){
		if( v_user[i].user == pre.user && v_user[i].item == pre.item && v_user[i].time == pre.time && v_user[i].result == pre.result){
			v_user.erase( v_user.begin() + i );
		}
		else{
			pre = v_user[i];
		}
	}
	pre.user = -1;
	pre.item = -1;
	pre.time = -1;
	pre.result = -1;
	for(int i = 0;i < size;i++){
		if( v_item[i].user == pre.user && v_item[i].item == pre.item && v_item[i].time == pre.time && v_item[i].result == pre.result){
			v_item.erase( v_item.begin() + i );
		}
		else{
			pre = v_item[i];
		}
	}
	int n;	
	cin>>n;
	for(int i = 0;i < n;i++){
		string command;
		cin>>command;
		if(command == "accept" ){ // question
			int u,i,t;
			accept(u,i,t);		
		}
		if(command == "items"){
			int u1,u2;
			items(u1,u2);
		}
		if(command == "users"){
			int i1,i2,t1,t2;
			users(i1,i2,t1,t2);
		}
		if(command == "ratio"){
			int i,threshold;
			ratio(i,threshold);
		}
		if(command == "findtime_item"){
			int i,temp;
			char ch;
			//vector<int> Us;
			scanf("%d",&i);
			while( scanf("%d%c",&temp,&ch) ){
				Us.push_back(temp);
				if( ch == '\n') break;
			}	
			sort(Us.begin(),Us.end(),compare_int);
			findtime_items(i);
			Us.erase( Us.begin(),Us.end() );
		}
	}	
	return 0;	
}
