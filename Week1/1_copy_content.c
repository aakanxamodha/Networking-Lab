//1. Write a program to copy one file to another using file system calls.

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
        int fd1, fd2, n;
        char buff[25];
        fd1=open("F1.txt",O_RDONLY);
        fd2=open("F3.txt",O_WRONLY|O_CREAT,0644);
        while((n=read(fd1,buff,20))!=0)
        {
                write(fd2,buff,n);
        }
}
