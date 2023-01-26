#include "/home/krishanudev/rahulSir/files/headers/headers.h"

/*
*   Function description
*   This function will create backup of the access_points.json file
*   and will store in files/backup
*/
void create_backup()
{
    char source_file[25];
    strcpy(source_file,"/tmp/access_points.json");
   
    FILE *source;  
    source = fopen(source_file, "r");
    
    if(source == NULL){
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    
    char target_file[25];
    strcpy(target_file, "files/backup/backup.json");
    
    FILE *target;        
    target = fopen(target_file, "w");
    
    if( target == NULL )
    {
        fclose(source);        
        printf("Press any key to exit...\n");        
        exit(EXIT_FAILURE);
    }    
    
    char ch;
    while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, target);
                
        fclose(source);        
        fclose(target);
}


/*
*   Function description
*   Do the following three steps after every 5 second
*   1. if MD5 is not same after comparing the orignal and backup then
*   2. fill the the structure fields defined in files/headers/var.h
*   3. Call the application A and send the information after reading the file from 
*      changes.txt
*   4. Create backup
*/
void after_every_5_second()
{

    while(1) {
            if(!is_MD5_digest_same()){//if MD5 is not same after comparing the orignal and backup then
                create_structure_array();//fill the the structure fields defined in files/headers/var.h
                A(); // Call the application A and send the information after reading the file from changes.txt
                create_backup();// Create backup
            }
                                    
            sleep(5);
    }
}

/*
*   Function description
*   Calculate MD5 digest 
*/
char * calculate_file_md5(const char *filename) 
{
	unsigned char c[MD5_DIGEST_LENGTH];
	int i;
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];
	char *filemd5 = (char*) malloc(33 *sizeof(char));

	FILE *inFile = fopen (filename, "rb");
	if (inFile == NULL) {
		perror(filename);
		return 0;
	}

	MD5_Init (&mdContext);

	while ((bytes = fread (data, 1, 1024, inFile)) != 0)

	MD5_Update (&mdContext, data, bytes);

	MD5_Final (c,&mdContext);

	for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(&filemd5[i*2], "%02x", (unsigned int)c[i]);
	}

	fclose (inFile);
	return filemd5;
}

/*
*   Function description
*   Calculate MD5 digest of both the files and compare for changes
*/
int is_MD5_digest_same() {
	char *first = calculate_file_md5("/tmp/access_points.json");
	char *second = calculate_file_md5("files/backup/backup.json");
    

	if(!strcmp(first, second)){
	    free(first);
    	free(second);
    	return 1;
	}
        
	free(first);
    free(second);
	return 0;
}


