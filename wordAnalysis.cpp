#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

int i,row,line= 0;
char a[1000];                 //����
int number[1000][100];       //������
char mark[100][5];           //��ʶ����


int wordanalysis(){
	if ((a[i] >= 'A'&&a[i] <= 'Z')||(a[i]>='a'&&a[i]<='z')){  //������ʶ���ͱ�����
        char word[10];
        char pro[100][100] = { "PROGRAM", "BEGIN", "END", "VAR", "INTEGER", "WHILE", "IF", "THEN", "ELSE", "DO", "PROCEDURE" ,
                                "char","int","if","else","var" ,"return","break","do","while","for","double","float","short"}; //�����ֱ�
	int n = 0;    
    word[n++] = a[i++];
    
    //���ַ�ΪA~Z��0~9���������ȡ
    while((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= '0' && a[i] <= '9')){
    	word[n++] = a[i++];
    }
    word[n] = '\0';
    i--;
  
    //�жϱ�ʶ�������Ƿ񳬳��涨
    if(strlen(word) > 20){
    	printf("%s\t Lexical analyzer read unlawful identifier",word);
    	return 0;
    }
	  
    //�жϸñ�ʶ���Ƿ�Ϊ������
    for(n = 0; n < 100; n++){
    	if(strcmp(word, pro[n]) == 0){
    		printf("%s\t(%d,->)\n", pro[n],n+1);//���������
    		return 3;
    	}
    }
        
    //�жϸñ�ʶ���Ƿ���ڱ�ʶ������
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
    
    //���ñ�ʶ�����浽��ʶ������
    strcpy(mark[line], word);
    printf("%s\t(12,'%s')\n", word, word);//�����ʶ��
    line++;
    return 3;
  }
  else if(a[i] >= '0' && a[i] <= '9'){ //��������
  	char x[100];
  	int n = 0,sum;
  	x[n++] = a[i++];
  	
 	//�ж��ַ��Ƿ���0~9
  	while(a[i] >= '0' && a[i] <= '9'){
  		x[n++] = a[i++];
  	}
  	x[n] = '\0';
  	i--;
  	int num = atoi(x);  //���ַ���ת����int��
  	
  	//�жϸó����Ƿ�����ڳ�������
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
  else									//������ַ������������
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
		case '*':							//ɾ��ע��
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
	fp = fopen("D:\\����ԭ��\\3.txt","r"); 
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
	fp = fopen("D:\\����ԭ��\\2.txt","w");
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
