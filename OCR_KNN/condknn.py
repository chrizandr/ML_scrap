def getkey(item):
	return item[0]

import numpy as np
def train():
  #r-fold cross validation:
  r=3
  #number of training entries:
  n=6670
  #Splitting into r equal part
  tset=[]
  cset=[]
  print "Training using file train.dat"
  f=open("train.dat","r")
  flag=0
  for line in f:  
         a=np.array([map(int,line.split())])
         #print a.shape
         tset.append(a)
         if flag==0:
            cset.append(a)
            flag=1
  count=0
  prev=-10
  while 1:
     count=0
     for entry in tset:
  	   l=[]
             for case in cset:
  		#print case.shape
  		x=case[0:192]
   		y=entry[0:192]
  		temp=(x-y)*(x-y)
  		d=temp.sum()
  		l.append([d,case[0][192]])
             l=sorted(l,key=getkey)
             c=l[0]
             if entry[0][192]!=c[1]:
                 count+=1
                 cset.append(entry)
     print count,len(cset)
     if count==prev:
        break    
     prev=count     
  print "Built condensed set, writing it to a file...."
  fp1=open("cset.dat","w")
  for t in cset:
   s=""
   for x in np.nditer(t):
     #print s
     s+=str(x)+" "
   s+="\n"
   fp1.write(s)
  fp1.close()
  print "Done writing, condensed set stored in file cset.dat"

def test(k):
  r=3
  n=6670
  tset=[]
  cset=[]
  print "Getting condensed set from file cset.dat"
  f=open("cset.dat","r")
  flag=0
  for line in f:  
         a=np.array([map(int,line.split())])
         #print a.shape
         cset.append(a)
  count=0
  ai=[0,0,0,0,0,0,0,0,0,0]
  print "Testing queries from file test.dat"
  with open("test.dat","r") as fp:
     for entry in fp:
       l=[]
             entry=np.array([map(int,entry.split())])
             for case in cset:
      x=case[0:192]
      y=entry[0:192]
      temp=(x-y)*(x-y)
      d=temp.sum()
      l.append([d,case[0][192]])
             l=sorted(l,key=getkey)
             a={0:0,2:0,1:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}
             for i in range(0,k):
                  a[l[i][1]]+=1
             maximum=0
             label=-1
             for i in a:
                   if maximum < a[i]:
                             maximum=a[i]
                             label=i

             if entry[0][192]!=label:
                 print "error predicted-",label,"actual-",entry[0][192]
                 ai[entry[0][192]]=ai[entry[0][192]]+1
             else:
                 count+=1
  print "Done testing, ",count, " entries correctly classified"

train()
test()
  


 

