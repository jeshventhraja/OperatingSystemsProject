#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<pthread.h>
#include<string.h>
#include <time.h>
#include "sys/stat.h"
void access_tester();
void processid_test();
void access_tester()
{
      
    if(access("testfile_a.txt",F_OK)==0)
     printf("accessed");
     else
     printf("not accessed");
}
void processid_test()
{
        int x=getpid();
        printf("pid %d uid:%d euid:%d gid:%d egid:%d\n",x,getuid(),geteuid(),getgid(),getegid());
        
}

void fork_test()
{
        int x=getpid();
        fork();
        if(getpid()==x)
        {       
                wait(NULL);
                printf("in parent pid1: %d\n",x);
                printf("uid:%d euid:%d gid:%d egid:%d\n\n",getuid(),geteuid(),getgid(),getegid());
                
        }
        else
        {
                printf("In child pid:%d ppid:%d\n",getpid(),getppid());
                printf("uid:%d euid:%d gid:%d egid:%d\n\n",getuid(),geteuid(),getgid(),getegid());
                exit(0);
        }
}
void sleep_test()
{
        printf("Sleeping for 5 seconds\n");
        sleep(5);
}

void exit_test()
{
        exit(0);
}
void chmod_tester()
{
        chmod("testfile_a.txt",S_IRUSR);
}

int create_tester()
{
        int filedesc =creat("testfile1.txt",S_IRWXU );
        filedesc=open("testfile1.txt", O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return 1;

    if(write(filedesc,"This will be output to testfile.txt(made uisng creat systemcall)\n", 36) != 36)
    {
        write(filedesc,"There was an error writing to testfile.txt\n",30);    // strictly not an error, it is allowable for fewer ..
        return 1;
    }
}

void file_tester()
{
        int filedesc = open("testfile_a.txt",O_CREAT| O_WRONLY | O_APPEND);
    char buf[100];
    if(filedesc < 0)
       { printf("Could not open file\n");return ;}

    if(write(filedesc,"This will be output to testfile.txt(made using open systemcall)\n", 64) != 64)
    {
        write(filedesc,"There was an error writing to testfile.txt\n",30);    // strictly not an error, it is allowable for fewer ..
        return;
    }
close(filedesc);
    int filedesc1= open("testfile_a.txt", O_RDONLY);
    if(read(filedesc1,buf,4));
puts(buf);
    close(filedesc1);
}



void link_tester()
{
         char buffer[19];
         printf("creating testfile_d.txt and then linking testfile_e.txt to it\n");	
    int filedesc = open("testfile_d.txt",O_CREAT| O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return;
       write(filedesc,"This will be output to testfile.txt\n", 36);
       close(filedesc);
      
      if(link("testfile_d.txt","testfile_e.txt"))
       printf("linked");
       
}

void unlink_tester()
{
        char buffer[19];	
  
       
      unlink("testfile_e.txt");
      printf("unlinked testfile_e.txt\n");
}


void date_tester()
{
        time_t mytime;
	mytime = time(NULL);
	printf((char*)ctime(&mytime));
}

void process_control()
{
        int select;
        printf("1.fork,2.sleep 3.exit\n");
        scanf("%d",&select);
        switch(select)
        {
                case 1:
                fork_test();
                break;
                case 2:
                sleep_test();
                break;
                case 3:
                exit_test();
                break;
                default:
                printf("Wrong entry");
                return;
        }
}

void fd_control()
{
        int select;
        printf("1.file_functions,2.check access 3.change file access(chmod) 4.link 5.unlink\n");
        scanf("%d",&select);
        switch(select)
        {
                case 1:
                file_tester();
                break;
                case 2:
                access_tester();
                break;
                case 3:
                chmod_tester();
                break;
                case 4:
                link_tester();
                break;
                case 5:
                unlink_tester();
                break;
                default:
                printf("Wrong entry");
                return;
        }
}

void info_maintain()
{
        int select;
        printf("1.get_process details,2.date&time \n");
        scanf("%d",&select);
        switch(select)
        {
                case 1:
                processid_test();
                break;
                case 2:
                date_tester();
                break;
               
                default:
                printf("Wrong entry");
                return;
        }
}

void pipes_tester()
{
       int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        printf("using fork and then sending message from child to parent process.\n");
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                printf("In child input the message word to send\n");
                /* Child process closes up input side of pipe */
                close(fd[0]);
                scanf("%s",string);
                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("In parent process\n");
                printf("Received string: %s", readbuffer);
        }
        
        return;
}
void communication()
{
        int select;
        printf("1.pipes \n");
        scanf("%d",&select);
        switch(select)
        {
                case 1:
                pipes_tester();
                break;
                default:
                printf("Wrong entry");
                return;
        }
}
int main()
{
    while(1)
    {
        int select;
        printf("\n1.process_control,2.File&Device Management ,3.Information Maintanence,4.Communication :");
        scanf("%d",&select);
        switch(select)
        {
                case 1:
                process_control();
                break;
                case 2:
                fd_control();
                break;
                case 3:
                info_maintain();
                break;
                case 4:
                communication();
                break;
                default:
                exit(0);
        }
        
        
    }
   
}
    
