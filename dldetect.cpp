#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int n; //number of process 
int m; //type of resource
int avail[100];
int alloc[100][100];
int req[100][100];
int work[100];
bool finish[100];
int dl[100];//array to store deadlocked processes
int i,j,flag,a;

void dldetect()
{
  for(i=0; i<n; i++)
    {
      finish[i]=false;
    }
  
  for(j=0; j<m; j++)
    {
      work[j]=avail[j];
    }
  
  //if alloc[][]={0,0,...,0}, set to true
  for(i=0; i<n; i++)
    {
      int count=0;
      for(j=0;j<m;j++)
	{
	  if(alloc[i][j]==0)
	    {
	      count++;
	    }
	}
      if(count==m)
	{
	  finish[i]=true;
	}
    }
  
  int k =n;//used in do loop
  do
    {
      for(i=0; i<n; i++)
	{
	  if(finish[i]==false)
	    {
	      flag=1;
	    }
	  for(j=0;j<m;j++)
	    {
	      if(req[i][j]>work[j])
		{
		  flag=0;
		}
	    }
	  if(flag==1)//find processes which finish[]==false AND req[][]<=work
	    {
	      finish[i]=true;//update process
	    
	      for(j=0; j<m; j++)
		{
		  work[j]=work[j]+alloc[i][j];//update work[]
		  avail[j]=work[j];
		    }
	    }
	}
      k--;}
    while(k>0);
}

int main(int argc, char* argv[])
{
  string infile = "";
  if( argc > 1 )
    {
      infile = argv[1];
    }
  else
    {
      cout << "Usage: ./cppfile inputfile" << endl;
      return 1;
    }
  // get inpute file
  ifstream file(infile);
  if( file.is_open() )
    {
      file >> n >> m;
      for(i=0; i<m; i++)
	{
	  file >> avail[i];
	}
      
      for(i=0; i<n; i++)
	for(j=0; j<m; j++)
	  {
	    file >> alloc[i][j];
	  }
      
      for(i=0; i<n; i++)
	for(j=0; j<m; j++)
	  {
	    file >> req[i][j];
	  }
      file.close();
    }
  
  dldetect();//deadlock detection algorithm
  
  flag=1;
  for(i=0; i<n; i++)
    {
      if(finish[i]==false)
	{
	  flag=0;
	  dl[a++]=i;//store deadlocked processes
	}
    }
  if(flag==0)
    {
      cout<<"These processes are deadlocked:";
      for(i=0; i<a; i++)
	{
	  cout<< dl[i] << ".";
	  
	}
      cout << endl;
    }
  else
    {
      cout<<"The system is not deadlocked."<< endl;
    }
  return 0;
}
