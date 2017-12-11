#include <stdio.h>
#include <stdlib.h>


char ** mytoken(char *str, char delim );
int countWords(char *str, char delim);

int wordcount;

void split(char* str, char** tokens, char delim) {

	int count = 0;
	int words = 0;
	int length = 0;

	while (str[length] != '\0' ){
		if (str[length] != delim ) {
			count = 0;
			while(str[length] != delim && str[length] != '\0' ){
				count ++;
				length++;
			}

			int wordsize = length - count;

			char *newToken = malloc((sizeof(char) * count));

			int x = 0;

			while (wordsize < length) {

				newToken[x] = str[wordsize];

				wordsize++;
				x++;

			}

			tokens[words] = newToken;


			words++;
		}

		else {
			length++;
		}



	}

}



char ** mytoken(char *str, char delim){




	int words2 = countWords(str, delim);

	// printf("It has %i \n", words2);

	char ** tokens = malloc((sizeof(char*) * words2)+1);

	tokens[words2] =  '\0';


	split(str, tokens, delim);





	return tokens;

}





int countWords(char *str, char delim){
	int length = 0;
	int count =0;
	int words = 0;

	while(str[length] != '\0'){

		if(str[length] != delim){

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
