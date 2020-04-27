#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define maxn 50000
#define maxm 50000
using namespace std;
inline void qread(int &x) {
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
inline void qprint(int x) {
	if(x<0) {
		putchar('-');
		qprint(-x);
	} else if(x==0) {
		putchar('0');
		return;
	} else {
		if(x>=10) qprint(x/10);
		putchar('0'+x%10);
	}
}
int n,m;
int a[maxn+5];
int bsz;
int belong[maxn+5];
struct query{
	int l;
	int bel;//��������Ѱַ���� 
	int r;
	int id;
	friend bool operator < (query p,query q){
		return p.bel<q.bel||(p.bel==q.bel&&p.r<q.r);
	}
}q[maxm+5]; 


int ans[maxn+5];
int rb[maxn+5],lb[maxn+5];
//��¼��i��������ҵ������γ��� 

//���ڳ����޸Ĳ�����ջ
struct node{
	int type;//��¼���ĸ������޸ģ�1����lb,2����rb 
	int pos;
	int val;
	node(){
		
	}
	node(int _type,int _pos,int _val){
		type=_type;
		pos=_pos;
		val=_val;
	}
}st[maxn+5];
int main(){
	qread(n);
	qread(m);
	for(int i=1;i<=n;i++) qread(a[i]);
	bsz=n/sqrt(m);
	for(int i=1;i<=n;i++) belong[i]=i/bsz+1;
	for(int i=1;i<=m;i++){
		qread(q[i].l);
		qread(q[i].r);
		q[i].id=i;
		q[i].bel=belong[q[i].l];
	}
	sort(q+1,q+1+m);
	int r=0;
	int sum=0;
	for(int i=1;i<=m;i++){
		if(q[i].bel!=q[i-1].bel){//�µĿ� 
			sum=0;
			for(int i=1;i<=n;i++) lb[i]=rb[i]=0;
			r=q[i].bel*bsz;
		}
		while(r<q[i].r){//���l,r����ͬһ���飬��r�ڿ��ⲿ�ּ���,r�����������ɲ��ó����޸� 
			r++;
			lb[a[r]]=lb[a[r]-1]+1;
			rb[a[r]]=rb[a[r]+1]+1;
			int tmp=lb[a[r]]+rb[a[r]]-1; 
			sum=max(sum,tmp);
			//����a[r]���˵���������˵�����ǲ���Ҫ�޸�ÿһ��ֵ��lb,rb��ֻ��Ҫ�޸Ķα߽�ľͿ�����
			//��Ϊ��һ�β���a[r]����a[r]�Ѿ����ڣ���𰸲��䣬
			//��a[r]����ĳ�������εı߽��ϣ����ǲ�Ҫ���´𰸣������µĴ�ֻ��α߽��lb,rb�й� 
			lb[a[r]+rb[a[r]]-1]=tmp;
			rb[a[r]-lb[a[r]]+1]=tmp;
		}
		int res=sum;//���ڳ�����sum���޸ıȽ��鷳���ƶ���˵��ʱ�򲻸���sum,�����´�res 
		int top=0;
		//min(q[i].r,q[i].bel*bsz)��ʾ��ѯ���ڵ�ǰ���ڲ��ּ��� 
		for(int l=q[i].l;l<=min(q[i].r,q[i].bel*bsz);l++){//�ƶ���˵㣬Ҫ�ع� 
			lb[a[l]]=lb[a[l]-1]+1;
			rb[a[l]]=rb[a[l]+1]+1;
			int tmp=lb[a[l]]+rb[a[l]]-1;
			st[++top]=node(1,a[l]+rb[a[l]]-1,lb[a[l]+rb[a[l]]-1]);//�޸�ǰ��ԭ����ֵ������ 
			st[++top]=node(2,a[l]-lb[a[l]]+1,rb[a[l]-lb[a[l]]+1]);
			lb[a[l]+rb[a[l]]-1]=tmp;
			rb[a[l]-lb[a[l]]+1]=tmp;
			res=max(res,tmp);
		}
		for(int j=top;j>=1;j--){//�����������ζ˵���޸� 
			if(st[j].type==1) lb[st[j].pos]=st[j].val;
			else rb[st[j].pos]=st[j].val; 
		}
		for(int j=q[i].l;j<=min(q[i].r,q[i].bel*bsz);j++){//�����¼���ĵ��lb,rb���޸� 
			lb[a[j]]=rb[a[j]]=0;
		} 
		ans[q[i].id]=res; 
	}
	for(int i=1;i<=m;i++){
		qprint(ans[i]);
		putchar('\n');
	}
}

