#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h> 

#include "timer.h"

//#define _DEBUG
//#define _DEBUG_FILE_IO
#define _DEBUG_FOUND


const char* filename = "input.txt";
const int LIMIT_TAB=20; 

void bit_print(char *buf, unsigned long bit); 

const char *bitap_bitwise_search(const char *text, const char *pattern) { 
	// length of the pattern
	int m = strlen(pattern); 
	unsigned long state; 
	unsigned long pattern_mask[CHAR_MAX+1]; 
	int i; 

	#ifdef _DEBUG 
	char buf[50]; 
	#endif 
	if (pattern[0] == '\0') return text; 
	if (m > 31) return "The pattern is too long!"; 

	// Initial State 1111...111
	// Word is used for the comparison,
	// thus the max length of pattern is word size(32bits)
	state = ~1;
	#ifdef _DEBUG
			bit_print("INITIAL STATE : ",state);
	#endif

	/* Initialize the pattern bitmasks */ 
	for (i=0; i <= CHAR_MAX; ++i)
		pattern_mask[i] = ~0;
	// We build the table for the unique chars by performing OR for each occurence
	// i.e. Pattern ababc -> bit in little endian, becomes cbaba by reversing the order
	// Table[b] = 01010 by occurence of b in reverse pattern 'cbaba'
	for (i=0; i < m; ++i)
		pattern_mask[pattern[i]] &= ~(1UL << i);
	for (i=0; text[i] != '\0'; ++i) {
		/* Update the bit array */
		#ifdef _DEBUG 
			printf("===================================");
			printf("===================================\n");
			bit_print("state", state);
			sprintf(buf, "pattern_mask[%c]", text[i]); 
			bit_print(buf, pattern_mask[text[i]]); 
		#endif 
		state |= pattern_mask[text[i]]; 
		state <<= 1; 

		if (0 == (state & (1UL << m))) 
		return (text + i - m) + 1; 
	} 
	return NULL; 
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
	//char *pattern = "ZzZZz"; 
	char *pattern = "the"; 
	int line_count = 0;

	timer_init(1);
	timer_reset(0);
	timer_start(0);
	while(fscanf(input, "%[^\n] ",text) != EOF) {
		#ifdef _DEBUG_FILE_IO 
			printf("TEXT IS >> %s\n",text);
			printf("PATTERN >> %s\n",pattern);
		#endif

		const char *found; 
		found = bitap_bitwise_search(text, pattern); 
		#ifdef _DEBUG_FOUND
		if(found != NULL) {
			printf("%d >> %s\n",++line_count,text);
		}
		#endif
	}
	fclose(input);
	timer_stop(0);
	timer_finalize();
	printf("elapsed time %lf\n",timer_read(0));

	return 0; 
} 

void bit_print(char *buf, unsigned long bit) { 
	int i; 
	int buf_len; 
	unsigned long mask; 

	mask = (1UL <<31 ); 
	buf_len = strlen(buf); 

	for ( i = 0; i < (LIMIT_TAB - buf_len); i++ ) { 
		printf(" "); 
	} 
	printf("%s : ", buf); 

	for ( i = 0; i < 32; i++ ) { 
		if (i%4 == 0) { 
			printf(" "); 
		} 
		printf("%ld", (bit & mask) >> (31-i)); 
		mask >>= 1; 
	} 
	printf("\n"); 
}

