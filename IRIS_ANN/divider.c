#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
  int i,j;
  time_t t;
  srand(time(NULL));
  
  FILE *f=fopen("data","r");
  char c[150][1000];
  int num[150]={0};
  for(i=0;i<150;i++)
  {
    int k=rand()%150;
    if(num[k]==0)
    {
      num[k]=1;
      fscanf(f,"%s",c[k]);
      for(j=0;j<strlen(c[k]);j++)
      {
        if(c[k][j]==',')
        {
          c[k][j]=' ';
        }
      }
      //printf("%s\n",c[k]);
    }
  }
  
  for(i=0;i<150;i++)
  {
    if(num[i]==0)
    fscanf(f,"%s",c[i]);
  for(j=0;j<strlen(c[i]);j++)
      {
        if(c[i][j]==',')
        {
          c[i][j]=' ';
        }
      }
  }
  
  fclose(f);
  f=fopen("train","w");
  FILE *o=fopen("test","w");

  for(i=0;i<100;i++)
  {
    fprintf(f,"%s\n",c[i]);
  }
  for(i=100;i<150;i++)
  {
    fprintf(o,"%s\n",c[i]);    
  }
  fclose(f);
  fclose(o);

  return 0;  
}
