#include "/home/krishanudev/rahulSir/files/headers/headers.h"

/*
*   Function description
*   This function will only read the file changes.txt
*/
void read_the_changes(char **buff)
{
    FILE* ptr;
    char *temp;
	long numbytes;
	
	//open the change file in read write mode
	ptr = fopen("/home/krishanudev/rahulSir/changes.txt", "a+");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}
	
	fseek(ptr, 0L, SEEK_END);
    numbytes = ftell(ptr);
    fseek(ptr, 0L, SEEK_SET);	

    temp = (char*)calloc(numbytes, sizeof(char));	


    fread(temp, sizeof(char), numbytes, ptr);
    
	*buff = temp;
    
	fclose(ptr);
}
