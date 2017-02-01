import random
main=[]
for i in range(0,667):
	main.append([])

f=open('pp_tra.dat','r')
for i in range(0,10):
	count=0
	while count<=666:
		main[count].append(f.readline())
		count+=1
f.close()
fp=open("train.dat","w")
for l in main:
	for k in l:
		fp.write(k)
fp.close()
f=open('train.dat','r')
l=[]
for i in range(0,6670):
    l.append('NULL')
print len(l)
count=0
for i in range(0,6670):
    k=random.randint(0,6669)
    if l[k]=='NULL':
       l[k]=f.readline()
for x in l:
   if x=="NULL":
     l[l.index(x)]=f.readline()
f1=open('train.dat','w')
for i in l:
  f1.write(i)
  if len(i)<20:
      print "Error at",i
f1.close()