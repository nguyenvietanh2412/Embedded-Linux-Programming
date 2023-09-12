#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_LEN 100
int main() {
    char directory[MAX_LEN ];

    printf("Enter directory name: ");
    scanf("%s", directory);

    DIR *dir = opendir(directory);

    if (dir == NULL) {
        printf("Could not open directory.\n");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;

        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
        stat(path, &fileStat);

        if (S_ISREG(fileStat.st_mode))
            printf("File: %s\n", entry->d_name);
        else if (S_ISDIR(fileStat.st_mode))
            printf("Folder: %s\n", entry->d_name);
        else
            printf("Other: %s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}