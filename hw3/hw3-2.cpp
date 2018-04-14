#include<cstdio>
#include<algorithm>
#define black true 
#define white false
const int mn=100;
int numr,numc;
int solved[mn][mn];//1: confirmed black; 0: confirmed white; -1: GOK
int ans[mn][mn];
class RC{
	public:
	int map[mn+1];//map[0] are prefilled white
	int needLength;
	int process;//index that should be fill next, 1 to mn
	int maxProcess;
	int numClue;
	int clue[mn];
	int processBuffer;
	int buffer[mn];
	void inititialize(void){
		map[0]=white;
		process=1;
		processBuffer=-1;
		for(int i=0;i<mn;i++)buffer[i]=0;
		needLength=0;
	}
	bool check(void){
		if(needLength>maxProcess-process)return 0;
		if(process==maxProcess){
			return (processBuffer==numClue-1)&&(buffer[processBuffer]==clue[numClue-1]);
		}
		if(map[process-1]==black){
			return buffer[processBuffer]<=clue[processBuffer];
		}
		if(map[process-1]==white){
			return processBuffer==-1||buffer[processBuffer]==clue[processBuffer];
		}
		//buffer[0...numBuffer-1] should be checked before.
	}
	void fill(bool color){
		if(color==black){
			needLength--;
			map[process]=black;
			if(map[process-1]==white)
				processBuffer++;
			buffer[processBuffer]++;
		}
		else{
			if(map[process-1]==black)needLength--;
			map[process]=white;
		}
		process++;
	}
	void erase(void){
		process--;
		if(map[process]==black){
			needLength++;
			buffer[processBuffer]--;
			if(map[process-1]==white)
				processBuffer--;
		}
		else
			if(map[process-1]==black)needLength++;
	}
};
RC row[mn];
RC col[mn];
bool solve(int r,int c){
	if(r==numr)return 1;
	ans[r][c]=black;
	row[r].fill(black);
	col[c].fill(black);
	if(row[r].check()&&col[c].check())
		if(solve(r+(c+1)/numc,(c+1)%numc))return 1;
	row[r].erase();
	col[c].erase();
	if(solved[r][c]!=1){
		ans[r][c]=white;
		row[r].fill(white);
		col[c].fill(white);
		if(row[r].check()&&col[c].check())
			if(solve(r+(c+1)/numc,(c+1)%numc))return 1;
		row[r].erase();
		col[c].erase();
	}
	return 0;
}
int main(){
	freopen("input","r",stdin);
	scanf("%d%d",&numr,&numc);
	for(int i=0;i<numr;i++){
		row[i].inititialize();
		row[i].maxProcess=numc+1;
	}
	for(int i=0;i<numc;i++){
		col[i].inititialize();
		col[i].maxProcess=numr+1;
	}
	for(int i=0;i<numr;i++){
		row[i].numClue=0;
		char tmpc=' ';
		while(tmpc==' '){
			scanf("%d",&row[i].clue[row[i].numClue]);
			row[i].needLength+=row[i].clue[row[i].numClue]+1;
			row[i].numClue++;
			scanf("%c",&tmpc);
		}
		row[i].needLength--;
		int d=numc-row[i].needLength,idx=0;
		for(int j=0;j<row[i].numClue;j++){
			for(int k=0;k<row[i].clue[j];k++)
				if(k>=d)solved[i][idx+k]=1;
			idx+=row[i].clue[j]+1;
		}

	}
	for(int i=0;i<numc;i++){
		col[i].numClue=0;
		char tmpc=' ';
		while(tmpc==' '){
			scanf("%d",&col[i].clue[col[i].numClue]);
			col[i].needLength+=col[i].clue[col[i].numClue]+1;
			col[i].numClue++;
			scanf("%c",&tmpc);
		}
		col[i].needLength--;
		int d=numr-col[i].needLength,idx=0;
		for(int j=0;j<col[i].numClue;j++){
			for(int k=0;k<col[i].clue[j];k++)
				if(k>=d)solved[idx+k][i]=1;
			idx+=col[i].clue[j]+1;
		}
	}
	puts("Input Completed.");
	solve(0,0);
	for(int i=0;i<numr;i++){
		for(int j=0;j<numc;j++){
			printf(ans[i][j]?"#":".");
		}
		puts("");
	}
}	
