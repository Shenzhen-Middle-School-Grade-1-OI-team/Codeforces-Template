//https://www.luogu.com.cn/blog/interestingLSY/cha-tou-dp-zong-jie
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 15
#define maxs 40000000
using namespace std;
typedef long long ll;
int n,m;
char tmp[maxn+5];
int a[maxn+5][maxn+5];

ll pw[maxn+5];
struct hash_table{//��Ϊ״ֵ̬̫��,�����ϣ��洢 
	static const int _base=131313;
	ll key[2][maxs+5];//[2]Ϊ��������,�洢״̬ 
	ll val[2][maxs+5];//�洢DPֵ 
	int nex[maxs+5];
	int head[_base+5];
	int ptr[2];
	void insert(int now,ll k,ll v){
//		printf("insert: %lld %lld\n",k,v);
		int mo=k%_base+1;
		for(int i=head[mo];i;i=nex[i]){
			if(key[now][i]==k){//���֮ǰ����,ֱ���ۼ� 
				val[now][i]+=v;
				return;
			}
		}
		//������� 
		ptr[now]++;
		nex[ptr[now]]=head[mo];
		key[now][ptr[now]]=k;
		val[now][ptr[now]]=v;
		head[mo]=ptr[now]; 
	}
	inline int size(int now){
		return ptr[now];
	}
	void clear(int now){
		memset(head,0,sizeof(head));
		ptr[now]=0;
	}
}S;
int main(){
	scanf("%d %d",&n,&m);
	int tx,ty;
	for(int i=1;i<=n;i++){
		scanf("%s",tmp+1);
		for(int j=1;j<=m;j++){
			if(tmp[j]=='.'){
				a[i][j]=1;
				tx=i;
				ty=j;//��¼���һ���ո��λ�� 
			}else a[i][j]=0; 
		}
	}
	pw[0]=1;
	for(int i=1;i<=15;i++) pw[i]=pw[i-1]<<2;
	
	int now=0,last;
	ll ans=0;
	S.insert(now,0,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=S.size(now);j++) S.key[now][j]<<=2;////�л�һ��,������������һλ 
		for(int j=1;j<=m;j++){
			now^=1;
			last=now^1;
			S.clear(now);
			for(int u=1;u<=S.size(last);u++){
				ll k=S.key[last][u],v=S.val[last][u];
				int p1=(k>>((j-1)*2))&3;
				int p2=(k>>(j*2))&3;//ȡ����jλ�͵�j-1λ 
				if(a[i][j]==0){//��ͨ,ֱ�Ӽ̳������ 
					if(p1==0&&p2==0) S.insert(now,k,v);
				}else if(p1==0&&p2==0){//Case 1,һ���²�ͷ��һ���Ҳ�ͷ,����һ��() 
					if(a[i+1][j]&&a[i][j+1]) S.insert(now,k+pw[j-1]*1+pw[j]*2,v);
				}else if(p1==0&&p2!=0){//Case 3.1,j-1��������û������,����ͨ����ǰ��,����ֱ��������ͨ��
					if(a[i+1][j]) S.insert(now,k-pw[j]*p2+pw[j-1]*p2,v); //������²�ͷ,j-1���ᱻ���� 
					if(a[i][j+1]) S.insert(now,k,v);  //������Ҳ�ͷ,״̬���� 
				}else if(p1!=0&&p2==0){//Case 3.2,j-1�������߱���������ͨ����ǰ��,����ֱ��������ͨ��
					if(a[i+1][j]) S.insert(now,k,v);//ͬ3.1
					if(a[i][j+1]) S.insert(now,k-pw[j-1]*p1+pw[j]*p1,v);
				}else if(p1==1&&p2==1){//Case2.1 (( ) -> ## (
					int bc=1;//��¼����ƥ�����
					for(int l=j+1;l<=m;l++){
						if(((k>>(l*2))&3)==1) bc++;//������
						else if(((k>>(l*2))&3)==2) bc--;//������ 
						if(bc==0){//�ҵ�ƥ���jλ������ 
							S.insert(now,k-pw[j-1]*p1-pw[j]*p2-pw[l],v);
							//��lλ��2��1,j-1��j���0 
							break;
						}
					} 
				}else if(p1==1&&p2==2){//Case2.3,(),ֻ�������ת�� 
					if(i==tx&&j==ty) ans+=v; 
				}else if(p1==2&&p2==1){//Case2.2,)(�γɻ�·
					S.insert(now,k-pw[j-1]*p1-pw[j]*p2,v);//2,1ȫ�����0 
				}else if(p1==2&&p2==2){//Case2.4,)),ͬCase2.1������ 
					int bc=1;//��¼����ƥ�����
					for(int l=j-2;l>=0;l--){
						if(((k>>(l*2))&3)==1) bc--;//������
						else if(((k>>(l*2))&3)==2) bc++;//������ 
						if(bc==0){//�ҵ�ƥ���j-1λ������ 
							S.insert(now,k-pw[j-1]*p1-pw[j]*p2+pw[l],v);
							//��lλ��1��2,j-1��j���0 
							break;
						}
					} 
				}
			}
		}
	}
	printf("%lld\n",ans);
}

