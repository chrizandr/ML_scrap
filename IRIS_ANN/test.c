#include <stdio.h>
#include <string.h>
#include <math.h>

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

int main()
{
	double f[5];
	int i,j,k,m;
	int n;
	char s[1000];
	FILE *fp,*o;
	double x;
	double Win[5][5];
	double Whd[3][6];
	int c=0;
printf("Enter number of hidden nodes:\n");
	scanf("%d",&n);	
o=fopen("weight","r");
	printf("Reading node weights from file 'weight'\n");

	for(i=0;i<n;i++)
	{for(j=0;j<5;j++)
		{fscanf(o,"%lf",&x);
			Win[i][j]=x;
		}}
	for(i=0;i<3;i++)
	{for(j=0;j<n+1;j++)
		{fscanf(o,"%lf",&x);
			Whd[i][j]=x;}}

	fp=fopen("test","r");
	for(m=0;m<50;m++)
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
		double y[n+1],z[3];

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

		for(j=0;j<3;j++)
		{          
			z[j]=0;
			for(k=0;k<n+1;k++)
			{
				z[j]+=y[k]*Whd[j][k];
			}
			z[j]=1/(1+exp(-1*z[j]));
		}

		if(diff(target,z)>0.1)
		{
			printf("Target: %lf %lf %lf | Output:%lf %lf %lf \n",target[0],target[1],target[2],z[0],z[1],z[2]);
			printf("Entry: %lf %lf %lf %lf %s\n\n",f[0],f[1],f[2],f[3],s);
		}
		else
		{	
			c++;
		}
	}
	printf("Cases Classified correctly:%d \n",c);
	return 0;
}    
