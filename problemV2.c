#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
void checkWarningsandError(int warning, int error, char name[])
{
    int fd;
    char string[256];
    fd = open("grades.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (error == 0 && warning == 0)
    {
        sprintf(string, "%s : %d", name, 10);
    }
    else if (error >= 1)
    {
        sprintf(string, "%s : %d", name, 1);
    }
    else if (warning > 10)
    {
        sprintf(string, "%s : %d", name, 2);
    }
    else
    {
        int score = 2 + 8 * (10 - warning) / 10;
        sprintf(string, "%s : %d", name, score);
    }
    write(fd, string, sizeof(string));

    close(fd);
}
void format(struct stat file)
{
    printf("USER:\n");
    if (file.st_mode & S_IRUSR)
    {
        printf("Read:YES\n");
    }
    else
    {
        printf("Read:NO\n");
    }
    if (file.st_mode & S_IWUSR)
    {
        printf("Write:YES\n");
    }
    else
    {
        printf("Write:NO\n");
    }
    if (file.st_mode & S_IXUSR)
    {
        printf("Execution:YES\n");
    }
    else
    {
        printf("Execution:NO\n");
    }
    printf("\nGROUP:\n");
    if (file.st_mode & S_IRGRP)
    {
        printf("Read:YES\n");
    }
    else
    {
        printf("Read:NO\n");
    }
    if (file.st_mode & S_IWGRP)
    {
        printf("Write:YES\n");
    }
    else
    {
        printf("Write:NO\n");
    }
    if (file.st_mode & S_IXGRP)
    {
        printf("Execution:YES\n");
    }
    else
    {
        printf("Execution:NO\n");
    }
    printf("\nOTHERS:\n");
    if (file.st_mode & S_IROTH)
    {
        printf("Read:YES\n");
    }
    else
    {
        printf("Read:NO\n");
    }
    if (file.st_mode & S_IWOTH)
    {
        printf("Write:YES\n");
    }
    else
    {
        printf("Write:NO\n");
    }
    if (file.st_mode & S_IXOTH)
    {
        printf("Execution:YES\n");
    }
    else
    {
        printf("Execution:NO\n");
    }
}
void getLinkname(char *file)
{
    char buffer[1024];

    readlink(file, buffer, sizeof(buffer) - 1);
    printf("The link name of %s is %s\n ", file, buffer);
}
void getLinksize(char *file)
{
    char buffer[1024];
    readlink(file, buffer, sizeof(buffer) - 1);
    struct stat Target;
    lstat(buffer, &Target);
    printf("The link size of %s is %lld\n ", file, Target.st_size);
}
void check_c_files(char *dir_name)
{
    DIR *dir;
    struct dirent *ent;
    int count = 0;
    int len;
    dir = opendir(dir_name);
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            len = strlen(ent->d_name);
            if (strcmp(ent->d_name + len - 2, ".c") == 0)
                count++;
        }
        closedir(dir);
    }
    else
    {
        printf("Error opening dir\n");
    }
    printf("The number of c files is %d", count);
}
void menu(char name[], struct stat file_stat)
{
    char choose;
    if (S_ISREG(file_stat.st_mode))
    {
        struct tm *time = localtime(&file_stat.st_mtime);
        printf("Choose one \n");
        printf("-n (file name)\n");
        printf("-d (dim/size)\n");
        printf("-h number of hardlinks\n");
        printf("-m (time of last modify\n");
        printf("-a (access rights)\n");
        printf("-l (create a sym link, give sym link name)\n");
        scanf("%c", &choose);
        switch (choose)
        {
        case 'n':
            printf("File name: %s\n", name);
            break;
        case 'd':
            printf("The file size is %lld", file_stat.st_size);
            break;
        case 'h':
            printf("The number of hard links is %hu\n", file_stat.st_nlink);
            break;
        case 'm':
            printf("%d minutes and %d seconds have elapsed since the file has been modified", time->tm_min, time->tm_sec);
            break;
        case 'a':
            format(file_stat);
            break;
        case 'l':
            printf("Name of the link you want to create: \n");
            char str[20];
            scanf("%s", str);
            symlink(name, str);
            printf("The link %s was created\n", str);
            break;
        default:
            break;
        }
    }
    else if (S_ISLNK(file_stat.st_mode))
    {
        printf("%s is a sym link \n", name);
        printf("Choose one \n");
        printf("-n(link name)\n");
        printf("-l (delete link)\n");
        printf("-d(size of the link)\n");
        printf("-t (size of the target)\n");
        printf("-a (access rights) \n");
        scanf("%c", &choose);
        switch (choose)
        {
        case 'n':
            getLinkname(name);
            break;
        case 'l':
            unlink(name);
            printf("The link was deleted\n");
            break;
        case 'd':
            printf("Size of the link is %lld \n", file_stat.st_size);
            break;
        case 't':
            getLinksize(name);
            break;
        case 'a':
            format(file_stat);
            break;
        default:
            break;
        }
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        printf("%s is a directory \n", name);
        printf("-d size\n");
        printf("-a access rights\n");
        printf("-c total number with the .c extension");
        scanf("%c", &choose);
        switch (choose)
        {
        case 'n':
            printf("File name is %s\n", name);
            break;
        case 'd':
            printf("Size of the file is %lld\n", file_stat.st_size);
            break;
        case 'c':
            check_c_files(name);
            break;
        case 'a':
            format(file_stat);
            break;
        default:
            break;
        }
    }
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Please insert more arguments");
        return -1;
    }
    int pid[argc];
    struct stat file_stat;
    for (int i = 1; i < argc; i++)
    {
        if (lstat(argv[i], &file_stat) < 0)
        {
            printf("Error reading file");
            return 0;
        }
        pid[i] = fork();
        if (pid[i] == 0)
        {
            menu(argv[i], file_stat);
            exit(0);
        }
        else
        {
            int pfd[2];
            if (pipe(pfd) < 0)
            {
                perror("Pipe creation error\n");
                exit(1);
            }
            int second_pid;
            if (S_ISREG(file_stat.st_mode))
            {
                if (strcmp(argv[i] - 2, ".c"))
                {
                    second_pid = fork();
                    if (second_pid == 0)
                    {
                        close(pfd[0]);
                        dup2(pfd[1], 1);
                        execlp("./compileFile.sh", "compileFile.sh", argv[i], NULL);
                        exit(0);
                    }
                }
                else
                {
                    second_pid = fork();
                    if (second_pid == 0)
                    {
                        close(pfd[0]);
                        close(pfd[1]);
                        execlp("wc", "wc", "-l", argv[i], NULL);
                        exit(0);
                    }
                }
            }
            else if (S_ISDIR(file_stat.st_mode))
            {
                second_pid = fork();
                if (second_pid == 0)
                {
                    close(pfd[0]);
                    close(pfd[1]);
                    execlp("./createFile.sh", "createFile.sh", argv[i], NULL);
                    exit(0);
                }
            }
            else if (S_ISLNK(file_stat.st_mode))
            {
                second_pid = fork();
                if (second_pid == 0)
                {
                    close(pfd[0]);
                    close(pfd[1]);
                    execlp("chmod", "chmod", 760, argv[i], NULL);
                    exit(0);
                }
            }
            FILE *stream;
            int warning = 0;
            int error = 0;
            close(pfd[1]);
            stream = fdopen(pfd[0], "r");
            fscanf(stream, "%d", &warning);
            fscanf(stream, "%d", &error);
            checkWarningsandError(warning, error, argv[i]);
            close(pfd[0]);
            int status;
            pid_t w;
            w = wait(&status);
            if (w == -1)
            {
                printf("Error at wait!\n");
                exit(4);
            }
            if (WIFEXITED(status))
            {
                printf("\nChild end correct: pid=%d, status=%d\n", w, WIFEXITED(status));
            }
        }
    }
    int status;
    pid_t w;
    for (int i = 1; i < argc; i++)
    {
        w = wait(&status);
        if (w == -1)
        {
            printf("Error at wait!\n");
            exit(4);
        }
        if (WIFEXITED(status))
        {
            printf("\nChild end correct: pid=%d, status=%d\n", w, WIFEXITED(status));
        }
    }
    return 0;
}