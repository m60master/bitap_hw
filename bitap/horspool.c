#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/stat.h>

#include "timer.h"

#define _DEBUG
#define _DEBUG_FILE_IO

const char* filename = "input.txt";
int jump[500];

void computeJump(char* pattern, int* jump) {
 int length = 0, i, j;
 while(pattern[length] != '\0') {
  length++;
 }
 for(i = 0; i < 500; i++) {
  jump[i] = length;
 }
 for(j = 0; j < length - 1; j++) {
  jump[pattern[j]] = length - 1 - j;
 }
}

void BoyerMooreHorspool(char* text, char* pattern) {
 int pattern_size = strlen(pattern);
 //int* jump = malloc(sizeof(int) * (pattern_size+1));

 computeJump(pattern, jump);
 int n = 0, m = 0, i = 0, j, k;
 while(text[n] != '\0') {
  n++;
 }
 while(pattern[m] != '\0') {
  m++;
 }
 while(i <= n - m) {
  j = m - 1;
  k = i + m - 1;
  while(j >= 0 && pattern[j] == text[k]) {
   j--;
   k--;
  }
  if(j == -1) {
   printf("Matched from position %d\n", i);
  }
  i = i + jump[text[i + m - 1]];
 }
}

int main() {
	// ========================================================
	// STEP A. READ THE TEXT & PATTERN
	// ========================================================
	// READ THE TEXT FROM THE INPUT FILE
	FILE* input = fopen(filename,"r");
	struct stat sb;
	stat(filename,&sb);
	char* text = malloc(sb.st_size);
	// READ THE PATTERN
	//char *pattern = "ababc"; 
	char *pattern = "ZzZZz"; 

	timer_init(1);
	timer_reset(0);
	timer_start(0);
	while(fscanf(input, "%[^\n] ",text) != EOF) {
		#ifdef _DEBUG_FILE_IO 
			printf("TEXT IS >> %s\n",text);
			printf("PATTERN >> %s\n",pattern);
		#endif

    BoyerMooreHorspool(text, pattern);
	}
	fclose(input);
	timer_stop(0);
	timer_finalize();
	printf("elapsed time %lf\n",timer_read(0));

  return 0;
}

