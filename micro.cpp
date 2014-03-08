//Lab Batch 57 Team C
//MICROMOUSE

/*Order of check :
1)Memory
2)wall
*/

//up=0,left=1,down=2,right=3

//Solving of Algorithm based on Bellman-Ford Algorithm

#include<iostream>
#include<time.h>
#include<stdio.h>
#include<cstdlib>
#include"ezwin.h"

using namespace std;

typedef struct {int speed; int face;int curx;int cury;int mem[33][33]; }prop;

//Time delay function (Copied from www.dreamincode.net)
void delay(unsigned int mseconds){
	clock_t goal = mseconds + clock();
	while(goal>clock()){};
	}

//Rotation Function
int rotate(int face, int nxtface,int tr){
   
    if (face==nxtface)     {return face;}
    else if (nxtface==(face-1)%4 || nxtface==(face+1)%4)   {delay(tr); return nxtface;}
    else {face=(face+1)%4; delay(tr); return face;}
}


//dead end function
int dead_end(int u,int l,int d,int r){
	if (u+l+r+d >=3 ){
		return 1;}
	else return 0;}
	

//Main Function
int ApiMain()
{	prop m;
	char a[33][34]; 
	int i,j,cmd,mem_check,nxtstep,nxtface,avail_l,avail_d,avail_r,avail_u,junction[33][33],ts=50000,tr=8000,exe=0,stage=1,temp1,center_x,center_y;
	time_t start,lap1,lap2,lap3;
	double time1 , time2, time3;
//map initialaisation
   /* for(i=0;i<33;i++){
		for( j=0; j<33;j++){
			if(i%2==0 && j%2==0){
				 a[i][j] = '+';}
			else if(i%2==0 && j%2!=0){
					a[i][j] ='-';}
			else if(i%2!=0 && j%2==0)
					{a[i][j] ='|';}
			else if( i%2!=0 && j%2!=0){a[i][j] = ' ' ;}

		}}

	for(i=2;i<28;i=i+2){a[1][i]=' ' ;}
	for(i=2;i<20;i=i+2){a[9][i]=' ' ;}
	for(i=2;i<10;i=i+2){a[i][1]=' ' ;}
 	for(i=2;i<20;i=i+2){a[i][19]=' ' ;}
    for(i=16;i<20;i=i+2){a[19][i]=' ' ;}
    a[15][16]=' ';a[15][18]=' ';
    a[16][15]=' ';a[16][17]=' ';
    a[17][16]=' ';
    */
    FILE *mazegen;
    mazegen=fopen("maze_database.txt","r");
	system("c++ maze_generation.cpp");
	system("./a.out");
	

	//fscanf(mazegen,"%d %d ",&row,&col);
	for(i=0;i<33;i++){
		for(j=0;j<34;j++){
			fscanf(mazegen,"%c",&a[i][j]);
		}
	}
	
//mouse memory reset	
	for(i=0;i<33;i++){
		for( j=0; j<33;j++){
			m.mem[i][j]=0;
			junction[i][j]=0;
		}}

	m.curx=1;
	m.cury=1;
	a[1][1]= 'M';
	m.face = 3;
	m.mem[1][1] = 20;
//printing maze initially
	for(i=0;i<33;i++){
		for(j=0;j<33;j++){
			printf("%c",a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl<<m.face<<endl<<endl;
	time (&start);
//$$mouse itertation starts$$
	while(exe==0)
    {
    
//If comes to start position repeatedly than it concludes that maze is unsolvable.
	if(m.mem[1][1] >21&& stage==1){ 
	cout<<endl<<"Maze is Unsolvable"<<endl;
	exe =1;
	break;}
	
//Checking availibity of path by checking the walls & exploring walls in memory
	if(a[m.cury-1][m.curx] == ' '){m.mem[m.cury-1][m.curx]=0 ;avail_u = m.mem[m.cury-2][m.curx];}
	else {avail_u = 2000; m.mem[m.cury-1][m.curx]=1;}
	if(a[m.cury][m.curx+1] == ' '){m.mem[m.cury][m.curx+1]=0 ;avail_r = m.mem[m.cury][m.curx+2];}
	else {avail_r = 2000; m.mem[m.cury][m.curx+1]=1;}
	if(a[m.cury+1][m.curx] == ' '){m.mem[m.cury+1][m.curx]=0 ;avail_d = m.mem[m.cury+2][m.curx];}
	else {avail_d = 2000; m.mem[m.cury+1][m.curx]=1;}
	if(a[m.cury][m.curx-1] == ' '){m.mem[m.cury][m.curx-1]=0 ;avail_l = m.mem[m.cury][m.curx-2];}
	else {avail_l = 2000; m.mem[m.cury][m.curx-1]=1;}

//Center check
	if(stage ==1){
		if((avail_l<1000) && m.curx==19 &&(m.cury==15 || m.cury == 17)) avail_l =-1;
		if((avail_r<1000) && m.curx==13 &&(m.cury==15 || m.cury == 17)) avail_r =-1;
		if((avail_d<1000) && m.cury==13 &&(m.curx==15 || m.curx == 17)) avail_d =-1;
		if((avail_u<1000) && m.cury==19 &&(m.curx==15 || m.curx == 17)) avail_u =-1;
	}
//Minimum with prefernce of direction,
	nxtstep =avail_u;
	if(avail_l < nxtstep){nxtstep = avail_l;}
	if(avail_d < nxtstep){nxtstep = avail_d;}
	if(avail_r < nxtstep){nxtstep = avail_r;}

	if(avail_u == nxtstep) nxtface= 0;
	if(avail_l == nxtstep) nxtface= 1;	
	if(avail_d == nxtstep) nxtface= 2;
	if(avail_r == nxtstep) nxtface= 3;

	if(avail_u == nxtstep && m.face == 0) nxtface= 0;
	if(avail_l == nxtstep && m.face == 1) nxtface= 1;	
	if(avail_d == nxtstep && m.face == 2) nxtface= 2;
	if(avail_r == nxtstep && m.face == 3) nxtface= 3;

//Junction check

	if(m.mem[m.cury-1][m.curx]+m.mem[m.cury][m.curx+1]+m.mem[m.cury+1][m.curx]+m.mem[m.cury][m.curx-1]==2)
		{junction[m.cury][m.curx]=2;}
	else if(m.mem[m.cury-1][m.curx]+m.mem[m.cury][m.curx+1]+m.mem[m.cury+1][m.curx]+m.mem[m.cury][m.curx-1]==1)
		{junction[m.cury][m.curx]=3;}
	else if(m.mem[m.cury-1][m.curx]+m.mem[m.cury][m.curx+1]+m.mem[m.cury+1][m.curx]+m.mem[m.cury][m.curx-1]==0)
		{junction[m.cury][m.curx]=4;}
	else {junction[m.cury][m.curx]=0;}
//Dead End Check
	if(m.cury !=1 && m.curx !=1){temp1=dead_end(m.mem[m.cury-1][m.curx],m.mem[m.cury][m.curx-1],m.mem[m.cury+1][m.curx],m.mem[m.cury][m.curx+1]);}
	if(temp1==1)
		{m.mem[m.cury][m.curx]=1500;}
	if(((avail_l ==1500)||(avail_d==1500)||(avail_r==1500)||(avail_r ==1500)) && (junction[m.cury][m.curx]<3) && (m.cury!=1 || m.curx!=1))
		{ m.mem[m.cury][m.curx] =1500;}


//Exploration check

	if(stage ==2 && nxtstep!=0 ){
		exe =1;
		for(i=0;i<33;i++){
                   for(j=0;j<33;j++){
                          if(junction[i][j]==3 && m.mem[i][j]<2) {exe =0;}
                          if(junction[i][j]==4 && m.mem[i][j]<3) {exe =0;}
	}}}
    if(exe==1) break;//break if exploration is complete, therefore nxtface!=0, so dont move after it, jst check the condition

//Movement	
//Face rotation function calling in the loop
	while(m.face !=	nxtface)
	{m.face = rotate(m.face,nxtface,tr);
    

 
    
//print after rotation
	 for(i=0;i<33;i++){
		for(j=0;j<33;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	
    }
//Movement Mouse
	if(m.mem[m.cury][m.curx]!=1500)m.mem[m.cury][m.curx]++;
	delay(ts);
	if(m.face==0)     {a[m.cury-2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury-2;}
	else if(m.face==1){a[m.cury][m.curx-2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx-2;}
	else if(m.face==2){a[m.cury+2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury+2;}
	else if(m.face==3){a[m.cury][m.curx+2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx+2;} 




//printing for debugging
	for(i=0;i<33;i++){
		for(j=0;j<33;j++){
			printf("%c",a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl<<m.face<<endl<<endl;
//Stage change to 2
	if((m.curx==15 || m.curx == 17) && (m.cury == 15 || m.cury == 17) && stage==1)
	{ stage =2;
	  center_x=m.curx;
	  center_y=m.cury;
	  time(&lap1);
	  time1=difftime(lap1,start);
	  cout<<"Time to reach center initially : "<<time1<<endl;
	}

//m iteratin stops
}

time(&lap2);
time2=difftime(lap2,start);
cout<<"Time to explore entire maze : "<<time2<<endl;


//Flood-hill algorithm for finding shortest path

//Initialising the memory values to zero
	for(i=1;i<33;i=i+2){
		for( j=1; j<33;j=j+2){
			m.mem[i][j]=0;
		}}
    m.mem[center_y][center_x]=1;
    
 //printing for debugging
	for(i=0;i<33;i++){
		for(j=0;j<33;j++){
		cout<<m.mem[i][j];
		}
		cout<<endl;
	}
//Loop 1st increases the value of already flooded cell by 1 and then flood available neighbour by 1.    
       while(m.mem[1][1]!=1){
           for(i=1;i<33;i=i+2){
		     for( j=1; j<33;j=j+2){
              if(m.mem[i][j]!=0)m.mem[i][j]++;}}
           for(i=1;i<33;i=i+2){
	         for( j=1; j<33;j=j+2){
                if(m.mem[i][j]==2){
                     if(m.mem[i-1][j]==0&&m.mem[i-2][j]==0){m.mem[i-2][j]++;}
                     if(m.mem[i+1][j]==0&&m.mem[i+2][j]==0){m.mem[i+2][j]++;} 
                     if(m.mem[i][j-1]==0&&m.mem[i][j-2]==0){m.mem[i][j-2]++;} 
                     if(m.mem[i][j+1]==0&&m.mem[i][j+2]==0){m.mem[i][j+2]++;}   
                     }}}}     
 //printing for debugging
       	for(i=0;i<33;i++){
	     	for(j=0;j<33;j++){
	        	cout<<m.mem[i][j];
		  }
		cout<<endl;
      	}  


        exe=0;
        a[m.cury][m.curx]=' ';
        m.curx=1;
        m.cury=1;
        a[1][1]='M';
        m.face=3;
//printing for debugging
    	for(i=0;i<33;i++){
	     	for(j=0;j<33;j++){
			    printf("%c",a[i][j]);
		    }
		    cout<<endl;
        }
	    cout<<endl<<m.face<<endl<<endl;
//Final Run
        while(exe==0){
//check availability of wall                            
        if(m.mem[m.cury-1][m.curx]==0){ avail_u = m.mem[m.cury-2][m.curx];}
        else {avail_u = -1;} 
        if(m.mem[m.cury+1][m.curx]==0){ avail_d = m.mem[m.cury+2][m.curx];}
        else {avail_d = -1;}
        if(m.mem[m.cury][m.curx-1]==0){ avail_l = m.mem[m.cury][m.curx-2];}
        else {avail_l = -1;} 
        if(m.mem[m.cury][m.curx+1]==0){ avail_r = m.mem[m.cury][m.curx+2];}
        else {avail_r = -1;} 
//take max of avail.. to decide nxtstep

       nxtstep=avail_u;
       if(avail_d>nxtstep) {nxtstep=avail_d;}
       if(avail_r>nxtstep) {nxtstep=avail_r;}
       if(avail_l>nxtstep) {nxtstep=avail_l;}
//Decide nxtface using nxtstep
         if(avail_u == nxtstep) nxtface= 0;
         if(avail_l == nxtstep) nxtface= 1;	
         if(avail_d == nxtstep) nxtface= 2;
         if(avail_r == nxtstep) nxtface= 3;
//Prefer existing face, do not change face if maximum already in that direction
         if(avail_u == nxtstep && m.face==0) nxtface= 0;
         if(avail_l == nxtstep && m.face==1) nxtface= 1;	
         if(avail_d == nxtstep && m.face==2) nxtface= 2;
         if(avail_r == nxtstep && m.face==3) nxtface= 3;
         
         
//Movement	
//Face rotation function calling in the loop
	while(m.face !=	nxtface){
	 m.face = rotate(m.face,nxtface,tr);
    

 
    
//print after rotation
	 for(i=0;i<33;i++){
		for(j=0;j<33;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	
    }
//Movement Mouse
	delay(ts);
	if(m.face==0)     {a[m.cury-2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury-2;}
	else if(m.face==1){a[m.cury][m.curx-2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx-2;}
	else if(m.face==2){a[m.cury+2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury+2;}
	else if(m.face==3){a[m.cury][m.curx+2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx+2;} 
                     
	if((m.curx==15 || m.curx == 17) && (m.cury == 15 || m.cury == 17))
	{ exe=1;
	  time(&lap3);
	  time3=difftime(lap3,lap2);
	  cout<<"Time to reach center finally : "<<time3<<endl;
	}
	
	a[15][15]='G';
    
    for(i=0;i<33;i++){
		for(j=0;j<33;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	
    
    }
    cin>>i;
	return 0;
}
