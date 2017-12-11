#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.c"



int main(){

  char *test = " wert cjbvj djfvj zkdn bnfjngf   dfjgjbfg   dodododododo  ";

  //char ** tested = mytoken(test, ' ');

  int wordcount = countWords(test);

  // char ** tested = malloc(wordcount);

 char ** tested = mytoken(test, ' ');
   
  printf("1.The words is %s :", tested[1]);

}
