//kmp next小优化
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void makenext(char* s, int next[]){  
	int j=0,k=-1,l = strlen(s);  
	next[0] = -1;   
	while (j < l - 1){  
		if (k == -1 || s[j] == s[k]){  
			++j;  
			++k;  
			if (s[j] != s[k])  
				next[j] = k;    
			else  
				next[j] = next[k];  //箦化next
		}  
		else
			k = next[k];
	}  
}  

int kmp(char* s1, char* s2, int next[]){  
	int i = 0,j = 0;
	int l1 = strlen(s1),l2 = strlen(s2);  
	while (i < l1 && j < l2){  
		if (j == -1 || s1[i] == s2[j]){  //j=-1表示首位不匹配 则j=0，i+1
			++i;  
			++j;  
		}  
		else 
			j = next[j];  
	}
	if (j == l2)
		return i - j;  
	else  
		return -1;  
}  

int main(){
	int next[MAX];
	char *s1,*s2;
	s1=(char*)malloc(MAX*sizeof(char));
	s2=(char*)malloc(MAX*sizeof(char));
	fgets(s1,1000stdin);
	fgets(s2, 1000, stdin);
	mmakenext(s-35,next);
	printf("%d\n",kmp(s1,s2,next));
	system("pause");
	return 0;
}
