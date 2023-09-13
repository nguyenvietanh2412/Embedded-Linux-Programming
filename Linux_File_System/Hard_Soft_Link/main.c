#include <stdio.h>
#include <dirent.h>
#include <string.h>
#define MAX_LEN 100
int main(){
    DIR *d;
    struct dirent *dir;
    char filename[MAX_LEN];
    char directory[MAX_LEN];

    printf("Enter file to search:");
    scanf("%s", filename);
    printf("Enter directory to search:");
    scanf("%s", directory);

    d = opendir(directory);

    if (d == NULL){
        printf("Could not open directory.\n");
        return 1;
    }

    while ((dir = readdir(d)) != NULL){
        if (strcmp(filename, dir->d_name) == 0){
            printf("%s found!\n", filename);
            closedir(d);
            return 0;
        }
    }
    printf("%s not found!\n", filename);

    return 0;
}
/*
    Create hard link: 
    SYNTAX:     ln <filepath of the original file> <filepath of the new file>
    CHECK IF THE NEW FILE WAS CREATED:      ls -l <filepath of the original file> <filepath of the new file>
    DISPLAY THE CONTENT OF THE ORIGINAL FILE THROUGH HARD LINK:         cat <filepath of the new file>

    Create soft link:
    SYNTAX:     ln -s <filepath of the original file> <filepath of the new file>
    CHECK IF THE NEW FILE WAS CREATED:      ls -l <filepath of the original file> <filepath of the new file>
    DISPLAY THE CONTENT OF THE ORIGINAL FILE THROUGH HARD LINK:         cat <filepath of the new file>

    Difference between hard link and soft link:
        If we delete the original file, the hard-link-created file still exist while the soft-link will be dangling,
        and if we recreate the original in somewhere, the soft-link won't be dangling and its content will be restored
*/
// D:\Training\Embedded_Linux_Programming\Linux_File_System\Hard_Soft_Link\main.c
