#include <stdio.h>
#include <stdlib.h>
#include "token.c"
//#include <sys/time.h>
//#include <assert.h>

char ** mytoken(char *str, char delim );
int countWords(char *str);

int wordcount;

// char *test = " wert cjbvj djfvj zkdn bnfjngf   dfjgjbfg   dodododododo  ";

int main(char *input, char delim){
  
  
  
  // if(input == '\0'){
    
    input = "Empty";

    char *test = " wert cjbvj djfvj zkdn bnfjngf   dfjgjbfg   dodododododo  ";
    // }

  

    // if(delim  == '\0'){
    
    delim = ' ';
     
    //}
  
  char ** tested = mytoken(test,' ');
 
  //char ** tested = mytoken(test, ' ');
  
  // int wordcount = countWords(test);
  
  // char ** tested = malloc(wordcount);
  int x = 0;
  int y = 0;

  while(tested[x] != '\0'){

    printf("%s \n", tested[x]);

    x++; 

  }

}


char ** mytoken(char *str, char delim){

int count = 0;
int words = 0;
int length = 0;


char *newToken;

int words2 = countWords(str); 

 
 length = 0;


 
 char **tokens = malloc(words2); 

 

 
 while(str[length] != '\0'){

  if(str[length] != ' '){    

      if (count == 0){
	
	 words++;
	 
      }
      count++;
      
  }
  
  else{
    if(count > 0){
      
      int wordsize = length-count;
      
      newToken = malloc(count);
      
      int x = 0; 
      
      while(str[wordsize] != ' '){
	
	
	newToken[x] = str[wordsize];
	
	wordsize++;

	
	x++;
      }
      
      
      tokens[words-1] = newToken;
      
      //   printf("The words is %c :\n", newToken);
      
      /// printf("Reached this");
      
      count = 0;
      
    }
    
    
    
  }
  
  
  
  length++; 
  
 } 
 
 //  printf("The words is %s :", tokens[]); 
 
 return tokens; 
 
}





int countWords(char *str){
  int length = 0;
  int count =0;
  int words = 0; 
  
 while(str[length] != '\0'){

  if(str[length] != ' '){

    if (count == 0){

      words++;

    }
      count++;
  }

  else{

    if(count > 0) count = 0;
    
  }

  length++; 

}

 return words;

}
