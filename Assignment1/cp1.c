//Alfred Shaker
//Systems programming
//Assignment 1
//cp1

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main (int argc,char *argv[]){
  int outFile, inFile, len, nChars;
  char buf[BUFFERSIZE];
  struct dirent *pDirent;
  DIR *pDir; //source directory
  DIR *dDir; //target directory
  
  //check for correct number of arguments
  if (argc < 3){
    printf("not enough arguments <dirname>\n");
    return 1;
  }

  //open the directories
  //opens source directory
  pDir = opendir (argv[1]);
  if(pDir == NULL){
    printf ("Cannot open directory '%s'\n", argv[1]);
    return 1;
  }
  //opens target directory
  //if none, creates one
  dDir = opendir (argv[2]);
  if (dDir == NULL){
    printf("cannot find directory, creating new one");
    mkdir(argv[2], 0700);
  }
  
  printf("Copying files from %s to %s \n", argv[1], argv[2]);
  //go through the source directory to get its contents
  //so that they can be copied to the target directory
  while ((pDirent = readdir(pDir)) != NULL) {
    //access file in first directory
    //make the name and path accessable as a variable
    int newLen = strlen(argv[1]) + strlen (pDirent->d_name) + 1;
    char *fileName = (char *) malloc(newLen);
    strcpy (fileName, argv[1]);
    strcat (fileName, pDirent->d_name);
    //    printf("%s\n", fileName);
    inFile = open(fileName, O_RDONLY);

    //take the name and path from the first directory
    //and make it available to the second directory
    //so that a new file is created with the same name
    int newLen2 = strlen(argv[2]) + strlen (pDirent->d_name) + 1;
    char * newFile = (char *) malloc(newLen2);
    strcpy (newFile, argv[2]);
    strcat (newFile, pDirent->d_name);
    //printf("new file name and location: %s\n", newFile);
    outFile = creat(newFile, COPYMODE);
    
    //copy the file contents from the first directory to the second
    while((nChars = read(inFile, buf, BUFFERSIZE)) > 0)
      if( write(outFile, buf, nChars) != nChars)
	oops("Write error to ", newFile);
    
  }

  printf("Copy successful!\n");
  close(inFile);
  close(outFile);
  closedir(pDir);
  closedir(dDir);
  return 0;
} 

void oops(char *s1, char *s2){
  fprintf(stderr, "Error: %s ", s1);
  perror(s2);
  exit(1);
}
