#include <stdio.h> 
#include <vector>
#include <string>
#include <assert.h>
#include <functional>
#include<string.h>
 
using namespace std; 

vector<string> hashtable[10037];
hash<string> hash_str;
vector<string> ed1;
vector<string> possible;
vector<string> answer;	
void Insert(string str,int depth){
	int length = str.length();
	if(!depth){
		for(int i = 0;i < 26;i++){
			for(int j = 0;j < length;j++){
				string str1 = str;
				str1.insert(str1.begin() + j,'a' + i);	
				ed1.push_back(str1);
			}
			string str1 = str;
			str1.push_back('a' + i);
			ed1.push_back(str1);
		}	
	}
	else{
		for(int i = 0;i < 26;i++){
			for(int j = 0;j < length;j++){
				string str1 = str;
				str1.insert(str1.begin() + j,'a' + i);	
				possible.push_back(str1);
			}
			string str1 = str;
			str1.push_back('a' + i);
			possible.push_back(str1);
		}	
	}	
	
}

void Delete(string str,int depth){
	int length = str.length();
	if(!depth){
		for(int i = 0;i < length;i++){
			string str1 = str;
			str1.erase(str1.begin() + i);
			ed1.push_back(str1);
		}	
	}
	else{
		for(int i = 0;i < length;i++){
			string str1 = str;
			str1.erase(str1.begin() + i);
			possible.push_back(str1);
		}
	}
}
void Subtitute(string str,int depth){
	int length = str.length();
	if(!depth){
		for(int i = 0;i < length;i++){
			for(int j = 0;j < 26;j++){
				string str1 = str;
				str1.replace(i,1,'a' + j);
				ed1.push_back(str1);	
			}
		}
	}
	else{
		for(int i = 0;i < length;i++){
			for(int j = 0;j < 26;j++){
				string str1 = str;
				str1.replace(i,1,'a' + j);
				possible.push_back(str1);	
			}
		}
	}
}
void Transpose(string str,int depth){
	int length = str.length();
	if(!depth){
		for(int i = 0;i < length - 1;i++){
			string str1 = str;
			char temp = str1[i+1];
			str1[i+1] = str1[i];
			str1[i] = temp;
			ed1.push_back(str1);	
		}
		
	}
	else{
		for(int i = 0;i < length - 1;i++){
			string str1 = str;
			char temp = str1[i+1];
			str1[i+1] = str1[i];
			str1[i] = temp;
			possible.push_back(str1);	
		}
		
	}
}	
void check(string str){
	Insert(str,0);
	Delete(str,0);
	Subtitute(str,0);
	Transpose(str,0);
	int size = ed1.size();
	for(int i = 0;i < size;i++){
		int key = hash_str(ed1[i]);
		if( key < 0 ) {
			key  = (-1) * key;
		}
		if( key > 10037 ){
			key = key % 10037; 
		} 
		int size_hash = hashtable[key].size();
		for(int j = 0;j < size_hash;j++){
			if(hashtable[key][j] == ed1[i]){
				answer.push_back(possible[i]);
				break;
			}			
		}
	for(int i = 0;i < size;i++){
		Insert(ed1[i],1);
		Delete(ed1[i],1);
		Subtitute(ed1[i],1);
		Transpose(ed1[i],1);
	}
	int size_p = possible.size();
	for(int i = 0;i < size_p;i++){
		int key = hash_str(possible[i]);
		if( key < 0 ) {
			key  = (-1) * key;
		}
		if( key > 10037 ){
			key = key % 10037; 
		} 
		int size_hash = hashtable[key].size();
		for(int j = 0;j < size_hash;j++){
			if(hashtable[key][j] == possible[i]){
				answer.push_back(possible[i]);
				break;
			}			
		}
	}
}
int main(){
	FILE *fp;
	char s1[200],s2[200];	
	fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b","r"); 
	assert( fp != NULL );
	while( fgets(s1,200,fp) != NULL ){
		if( isalpha(s1[0]) ){
			sscanf(s1,"%s",s2);
			int length = strlen(s2);
			for(int i = 0;i < length;i++){
				if( isalpha(s2[i]) ){
					s2[i] = tolower(s2[i]);
				}
			}
			int key;
			string s(s2);
			key = hash_str(s);
			if( key < 0 ) {
				key  = (-1) * key;
			}
			if( key > 10037 ){
				key = key % 10037; 
			} 
			hashtable[key].push_back(s);
		}
	}
	fclose(fp);
	char s3[200],s4[200];
	while( fgets(s3,200,stdin) != NULL ){
		sscanf(s3,"%s",s4);
		string s(s4);
		int key = hash_str(s);
		if( key < 0 ) {
			key  = (-1) * key;
		}		
		if( key > 10037 ){
			key = key % 10037; 
		} 
		
		int length = hashtable[key].size();
 		int flag = 0;
		for(int i = 0;i < length;i++){
			if( hashtable[key][i] == s){
				flag = 1;
				break;
			}			
		}
		if(flag){
			printf("%s ==> OK\n",s4);
			continue;
		}
		else{
			check(s);
			int size_ans = answer.size();
			if(!size_ans){
				printf("%s ==> NONE",s.c_str());
			}
			else{
				printf("%s ==> ",s.c_str());
				for(int i = 0;i < size_ans;i++){
					if(i == size_ans - 1){
						printf("%s\n",answer[i].c_str());
					}
					else{
						printf("%s ",answer[i].c_str());
					}
					
				}
				
			}
	
		}
	}
	return 0;
}
