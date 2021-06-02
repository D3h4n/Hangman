#include "hangman.h"

int main(){
	int i;
	int count;
	int failCount;
  int upperLimit;
	bool end = false;
	bool run = true;
	char guesses[26];
	char input[3];
	char array[Wlength];
	Word wordObj = {"", ""};

  startup(&failCount, &upperLimit);

	while (run) {
		end = false;
		count = 0;
		strcpy(guesses, "");
		strcpy(array, "");
		strcpy(wordObj.word, "");
		strcpy(wordObj.hint, "");
		
		while (strlen(wordObj.word) <= 0 || strlen(wordObj.hint) <= 0){
			wordObj = setup(upperLimit);
		}
		
		for (i = 0; i < strlen(wordObj.word); i++){
      if (isalpha(wordObj.word[i])) {
			  array[i] = '-';
      }
      else {
			  array[i] = wordObj.word[i];
      }
		}
		array[i] = '\0';
			
		display(guesses, array, wordObj, count);

		while (!end) {
			if(!game(guesses, array, wordObj, count)){
				count++;
			}
			
			display(guesses, array, wordObj, count);
			
			if(strcmp(wordObj.word, array)==0){
				printf ("\nYay you win!!!\n\n");
				end = true;
			}
			else{
				if (count >= failCount){
					printf("\nYou lose!\n\n");
					end = true;
				}
			}
		}
		
		printf("Again?\n1. Yes\n2. No\n----> ");
		
		fgets(input, 3, stdin);

    char * temp;

    if((temp = strchr(input, '\n')) != NULL) {
      *temp = '\0';
    }

		for (i = 0; i < strlen(input); i++) {
			input[i] = tolower(input[i]);
		}

		if(strcmp(input, "no") == 0 || strcmp(input, "2") == 0){
			run = false;
		}
	}

	system("Pause");
	return 0;
}
