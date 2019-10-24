#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* to_str(int n)
{
    unsigned int  k     =  0;
    char         *buf  =  NULL;
    
    while(n != 0)
    {
        buf = (char*)realloc(buf,k + 1);
        buf[k++] = n % 10 + '0';
        n /= 10;
    }
    
    buf = (char*)realloc(buf,k + 1);
    buf[k] = '\0';
    
    char l = strlen(buf);
    for(char i = 0;i < l / 2;i++)
    {
        char aux = buf[i];
        buf[i] = buf[l - i - 1];
        buf[l - i - 1] = aux;
    }
    
    return buf;
}

char* offs_str(int offset, unsigned int out_c)
{
    char  *buf    =  (char*)malloc(out_c);
    char  *o      =  to_str(offset);
    int   zeroes  =  out_c - strlen(o);
    
    int i = 0;
    while(i < zeroes)
        buf[i++] = '0';
    
    strcat(buf,o);
    
    return buf;
}

void hex_disp(char *file_name, int char_no)
{
    FILE  *f      =  fopen(file_name,"rb");
    int   offset  =  0;
    int   l;
    char  buf[128];
    
    if(!f)
    {
        printf("Error opening input file!");
        exit(EXIT_FAILURE);
    }
    
    while((l = fread(&buf,1,char_no,f)) != 0)
    {
        printf("%s | ",offs_str(offset,8));
        
        for(int i = 0;i < l;i++)
        {
            if(i != 0 && i % 4 == 0) printf(" ");
            printf("%02X ",(buf[i] < 0) ? -buf[i] : buf[i]);
        }
        
        printf("| ");
        
        for(int i = 0;i < l;i++)
            {
            if(i != 0 && i % 4 == 0) printf(" ");
            printf("%c",isprint(buf[i]) ? buf[i] : '.');
        }
        
        offset += l;
        
        printf("\n");
    }
    
    fclose(f);
}

int main(int argc, char *argv[])
{
    if(argc != 2 && argc != 3)
    {
        printf("Use: %s <file_name> *<chars_per_line>",argv[1]);
        exit(EXIT_FAILURE);
    }
    
    hex_disp(argv[1],atoi(argv[2]));
    
    return 0;
}
