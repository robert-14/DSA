#include<stdio.h>
#include<string>
using namespace std;
int main(){
	string s("fuck u");
	s.insert(s.length(),"haha");
	printf("%s\n",s.c_str());
	return 0;


}
