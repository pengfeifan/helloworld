#include<stdio.h>
#include<stdlib.h>
#define MaxLength 60
typedef struct{
	char str[MaxLength];
	int length;
}SeqString;
//串的赋值操作
void StrAssign(SeqString *S,char cstr[]){
	int i;
	for(i=0;cstr[i]!='\0';i++)
		S->str[i]=cstr[i];	//将常量cstr中的字符赋值给串S
	S->length=i;
}
//判断串是否为空，串为空返回1，否则返回0
int StrEmpty(SeqString S){
	if(S.length==0)
		return 1;
	else
		return 0;
}
//求串的长度操作
int StrLength(SeqString S){
	return S.length;
}
//串的复制操作
void StrCopy(SeqString *T,SeqString S){
	int i;
	for(i=0;i<S.length;i++)	//将串S的字符赋值给串T
		T->str[i]=S.str[i];
	T->length=S.length;	//将串S的长度赋值给串T
}
//串的比较操作
int StrCompare(SeqString S,SeqString T){	//比较两个串中的字符
	int i;
	for(i=0;i<S.length&&i<T.length;i++){		//比较两个串中的字符
		if(S.str[i]!=T.str[i])		//如果出现字符不同，则返回两个字符的差值
			return (S.str[i]-T.str[i]);
	}
	return (S.length-T.length);	//如果比较完毕，返回两个串的长度的差值
}
//串的插入操作。在S中第pos个位置插入T分为三种情况
int StrInsert(SeqString *S,int pos,SeqString T){
	int i;
	if(pos<0||pos-1>S->length){	//插入位置不正确，返回0
		printf("插入位置不正确");
		return 0;
	}
	if(S->length+T.length<=MaxLength){	//第一种情况，插入子串后串长≤MaxLength，即子串T完整地插入到串S中
		for(i=S->length+T.length-1;i>=pos+T.length-1;i--)	//在插入子串T前，将S中pos后的字符向后移动len个位置
			S->str[i]=S->str[i-T.length];
		for(i=0;i<T.length;i++)	//将串插入到S中
			S->str[pos+i-1]=T.str[i];
		S->length=S->length+T.length;
		return 1;
	}else if(pos+T.length<=MaxLength){	//第二种情况，子串可以完全插入到S中，但是S中的字符将会被截掉
		for(i=MaxLength-1;i>T.length+pos-i;i--)		//将S中pos以后的字符整体移动到数组的最后
			S->str[i]=S->str[i-T.length];
		for(i=0;i<T.length;i++)		//将T插入到S中
			S->str[i+pos-1]=T.str[i];
		S->length=MaxLength;
		return 0;
	}else{		//第三种情况，子串T不能被完全插入到S中，T中将会有字符被舍弃
		for(i=0;i<MaxLength-pos;i++)	//将T直接插入到S中，插入之前不需要移动S中的字符
			S->str[i+pos-1]=T.str[i];
		S->length=MaxLength;
		return 0;
	}
}
//在串S中删除pos开始的len个字符
int StrDelete(SeqString *S,int pos,int len){
	int i;
	if(pos<0||len<0||pos+len-1>S->length){
		printf("删除位置不正确，参数len不合法");
		return 0;
	}else{
		for(i=pos+len;i<=S->length-1;i++)
			S->str[i-len]=S->str[i];
		S->length=S->length-len;
		return 1;
	}
}
//串的连接操作
int StrCat(SeqString *T,SeqString S){
	int i,flag;
	if(T->length+S.length<=MaxLength){
		for(i=T->length;i<T->length+S.length;i++)
			T->str[i]=S.str[i-T->length];
		T->length=T->length+S.length;
		flag=1;
	}else if(T->length<MaxLength){
		for(i=T->length;i<MaxLength;i++)
			T->str[i]=S.str[i-T->length];
		T->length=MaxLength;
		flag=0;
	}
	return flag;
}
//截取子串操作
int SubString(SeqString *Sub,SeqString S,int pos,int len){
	int i;
	if(pos<0||len<0||pos+len-1>S.length){
		printf("参数pos和len不合法");
		return 0;
	}else{
		for(i=0;i<len;i++)
			Sub->str[i]=S.str[i+pos-1];
		Sub->length=len;
		return 1;
	}
}
//串的定位操作
int StrIndex(SeqString S,int pos,SeqString T){
	int i,j;
	if(StrEmpty(T))
		return 0;
	i=pos;
	j=0;
	while(i<S.length&&j<T.length){
		if(S.str[i]==T.str[j]){
			i++;
			j++;
		}else{
			i=i-j+1;
			j=0;
		}
	}
	if(j>=T.length)
		return i-j+1;
	else 
		return 0;
}
//串的替换操作
int StrReplace(SeqString *S,SeqString T,SeqString V){
	//将S中所有的T替换为V
	int i;
	int flag;
	if(StrEmpty(T))
		return 0;
	i=0;
	do{
		i=StrIndex(*S,i,T);//找到T在S中的位置
		if(i){
			StrDelete(S,i,StrLength(T));	//删除找到的T
			flag=StrInsert(S,i,V);	//在i位置插入V
			if(!flag)
				return 0;
			i+=StrLength(V);
		}
	}while(i);
	return 1;
}
//串的清空操作
void StrClear(SeqString *S){
	S->length=0;
}
//===========
void StrPrint(SeqString S){
	int i;
	for(i=0;i<S.length;i++){
		printf("%c",S.str[i]);
	}
	printf("\n");
}
void main(){
	SeqString S1,S2,Sub;
	char ch[MaxLength];	
	printf("请输入第一个字符串:\n");
	gets(ch);
	StrAssign(&S1,ch);
	printf("输出串S1：");
	StrPrint(S1);
	printf("请输入第二个字符串:\n");
	gets(ch);
	StrAssign(&S2,ch);
	printf("输出串S2：");
	StrPrint(S2);
	printf("将串S2插入到S1的第13个位置:\n");
	StrInsert(&S1,13,S2);
	StrPrint(S1);
	printf("将串S1中的第22个位置起的7个字符删除:\n");
	StrDelete(&S1,22,7);
	StrPrint(S1);
	printf("将串S2中的第6个位置起的4字符取出放入Sub中:\n");
	SubString(&Sub,S2,6,4);
	StrPrint(Sub);
	printf("将串Sub赋值为America:\n");
	StrAssign(&Sub,"America");
	printf("将串S1中的串S2用Sub取代:\n");
	StrReplace(&S1,S2,Sub);
	StrPrint(S1);
	system("pause");
}