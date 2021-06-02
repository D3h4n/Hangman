#include "settings.h"

void create_settings(){
	FILE* p;
	int i;
	char settings[][length] = {
									"number_tries = \"\"",
									"words_filename = \"\""
								};
	
	if((p = fopen("./settings.txt", "a")) == NULL){
		printf ("Error Creating Settings File\n");
		exit(1);
	}
	
	for (i = 0; i < sizeof(settings) / sizeof(*settings); i++){
		fprintf(p, "%s\n", settings[i]);
	}

	fclose(p);
}

void read_setting(char Read[], int number){
	FILE* settings;
	int i;
	char* subString;
	
	if((settings = fopen("./settings.txt","r")) != NULL){
		for(i = 0; i < number; i++){
			fgets(Read, length, settings);
		}
	
		subString = strtok(Read,"\"");
		subString = strtok(NULL,"\""); 
		  
		if(subString == NULL){
			strcpy(Read, "");
		}	
		else{
			strcpy(Read, subString);
		}
	}
	else{
		printf ("creating settings.txt\n");
		create_settings();
		strcpy(Read, "");
	}

	fclose(settings);
}
