//sg
#include<iostream>
#include<fstream>
using namespace std;
class ReadArray
{
	int i,len;
	char * fn;
	int factor;
	fstream f;
	public:
	double arr[5000];
	ReadArray(char * fn,int factor)
	{
		this->fn=fn;
		i=0;
		this->factor=factor;
		f.open(fn,ios::in);
		if(!f)
		{
			cout<<"Error!";
			return;
		}
		fillArray();
	}
	ReadArray()
	{
		i=0;
		
		fillZeroes();
	}
	void fillZeroes()
	{
		while(i<2500)
		{
			arr[i]=0;
			i++;
		}
		len=i-1;
	}
	void fillArray()
	{
		while(i<2500)
		{
			f>>arr[i];
			arr[i]*=factor;
			i++;
		}
		len=i-1;
	}
	void printArr(char * d)
	{
		fstream f(d,ios::out);
		for(int i=0;i<len;i++)
		f<<arr[i]<<"\n";
	}
	static ReadArray * diff(ReadArray& r1,ReadArray& r2)
	{
		ReadArray * temp=new ReadArray();
		for(int i=0;i<2500;i++)
		{
			temp->arr[i]=r1.arr[i]-r2.arr[i];
		}
		return temp;
	}
};
int main()
{
	cout<<"sg";
	ReadArray s("/home/aman/arr/sumn/sigs_arr.txt",1),d("/home/aman/arr/sumn/sigd_arr.txt",2),t("/home/aman/arr/sumn/sigt_arr.txt",3),q("/home/aman/arr/sumn/sigq_arr.txt",4);
	ReadArray *diff1=ReadArray::diff(q,s);
	diff1->printArr("dump.txt");
	
}
