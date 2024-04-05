#ifndef __GENERAL__
#define __GENERAL__



#define MAX_STR_LEN 255


char*	getStrExactName(const char* msg);
char* myGets(char* buffer, int size,FILE* stream);
char*	getDynStr(char* str);

void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
void generalArrayFunctionForSongRepostiory(void* arr, int size, int typeSize, void(*func)(const void* element));



#endif

