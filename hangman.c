#include "hangman.h"

int randInt(int upper, int lower){
	srand(time(0));
	return (rand() % (upper-lower+1) + lower);	
}

int createWordFile(){
	FILE* words;
	FILE* wordsTxt;
	Word word = {"", ""};
	int count = 0;
	char input[Wlength + Hlength];
	char wordsTxtFilename[length];

	read_setting(wordsTxtFilename, 2);

	if((wordsTxt = fopen(wordsTxtFilename, "r")) == NULL || (words = fopen("words","wb+")) == NULL){
		return 0;
	}

	fgets(input, sizeof(input), wordsTxt); // skip heading line
	fseek(words, 0, SEEK_SET);

	fgets(input, sizeof(input), wordsTxt);
	while(!feof(wordsTxt)){
		sscanf(input, "%[^,],%[^\n]", word.word, word.hint);

		fwrite(&word, sizeof(Word), 1, words);
		count++;
		
		fgets(input, sizeof(input), wordsTxt);
	}
	
	fclose(wordsTxt);
	fclose(words);
	
	return count;
}

void startup(int * failCount, int * upperLimit){
	char read[length];

	*upperLimit = createWordFile();
	
	if (*upperLimit <= 1) {
		printf("Startup Error: Check Words File");
		exit(1);
	}
	
	read_setting(read, 1);

	if(strcmp(read, "") == 0 || atoi(read) < 1){
		printf("Startup Error: Check Settings File");
		exit(2);
	}

	*failCount = atoi(read);
}

Word setup(int upperLimit){
	FILE* words;
	Word input;
	int randIdx;

	if((words=fopen("words","rb+"))==NULL){
		printf("Error opening word file\n");
		exit(1);
	}	

	randIdx = randInt(upperLimit - 1, 0);

	fseek(words, sizeof(Word) * randIdx, SEEK_SET);
	fread(&input,sizeof(Word),1,words);

	fclose(words);
	return input;
}

void display(char guesses[], char array[], Word word, int wrong){
	int i;
	system("cls");
	printf("Wrong: %d\n",wrong);
	printf("Hint: %s\n",word.hint); 
	
	printf("%s\n",array);
	
	for(i = 0; i < strlen(guesses); i++){
		printf("%c ",guesses[i]);
	}
	printf("\n");
}

bool game(char guesses[], char array[], Word word, int count){
	char guess;
	int i;
	bool found = false;

	while (true) {
		printf("\nEnter guess--> ");
		scanf("%c", &guess);
		fflush(stdin);

		if (isalpha(guess) && strchr(guesses, guess) == NULL){
			break;
		}
		
		display(guesses,array,word,count);	
	}
	
	for(i = 0; i < strlen(word.word); i++){
		if(word.word[i] == guess || toupper(word.word[i]) == guess){
			found = true;
			array[i] = guess;	
		}	
	}
	
	if (!found) {
		strcat(guesses, &guess);
		return false;
	}
	else {
		return true;
	}
}
