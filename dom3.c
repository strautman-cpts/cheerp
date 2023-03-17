#include <stdlib.h>
#include <stdio.h>

char * ar[3];
static int i = 0;
 
void init()
{
	printf("Hello World.!.\n");
	int i = 0;
	for (i = 0; i < 3; i++) {
		//ar[i] = (char *)malloc(64*sizeof(char));
		ar[i] = (char *)malloc(1024);
		if (ar[i] == NULL) {
			printf("malloc failed");
			return;
		}
	}	
	
	snprintf(ar[0], 1024, "line 1");
	snprintf(ar[1], 1024, "line 2");
	snprintf(ar[2], 1024, "line 3");
	return;
}

char * myFunction() {
	printf("MyFunction Called\n");
	if (i >= 3) i = 0;
	return ar[i++];
}

int myIntFunc() {
	printf("MyIntFunc Called\n");
	if (i >= 3) i = 0;
	return i++;
}

char * getLine(int x) {
	printf("getLine Called\n");
	if (x > -1 && x < 3)
		return ar[x];
	return "Out of bounds";
}

char * exchangeStr(const char* str) {
	printf("exchangeStr Called\n");
	printf("exchangeStr str = %s", str);
	return "No, I'm not going with you.";
}
