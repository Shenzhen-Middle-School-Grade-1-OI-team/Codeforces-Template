//����TSP
/*���⣺������һ����������Ҫ�ݷ�N�����У�������ѡ����Ҫ�ߵ�·����
·����������ÿ������ֻ�ܰݷ�һ�Σ��������Ҫ�ص�ԭ�������ĳ��У����ܶٻ�·����
Ҫ��·�����ܺ���С 
*/ 
/*������״̬ѹ�� �㼯s
	   �Ѽ���s�е�i����ɾ���� s&=~(1<<i)
	   �жϵ�i�����Ƿ����ڼ���s�� if(s&(1<<i)==0) return false; else return true;
	   
	   ״̬dp[s][i]����sΪ�㼯����ǰ�ڵ�i���ڵ����С�ܺ� 
	   ״̬ת�Ʒ��̣�dp[i][j]=min(dp[s&~(1<<i)][j]+dis[j][i],dp[i][j])
	   jΪ�㼯s�в�����i��һ���� 
*/
#include<iostream>
#include<cstring>
#include<cmath> 
#define maxn 17
using namespace std;
int n;
struct node{
	double x;
	double y;
}dot[maxn];
double dis[maxn][maxn];
double dp[1<<maxn][maxn];
double cal_dist(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void ini(){
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			dp[i][j]=0x7fffffff;
		}
	}
	
	dp[1][0]=0;//����ص���㣬ֻҪ�����1��Ϊ0 
	//������ص����for(int i=0;i<n;i++) dp[(1<<i)][i]=0;//��1,10��ÿһ��������ʼ�����0        
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			dis[i][j]=dis[j][i]=cal_dist(dot[i].x,dot[i].y,dot[j].x,dot[j].y);
		}
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>dot[i].x>>dot[i].y;
	}
	ini();
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			if(s&(1<<i)==0) continue;
			for(int j=0;j<n;j++){
				if(i!=j&&(s&(1<<j))>0){
					dp[s][i]=min(dp[s&(~(1<<i))][j]+dis[j][i],dp[s][i]);
					//debug();
				}
			}
		}
	}
	double ans=0x7fffffff;
	for(int i=0;i<n;i++){
		ans=min(ans,dp[(1<<n)-1][i]+dis[i][0]);
	}
	cout<<ans<<endl; 
	//debug();
}
/*
3
2.5 4.0
1.2 -2.4
8.7 1.2
*/
