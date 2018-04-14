#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct{
	int bidId,clientId,action,price,sharecount;
} data;
vector<data> buy,sell;
int num;
bool comp_buy(const data a,const data b){
	if( a.price < b.price ) return 1;
	else if( a.price > b.price ) return 0;
	else{
		if( a.bidId > b.bidId ) return 1;
		else return 0;
	}
}
bool comp_sell( const data a,const data b){
	if( a.price > b.price ) return 1;
	else if( a.price < b.price ) return 0;	
	else{
		if( a.bidId > b.bidId ) return 1;
		else return 0;
	}
}
void trade(){
		while(true){
			if( sell.size() == 0 || buy.size() == 0 )	 return;
			if( sell[0].price <= buy[0].price ){
				if( sell[0].sharecount > buy[0].sharecount ){
					printf("%d\t%d\t%d\t%d\t%d\n",num,buy[0].clientId,sell[0].clientId,sell[0].price,buy[0].sharecount);					
					num++;
					sell[0].sharecount -= buy[0].sharecount;
					pop_heap(buy.begin(),buy.end(),comp_buy);
					buy.pop_back();
				}
				else if( sell[0].sharecount < buy[0].sharecount ){
					printf("%d\t%d\t%d\t%d\t%d\n",num,buy[0].clientId,sell[0].clientId,sell[0].price,sell[0].sharecount);					
					num++;
					buy[0].sharecount -= sell[0].sharecount;
					pop_heap(sell.begin(),sell.end(),comp_sell);
					sell.pop_back();
				}
				else{
					printf("%d\t%d\t%d\t%d\t%d\n",num,buy[0].clientId,sell[0].clientId,sell[0].price,sell[0].sharecount);					
					num++;
					pop_heap(sell.begin(),sell.end(),comp_sell);
					sell.pop_back();
					pop_heap(buy.begin(),buy.end(),comp_buy);
					buy.pop_back();
				}
			}
			else{
				break;
			}
		}
}
void cancel(int id){
	int size = buy.size();
	for(int i = 0;i < size;i++){
		if( buy[i].bidId == id ){
			buy.erase( buy.begin() + i );
			return;
		} 
	}
	size = sell.size();
	for(int i = 0;i < size;i++){
		if( sell[i].bidId == id ){
			sell.erase( sell.begin() +i);
			return;
		}
	}
}
int main(){
	data temp;
	while( scanf("%d%d%d%d%d",&temp.bidId,&temp.clientId,&temp.action,&temp.price,&temp.sharecount) != EOF){
		if( !temp.action ){     //buy
			buy.push_back(temp);
			make_heap( buy.begin(),buy.end(),comp_buy );
			trade();
		}
		else if( temp.action == 1 ){ //sell
			sell.push_back(temp);
			make_heap( sell.begin(),sell.end(),comp_sell);
			trade();
		}
		else{                        //cancel
			cancel(temp.price);
			make_heap( buy.begin(),buy.end(),comp_buy );
			make_heap( sell.begin(),sell.end(),comp_sell);
		}	
		
	}
	return 0;
}
