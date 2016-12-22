#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

const int maxn=1100;

char str[maxn*maxn];
char tstr[maxn*maxn];
char ip[maxn];
char file_sv[30][maxn];
char file_cl[30][maxn];

void init_filename(){
	for(int i=1;i<=5;i++){
		strcpy(file_sv[i],"Server/S/server");
		int len=strlen(file_sv[i]);
		file_sv[i][len++]=(i+'0');
		file_sv[i][len]='\0';
		strcat(file_sv[i],".cpp");
	}
	for(int i=1;i<=5;i++){
		strcpy(file_cl[i],"Client/C/room");
		int len=strlen(file_cl[i]);
		file_cl[i][len++]=(i+'0');
		file_cl[i][len]='\0';
		strcat(file_cl[i],".cpp");
	}
}

void set_ip(char *path,char *ip,int id){
	FILE *fp=fopen(path,"r");
	char ch;
	int strn=0;
	bool tag=0;
	bool flag=0;
	while(fscanf(fp,"%c",&ch)!=EOF){
		str[strn++]=ch;
		if(ch=='\"'&&!tag){
			for(int i=0;i<strlen(ip);i++) str[strn++]=ip[i];
			while(fscanf(fp,"%c",&ch)!=EOF){
				if(ch!='\"') continue;
				str[strn++]=ch;
				break;
			}
			tag=1;
		}
		else if(tag&&!flag&&ch=='8'){
			str[strn++]='0';str[strn++]='0';
			str[strn++]=(id+'0');
			for(int i=1;i<=3;i++) fscanf(fp,"%c",&ch);
			flag=1;
		}
	}
	fclose(fp);
	fp=fopen(path,"w");
	for(int i=0;i<strn;i++) fprintf(fp,"%c",str[i]);
	fclose(fp);
}

int main(){
	printf("请输入服务器的ip地址(如果不清楚请在服务器上的终端上输入ifconfig查看):\n ");
	scanf("%s",ip);
	init_filename();
	for(int i=1;i<=5;i++) set_ip(file_sv[i],ip,i);
	for(int i=1;i<=5;i++) set_ip(file_cl[i],ip,i);
	system("chmod +x run.sh");
	system("./run.sh");
	printf("设置成功!\n");
	return 0;
}


