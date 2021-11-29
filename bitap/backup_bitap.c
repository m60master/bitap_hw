#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h> 

#define _DEBUG
#define _DEBUG_FILE_IO

const char* filename = "input.txt";
const int LIMIT_TAB=20; 

void bit_print(char *buf, unsigned long bit); 

const char *bitap_bitwise_search(const char *text, const char *pattern) { 
	// length of the pattern
	int m = strlen(pattern); 
	unsigned long move_bit; 
	unsigned long pattern_mask[CHAR_MAX+1]; 
	int i; 

	#ifdef _DEBUG 
	char buf[50]; 
	#endif 
	if (pattern[0] == '\0') return text; 
	if (m > 31) return "The pattern is too long!"; 

	/* Initialize the bit array R */ 
	move_bit = ~1; 
		printf("MOVE BIT %ld\n",move_bit);
	bit_print("MOVE BIT",move_bit);
#ifdef _DEBUG 
	printf("goal is move_bit & (1UL<<m) equal 0\n"); 
#endif 
	
	/* Initialize the pattern bitmasks */ 
	for (i=0; i <= CHAR_MAX; ++i) 
		pattern_mask[i] = ~0; 
	for (i=0; i < m; ++i) 
		pattern_mask[pattern[i]] &= ~(1UL << i); 
		printf("%ld\n",pattern_mask[i]);
	for (i=0; text[i] != '\0'; ++i) { 
		/* Update the bit array */ 
	#ifdef _DEBUG 
		bit_print("move_bit", move_bit); 
		sprintf(buf, "pattern_mask[%c]", text[i]); 
		bit_print(buf, pattern_mask[text[i]]); 
	#endif 
		move_bit |= pattern_mask[text[i]]; 
		move_bit <<= 1; 

		if (0 == (move_bit & (1UL << m))) 
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
	char *pattern = "ababc"; 

	while(fscanf(input, "%[^\n] ",text) != EOF) {
		#ifdef _DEBUG_FILE_IO 
			printf("TEXT IS >> %s\n",text);
			printf("PATTERN >> %s\n",pattern);
		#endif

		const char *find; 
		find = bitap_bitwise_search(text, pattern); 
		//printf("find : %s\n", find); 
		//unsigned long t = 32; 
		//bit_print("sample", t); 
	}
	fclose(input);

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
		printf("%d", (bit & mask) >> (31-i)); 
		mask >>= 1; 
	} 
	printf("\n"); 
}

