#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

int i,row,line= 0;
char a[1000];                 //程序
int number[1000][100];       //常数表
char mark[100][5];           //标识符表


int wordanalysis(){
	if ((a[i] >= 'A'&&a[i] <= 'Z')||(a[i]>='a'&&a[i]<='z')){  //分析标识符和保留字
        char word[10];
        char pro[100][100] = { "PROGRAM", "BEGIN", "END", "VAR", "INTEGER", "WHILE", "IF", "THEN", "ELSE", "DO", "PROCEDURE" ,
                                "char","int","if","else","var" ,"return","break","do","while","for","double","float","short"}; //保留字表
	int n = 0;    
    word[n++] = a[i++];
    
    //若字符为A~Z或0~9，则继续读取
    while((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= '0' && a[i] <= '9')){
    	word[n++] = a[i++];
    }
    word[n] = '\0';
    i--;
  
    //判断标识符长度是否超出规定
    if(strlen(word) > 20){
    	printf("%s\t Lexical analyzer read unlawful identifier",word);
    	return 0;
    }
	  
    //判断该标识符是否为保留字
    for(n = 0; n < 100; n++){
    	if(strcmp(word, pro[n]) == 0){
    		printf("%s\t(%d,->)\n", pro[n],n+1);//输出保留字
    		return 3;
    	}
    }
        
    //判断该标识符是否存在标识符表中
    int m = 0;
    if(line != 0){
    	int q = 0;
    	while(q<line){
    		if(strcmp(word,mark[q++]) == 0){
    			printf("%s\t(12,'%s')\n",word,word);
    			return 3;
    		}
    	}
    }
    
    //将该标识符保存到标识符表中
    strcpy(mark[line], word);
    printf("%s\t(12,'%s')\n", word, word);//输出标识符
    line++;
    return 3;
  }
  else if(a[i] >= '0' && a[i] <= '9'){ //分析常数
  	char x[100];
  	int n = 0,sum;
  	x[n++] = a[i++];
  	
 	//判断字符是否是0~9
  	while(a[i] >= '0' && a[i] <= '9'){
  		x[n++] = a[i++];
  	}
  	x[n] = '\0';
  	i--;
  	int num = atoi(x);  //将字符串转换成int型
  	
  	//判断该常数是否存在于常数表中
  	if(row != 0){
  		int y;
  		for(y = 0; y < 1000; y++){
  			int w = number[y][0];
  			sum = 0;
  			int d;
  			for(d = 1; d <= number[y][0]; d++){
  				w = w - 1;
  				sum = sum + number[y][d] * pow(2, w);
  			}
  			if(num == sum){
  				printf("%d\t(13,%d)\n",num, y + 1);
  				return 3;
  			}
  		}
  	}
  	
  	int line = row;
  	printf("%d\t(21,%d)\n", num, num);
  	row++;
  	return 3;
  }
  else									//输出除字符外的其他符号
  	switch(a[i]){
  		case ' ':
  		case '\n':
  			return -1;
  		case '#':
  			return 0;
  		case '=':
  			printf("=\t(14,->)\n");
  			return 3;
  		case '<':
  			i++;
  			if(a[i] == '='){
  				printf("<= \t(16,->)\n");
  				return 3;
  			}
  			else if(a[i] == '>'){
  				printf("<>\t(19,->)\n");
  				return 3;
  			}
  			else{
  				i--;
  				printf("<\t(15,->)\n");
  				return 3;
  			}
  		case '>':
  			i++;
  			if (a[i] == '=')
            {
                printf(">=\t(18,->)\n");
                return 3;
            }
            else
            {
                i--;
                printf(">\t(17,->)\n");
                return 3;
            }
        case '+':
        	printf("+\t(20,->)\n");
        	return 3;
        case '-':
        	printf("-\t(21,->)\n");
			return 3;
		case '*':							//删除注释
			i++;
			if(a[i] != '/'){
				i--;
				printf("*\t(22,->)\n");
				return 3;
			}
			else{
				while(1){
					if(a[i++] == '\n')
						return -1;
				}
				printf("*/\t(35,->)\n");
				return 3;
			}
		case '/':
			i++;
			if(a[i] != '/' && a[i] != '*'){
				i--;
				printf("/\t(23,->)\n");
				return 3;
			}
			else{
				while(1){
					if(a[i++] == '*')
						if(a[i] == '/')
							return -1;
					if(a[i++] == '\n')
						return -1;
				}
				printf("//\t(35,->)\n");
				return 3;
			}
		case '%':
			 printf("%\t(38,->)\n");
			 return 3;
 		case '!':
		 	 printf("!\t(37,->)\n");
			 return 3;
 		case '.':
		 	 printf(".\t(33,->)\n"); 
			 return 3;
        case ':': 
			 printf(":\t(24,->)\n");
			 return 3;
        case ';':
			 printf(";\t(25,->)\n");
			 return 3;
        case '(':
			 printf("(\t(26,->)\n");
			 return 3;
        case ')':
			 printf(")\t(27,->)\n");
			 return 3;
        case '{':
			 printf("{\t(28,->)\n");
			 return 3;
        case '}':
			 printf("}\t(29,->)\n");
			 return 3;
        case '[':
			 printf("[\t(30,->)\n");
			 return 3;
        case ']':
			 printf("]\t(31,->)\n");
			 return 3;
        case '|':
			 printf("|\t(32,->)\n");
			 return 3;
        case '"':
			 printf("\"\t(33,->)\n");
			 return 3;
        case ',':
			 printf(",\t(34,->)\n");
			 return 3;
        case '\'':
			 printf("'\t(36,->)\n");
			 return 3;					
  		case '&': 
            i++;
            if(a[i]!='&'){
                i--;
                printf("&\t(37,->)\n");
			    return 3;
            }   
            else{   
                printf("&&\t(38,->)\n");
				return 3;

            }
        case '\\':
			 printf("\\\t(39,->)\n");
			 return 3;
        default: {
			printf("Lexical analyzer read Unlawful sign %d  Unlawful identifier\n",i);
			return 0;
		}
  	}
}

int main(){
	int l = 0;
	int m;
	i = 0;
	FILE * fp;
	fp = fopen("D:\\编译原理\\3.txt","r"); 
	if(fp == NULL){
		printf("File is not exist!");
		exit(0);
	}
	
	while(!feof(fp)){
		a[l++] = fgetc(fp);
		printf("%c",a[l-1]);		
	}
	printf("\n");
	a[l] = '#';
	do{
		m = wordanalysis();
		switch(m){
			case -1:
				i++;
				break;
			case 0:
				i++;
				break;
			case 3:
				i++;
				break;
		}
	}while(m != 0);
	
	int i = 0,j = 0;
	fp = fopen("D:\\编译原理\\2.txt","w");
	while(mark[j][i] != '\0'){
		while(mark[j][i] != '\0'){
			fprintf(fp,"%c",mark[j][i]);
			i++;
		}
		fprintf(fp,"\n");
		i = 0;
		j++;
	}
	fclose(fp);
	printf("write over!");
	_getch();
	return 0;
}
