#include<bits/stdc++.h>
using namespace std;
int call_table[100][100]={0};//�к��ǵڼ��ڿΣ��к���ѧ����ѧ�� 
int score_table[100]={0};//ѧ���ĳɼ��� 
int score_table_ordered[100]={0};//������ѧ���ɼ� 
int N;//N����ȱ��ѧ�� 
int absent_stu_num[100];//���N����ȱ��ѧ����ѧ�� 
int focus_table[100];//�㷨һ�������ѧ������ 
int focus_table2[100];//�㷨���������ѧ������ 

void score_table_create(){
	N=5+rand()%3;
	for(int i=0;i<90;i++){
		score_table[i]=40+rand()%60;
		score_table_ordered[i]=score_table[i];
	}
}

void absent_stu_num_create(){//�ӳɼ�����ʮ��ѧ�����������N����ȱ��ѧ�� 
	score_table_create();
	sort(score_table_ordered,score_table_ordered+90);
	int cnt=N;
	int flag=score_table_ordered[9];
	for(int i=0;i<90;i++){
		if(cnt==0)break;
		if(score_table[i]<=flag){
			absent_stu_num[cnt-1]=i;
			cnt--;
		}
	}
}

void data_create(){//�������ݼ� 
	absent_stu_num_create();
	for(int i=0;i<N;i++){
		int absent_class[100]={0};//��¼��ȱ��ѧ��ȱ���ļ��ڿ� 
		int vis[100]={0};//��֤��ȱ��ѧ�����ȱ��ʮ���ڿ� 
		for(int j=0;j<16;){
			int index=rand()%19;
			if(vis[index]==0){
				vis[index]=1;
				absent_class[j]=index;
			}
			else continue;
			j++; 
		}
		for(int k=0;k<16;k++){
			call_table[absent_class[k]][absent_stu_num[i]]++;
		}
	}
	
	for(int i=0;i<20;i++){//ÿ�ڿ��������������ȱ��ѧ�� 
		int M=rand()%3;
		int vis[100]={0};
		int absent_stu[100]={0};
		for(int j=0;j<M;){
			int index=rand()%89;
			if(vis[index]==0){
				vis[index]=1;
				absent_stu[j]=index;
			}
			else continue;
			j++;
		}
		for(int k=0;k<M;k++){
			call_table[i][absent_stu[k]]++;			
		}
	} 
}

double rollcall(){//�㷨һ�ĵ��� 
	int correct=0;
	int cnt=0;
	double ans=0;
	for(int i=0;i<90;i++){
		if(call_table[0][i]!=0){
			focus_table[cnt]=i;
			cnt++;
		}
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<90;j++){
			if(call_table[i][j]==1){
				for(int k=0;k<N;k++){
					if(focus_table[k]==j){
						correct++;break;
					}	
				}
			}
		}
	}
	ans=(double)correct/(N*20);
	return ans;
}

double rollcall2(){//�㷨���ĵ��� 
	int cnt=0;
	int correct=0;
	double ans;
	for(int i=0;i<90;i++){
		if(score_table[i]<=score_table_ordered[9]){
			focus_table2[cnt]=i; 
			cnt++;
			if(cnt==N)break;
		}
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<90;j++){
			if(call_table[i][j]==1){
				for(int k=0;k<N;k++){
					if(focus_table2[k]==j){
						correct++;break;
					}	
				}
			}
		}
	}
	ans=(double)correct/(N*20);
	return ans;
}

void init(){//��ʼ���������� 
	memset(call_table,0,sizeof(call_table));
	memset(score_table,0,sizeof(score_table));
	memset(score_table_ordered,0,sizeof(score_table_ordered));
	memset(absent_stu_num,0,sizeof(absent_stu_num));
	memset(focus_table,0,sizeof(absent_stu_num));
	memset(focus_table2,0,sizeof(focus_table2));	
}

int main(){
	double sum=0,sum2=0;
	data_create();
	printf("-----��1�β�����ϸ����-----\n") ;
	printf("\n��ȱ��ѧ������\n");
	for(int i=0;i<N;i++){
		printf("%d ",absent_stu_num[i]);
	}
	printf("\n��ȱ��ѧ���ɼ�\n");
	for(int i=0;i<N;i++){	
		printf("%d ",score_table[absent_stu_num[i]]); 
	}
	for(int i=0;i<20;i++){
		printf("\n��%d�ڿ�\n",i); 
		for(int j=0;j<90;j++){
			if(j%10==0)printf("\n");
			printf("%d ",call_table[i][j]);
		} 
	}
	double result=rollcall();
	sum+=result;
	printf("\n��һ���㷨�����E=%lf\n",result);
	result=rollcall2();
	sum2+=result;
	printf("�ڶ����㷨�����E=%lf\n",result);
	printf("-----ѭ��һ�ٴν��ƽ��ֵ-----\n");
	for(int i=0;i<99;i++){
		srand(i);
		init();
		data_create();
		printf("---��%d�β���---\n",i+1);
		result=rollcall();
		sum+=result;		
		printf("��һ���㷨�����E=%lf\n",result);
		result=rollcall2();
		sum2+=result;
		printf("�ڶ����㷨�����E=%lf\n",result);
		printf("N=%d\n",N);
	}
	printf("\n----ѭ��һ�ٴεľ�ֵ----\n");
	printf("�㷨һ��E=%lf  �㷨����E=%lf\n",sum/100,sum2/100);		
}

