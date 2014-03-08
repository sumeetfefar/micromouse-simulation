//Program to Multiply Two Matrices
#include<iostream>
using namespace std;
/*
The following two lines define constants or MACROS which define the maximum 
number of rows and columns in a matrix that the program can handle.
*/
#define MAXROWS 50
#define MAXCOLS 50
//Prototypes of the functions
int giveinput(char a[][MAXCOLS],int m,int n);
int multiply(char a[][MAXCOLS],char b[][MAXCOLS],char c[][MAXCOLS],int m,int n,int 
p);
int printoutput(char c[][MAXCOLS],int m,int p);// of matrix
int main()
{
int nrows,ncols,mrows,mcols;
char a[MAXROWS][MAXCOLS], b[MAXROWS][MAXCOLS], c[MAXROWS][MAXCOLS];
cout<<"How many rows in the first matrix?  ";
cin>>nrows;
cout<<"How many cols in the first matrix?  ";
cin>>ncols;
cout<<"How many rows in the second matrix?  ";
cin>>mrows;
cout<<"How many cols in the second matrix?  ";
cin>>mcols;
//The product cannot be defined if number of columns in first matrix
//is not same as number of rows in other matrix
if (ncols != mrows) 
{
cout<<"The product of these matrices is not defined."<<endl;
return 0;
}
cout<<"Enter first matrix:\n";
giveinput(a,nrows,ncols);
cout<<"Enter second table:\n";
giveinput(b,mrows,mcols);
multiply(a,b,c,nrows,ncols,mcols);
cout<<"Product of the matrices is:\n";
printoutput(c,nrows,mcols);
return 0;
}
int giveinput(char a[][MAXCOLS],int m,int n)
{
int row,col;
for (row=0;row<m;row++)
{
cout<<"Enter data for row no."<<row+1<<"\n";
for (col=0;col<n;col++)
cin>>a[row][col];
}
return 0;
}
int multiply(char a[][MAXCOLS],char b[][MAXCOLS],char c[][MAXCOLS],int m,int n,int 
p)
{
int i,j,k,sum=0;
for (i=0;i<m;i++)
{
for (j=0;j<p;j++)
{
c[i][j]=0;
for (k=0;k<n;k++)
c[i][j]+=(a[i][k]*b[k][j]);
}
}
return 0;
}
int printoutput(char c[][MAXCOLS],int m,int p)
{
int row,col;
for (row=0;row<m;row++)
{
for (col=0;col<p;col++)
{
cout<<c[row][col]<<" ";
}
cout<<endl;
}
return 0;
}
