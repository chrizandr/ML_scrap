#include <stdio.h>
#include <string.h>
#include <math.h>
double Win[][5]={{0.1,0.2,0.3,0.4,0.5},{0.1,0.2,0.3,0.4,0.5},{0.1,0.2,0.3,0.4,0.5},{0.1,0.2,0.3,0.4,0.5},{0.1,0.2,0.3,0.4,0.5}};
double Whd[][6]={{0.1,0.2,0.3,0.4,0.5,0.6},{0.1,0.2,0.3,0.4,0.5,0.6},{0.1,0.2,0.3,0.4,0.5,0.6}};
double Whd2[][6]={{0.1,0.2,0.3,0.4,0.5,0.6},{0.1,0.2,0.3,0.4,0.5,0.6},{0.1,0.2,0.3,0.4,0.5,0.6}};
//-----------------------------------------------------------------------------------
void printweight(int n)
{
  FILE *f=fopen("weight","w");
  int i,j;
  for(j=0;j<n;j++)
  {
      for(i=0;i<5;i++)
    {
      fprintf(f,"%lf\n",Win[j][i]);
    }
  }

  for(j=0;j<3;j++)
  { 
    for(i=0;i<n+1;i++)
    {
        fprintf(f,"%lf\n",Whd[j][i]);
    }
  }  
  printf("Output written to file 'weight'\n");
  return;
}
//-----------------------------------------------------------------------------------
double diff(double z[], double t[])
{
  int i;
  double sum=0,x;
  for(i=0;i<3;i++)
  {
    x=t[i]-z[i];
    sum=sum+x*x;
  }
  return sum/2.0;
}
//-----------------------------------------------------------------------------------
void clsfy(double f[],double t[],int n)
{
  double y[n+1],z[3]={0.0,0.0,0.0};
  int i,j,k;
  while(diff(z,t)> 0.000001)
  {
    //calculating hidden layer output
    for(j=1;j<n+1;j++)
    {
      y[j]=0;
      
      for(i=0;i<5;i++)
      {          
        y[j]+=f[i]*Win[j-1][i];    
      }
      
      y[j]=1.0/(1.0+exp(-1.0*y[j]));
    }
      
    y[0]=1;
    //calculating output
    for(j=0;j<3;j++)
    {
      z[j]=0;
      for(k=0;k<n+1;k++)
      {
        z[j]+=y[k]*Whd[j][k];
      }
      z[j]=1/(1+exp(-1*z[j]));
    }
    //new values hidden to output      
    for(i=0;i<3;i++)
    {
      for(j=0;j<n+1;j++)
      {
        double deltak=(t[i]-z[i])*z[i]*(1-z[i]);
        Whd2[i][j]=Whd2[i][j]+(0.1*deltak*y[j]);
      }
    }
    //new values input to hidden      
    for(i=0;i<5;i++)
    {
      for(j=1;j<n+1;j++)
      {
        double sum=0;
        for(k=0;k<3;k++)
        {
          sum=sum+(t[k]-z[k])*z[k]*(1-z[k])*Whd[k][j]*y[j]*(1-y[j])*f[i];
        }
        Win[j-1][i]=Win[j-1][i]+0.1*sum;
      }
    }
    //Update hidden to out    
    for(i=0;i<3;i++)
    {
      for(j=0;j<n+1;j++)
        Whd[i][j]=Whd2[i][j];
    }
  }
  return;
}
//-----------------------------------------------------------------------------------
int main()
{
  double f[5];
  int i,j,m;
  int epoch=50;
  char s[1000];
  FILE *fp;
 int n;
printf("Enter the number of hidden nodes:\n");
scanf("%d",&n);
  printf("Running training data for %d EPOCHS..........\n",epoch);
  while(epoch--){
    
    fp=fopen("train","r");
    for(m=0;m<100;m++)
    {

      double target[3];
      f[0]=1;
      fscanf(fp,"%lf %lf %lf %lf %s",&f[1],&f[2],&f[3],&f[4],s);
      
      if(strcmp(s,"Iris-setosa")==0)
      {
        target[0]=1;
        target[1]=0;
        target[2]=0;
      }

      else if(strcmp(s,"Iris-versicolor")==0)
      {
        target[0]=0;
        target[1]=1;
        target[2]=0;
      }

      else
      {
        target[0]=0;
        target[1]=0;
        target[2]=1;
      }
      clsfy(f,target,n);
    }
  }
  printweight(n);
  return 0;
}   
//-----------------------------------------------------------------------------------
