/*
feature: Without An ENTER after a <q>|<ENTER>|<SPACE>, the program gets input.
Method: Change stty attributes.
*/
#include<stdio.h>
#include<stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more(FILE *);
int main(int argc, char *argv[])
{
    FILE *fp;
    if(argc == 1)
        do_more(stdin);
    else
        while(--argc)
        {
            if((fp = fopen(* ++argv,"r")) != NULL)
            {
                do_more(fp);
                fclose(fp);
            }
        }
}

void do_more(FILE * fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(), reply;
    FILE *fp_tty;
    fp_tty = fopen("/dev/tty","r");
    if(fp_tty == NULL)
        exit(1);
    while(fgets(line,LINELEN,fp))
    {
        if(num_of_lines == PAGELEN) // full screen?
        {
            reply = see_more(fp_tty); // 1, 24, or exit
            if(reply == 0)
                break;
            num_of_lines -= reply;
        }
        if(fputs(line, stdout) == EOF)
            exit(1);
        num_of_lines++;
    }
}

int see_more(FILE *cmd)
{
    int c;
    system("stty -icanon");
    printf("\033[7m more?\033[m");
    while((c=getc(cmd))!=EOF)
    {
        if(c == 'q')
            return 0;
        if(c == ' ')
            return PAGELEN;
        if(c =='\n')
            return 1;
    }
    return 0;
}


