/*
+----> show 24 lines from input
| +--> print [more?] message
| |    input Enter, SPACE, or q
| +--> if Enter, advance next page
+ ---- if Space, advance one line
       if q --> exit
*/

/*fix bug: Redirect file input*/
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

/* to be complete:
1. how to remove 'more?' in the bottom of each output?
2. how to get next output without enter after input q SPACE or ENTER?
3. how to calculate the percentage?
4. to get input from file stream.
*/

