def getkey(item):
	return item[0]
def train():
	import numpy as np
	# r-fold cross validation:
	r=3
	# Number of training entries:
	n=6670
	# Splitting into r equal part
	bigset=[np.ones((2224,193))*-1,np.ones((2223,193))*-1,np.ones((2223,193))*-1]
	count=1
	l1=[]
	l2=[]
	l3=[]
	f=open("train.dat","r")
	print "Splitting the file into blocks"
	for line in f:
	 if count>=1 and count <=2224:
	    l1.append(map(int,line.split()))
	 elif count>2224 and count<=4447:
	    l2.append(map(int, line.split()))
	 else:
	    l3.append(map(int, line.split()))
	 count+=1
	print count
	print "Making blocks into matrices"
	bigset[0]=np.array(l1)
	bigset[1]=np.array(l2)
	bigset[2]=np.array(l3)
	final=[]
	minerr=10000000000.0
	kval=-1
	print "Checking for values of k"
	for k in range(1,11):
		error=[]
		for i in range(0,r):
			err=0
			valid=bigset[i]
			if i==0:
				train=np.concatenate((bigset[1],bigset[2]),axis=0)
			elif i==1:
				train=np.concatenate((bigset[0],bigset[2]),axis=0)
			elif i==2:
				train=np.concatenate((bigset[0],bigset[1]),axis=0)
			for entry in valid:
				a={0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}
				l=[]
				for case in train:
					x=case[0:192]
					y=entry[0:192]
					temp=(x-y)
					temp=temp*temp
					d=temp.sum()
					l.append([d,case[192]])
				l=sorted(l,key=getkey)
				for m in range(0,k):
					a[l[m][1]]+=1
				maximum=0
				label=-1
				for each in a:
					if maximum <= a[each]:
						maximum=a[each]
						label=each
				if label!=entry[192]:
					err+=1
			print "Error for k =",k, "validation set = ",i , "is: ",err
			error.append(err)
		mean=reduce(lambda x, y: x + y, error) / float(len(error))
		print "Mean for test = ",k," is: " , mean
		if minerr > mean:
			minerr=mean
			kval=k
	return kval

def test(k):
	import numpy as np
	f=open("train.dat","r")
	l=[]
	for line in f:
	    l.append(map(int,line.split()))
	print "Making blocks into matrices"
	bigset=np.array(l)
	f.close()
	f=open("test.dat",'r')
	count=0
	for line in f:
		b=np.array(map(int,line.split()))
		a={0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}
		l=[]
		for i in bigset:
			x=i[0:192]
			y=b[0:192]
			temp=(x-y)*(x-y)
			d=temp.sum()
			l.append([d,i[192]])
			l=sorted(l,key=getkey)
		for i in range(1,k+1):
			a[l[i][1]]+=1
		maximum=0
		label=-1
		for i in a:
			if maximum < a[i]:
				maximum=a[i]
				label=i
		if label!=b[192]:
			print "Wrong prediction: Predicted = ",label, " Actual = ",b[192],"Count:", count
		else:
			count+=1
	return count
		
print "Training using the training set"
k=train()
print "Testing using the test set"
m=test(k)
print m,"Correct predictions with k=",k
print "Percentage Error: ",(float(m)/6670)*100,"%"
