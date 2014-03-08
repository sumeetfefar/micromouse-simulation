//Lab Batch 57 Team C
//MICROMOUSE

/*Order of check :
1)Memory
2)wall
*/

//up=0,left=1,down=2,right=3

//Solving of Algorithm based on Bellman-Ford Algorithm Theory

#include<iostream>
#include<time.h>
#include<stdio.h>
#include<cstdlib>
#include"ezwin.h"
#include<math.h>
FILE *maze_move;

using namespace std;

typedef struct {float speed; int face;int curx;int cury;int mem[100][100]; }prop;


//Rotation Function
int rotate(int face, int nxtface,int tr,int *t){
   
    if (face==nxtface)     {return face;}
    else if (nxtface==(face-1)%4 || nxtface==(face+1)%4)   {*t=1; return nxtface;}
    else {face=(face+1)%4; *t=1; return face;}
}


//dead end function
int dead_end(int u,int l,int d,int r){
	if (u+l+r+d >=3 ){
		return 1;}
	else return 0;}
	

//Main Function
int ApiMain()
{	prop m;
	int i,j,cmd,mem_check,nxtstep,nxtface,avail_l,avail_d,avail_r,avail_u,ts,tr,exe=0,stage=1,temp1,center_x,center_y,delay_rot,ideal_t;
	int col,row,n1,n2,m1,m2 ;
	int signal=0;
	float top_spd, acc,brake, brk_stp_spd,ang_spd_t;		
	//signal=0;


	
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

	maze_move=fopen("gui_out.txt","w");
	
	FILE *mazegen;
	mazegen=fopen("maze_database.txt","r");
	system("g++ -o maze_generation maze_generation.cpp -I ../EzWindows/include -L/usr/X11R6/lib -lX11 -L../EzWindows/lib -lezwin ");
	system("./maze_generation");
		fscanf(mazegen,"%d %d ",&row,&col);
		fscanf(mazegen,"%f %f %f %f ",&acc,&brake,&top_spd,&ang_spd_t);		
		char a[2*row+1][2*col+2]; 
		int junction[2*row+1][2*col+1];
	for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+2;j++){
			fscanf(mazegen,"%c",&a[i][j]);
		}
	}
											
//Speed Conversion
	top_spd/=180*1000;//converting top speed into time taken to move a block in that speed
	
	brk_stp_spd=sqrt(2*brake*180/1000);
	brk_stp_spd/=180*1000;
	

//Speed Calculation part
	m.speed=0;
	if(top_spd<brk_stp_spd){top_spd=brk_stp_spd;}
	tr= ang_spd_t/4*1000*1000;
	

	
//mouse memory reset	
	for(i=0;i<2*row+1;i++){
		for( j=0; j<2*col+1;j++){
			m.mem[i][j]=0;
			junction[i][j]=0;
		}}
    //m1,m2,r rows, got to be input
    //n1,n2, c coloumns, got to be input
	m.curx=1;
	m.cury=1;
	a[1][1]= 'M';
	m.face = 3;
	m.mem[1][1] = 10;
	
	if(col%2==0){n1=col-1;n2=col+1;}
	else{n1=col;n2=col;}
	
	if(row%2==0){m1=row-1;m2=row+1;}
	else{m1=row;m2=row;}
	
//printing maze initially
	fprintf(maze_move,"%d %d %d %d %d 0\n",m.cury,m.curx,m.face,stage,signal);
	signal++;
	/*for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			printf("%c",a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl<<m.face<<endl<<endl;*/

//$$4MOUSE ITERATION STARTS$$
	while(exe==0)    {
    	
//If comes to start position repeatedly than it concludes that maze is unsolvable.
	if(m.mem[1][1] >20&& stage==1){ 
	cout<<endl<<"Maze is Unsolvable"<<endl;
	exe =1;
	stage=0;
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
		if((avail_l<1000) && m.curx==(n2+2) &&(m.cury==m1 || m.cury == m2)) avail_l =-1;
		if((avail_r<1000) && m.curx==(n1-2) &&(m.cury==m1 || m.cury == m2)) avail_r =-1;
		if((avail_d<1000) && m.cury==(m1-2) &&(m.curx==n1 || m.curx == n2)) avail_d =-1;
		if((avail_u<1000) && m.cury==(m2+2) &&(m.curx==n1 || m.curx == n2)) avail_u =-1;
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
		for(i=0;i<2*row+1;i++){
                   for(j=0;j<2*col+1;j++){
                          if(junction[i][j]==3 && m.mem[i][j]<2) {exe =0;}
                          if(junction[i][j]==4 && m.mem[i][j]<3) {exe =0;}
	}}}
    if(exe==1) break;//break if exploration is complete, therefore nxtface!=0, so dont move after it, jst check the condition

//Movement	
//Face rotation function calling in the loop
	delay_rot=0;
	while(m.face !=	nxtface)
	{m.face = rotate(m.face,nxtface,tr,&delay_rot);
    

 //If turn is taken then speed is zero, so reaccelerates
	if(delay_rot==1){m.speed=0;}    
//print after rotation
	if(delay_rot==1)fprintf(maze_move,"%d %d %d %d %d %d\n",m.cury,m.curx,m.face,stage,signal,tr);
	else if(delay_rot==0)fprintf(maze_move,"%d %d %d %d %d 0\n",m.cury,m.curx,m.face,stage,signal);
	signal++;
	 /*for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	
    */}
    
//Mouse Speed Calculation
	m.speed=sqrt(2*acc*180/1000+m.speed*m.speed);
	ts=180*1000/m.speed;
	if(ts<top_spd){ts=top_spd;}

//Movement Mouse
	if(m.mem[m.cury][m.curx]!=1500)m.mem[m.cury][m.curx]++;
	if(m.face==0)     {a[m.cury-2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury-2;}
	else if(m.face==1){a[m.cury][m.curx-2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx-2;}
	else if(m.face==2){a[m.cury+2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury+2;}
	else if(m.face==3){a[m.cury][m.curx+2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx+2;} 




//printing after movement
	fprintf(maze_move,"%d %d %d %d %d %d\n",m.cury,m.curx,m.face,stage,signal,ts);
	signal++;
	/*for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			printf("%c",a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl<<m.face<<endl<<endl;*/
//Stage change to 2
	if((m.curx==n1 || m.curx == n2) && (m.cury == m1 || m.cury == m2) && stage==1)
	{ stage =2;
	  center_x=m.curx;
	  center_y=m.cury;
	  
	}

//m iteratin stops
}

	
	m.speed=0;
//Flood-hill algorithm for finding shortest path
	stage=3;
//Initialising the memory values to zero
	for(i=1;i<2*row+1;i=i+2){
		for( j=1; j<2*col+1;j=j+2){
			m.mem[i][j]=0;
		}}
    m.mem[center_y][center_x]=1;
    
 //printing for debugging
	/*for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
		cout<<m.mem[i][j];
		}
		cout<<endl;
	}*/
//Loop 1st increases the value of already flooded cell by 1 and then flood available neighbour by 1.    
       while(m.mem[1][1]!=1){
           for(i=1;i<2*row+1;i=i+2){
		     for( j=1; j<2*col+1;j=j+2){
              if(m.mem[i][j]!=0)m.mem[i][j]++;}}
           for(i=1;i<2*row+1;i=i+2){
	         for( j=1; j<2*col+1;j=j+2){
                if(m.mem[i][j]==2){
                     if(m.mem[i-1][j]==0&&m.mem[i-2][j]==0){m.mem[i-2][j]++;}
                     if(m.mem[i+1][j]==0&&m.mem[i+2][j]==0){m.mem[i+2][j]++;} 
                     if(m.mem[i][j-1]==0&&m.mem[i][j-2]==0){m.mem[i][j-2]++;} 
                     if(m.mem[i][j+1]==0&&m.mem[i][j+2]==0){m.mem[i][j+2]++;}   
                     }}}}     
 //printing for debugging
 	for(i=0;i<2*row+1;i++){
	     	for(j=0;j<2*col+1;j++){
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
        m.speed=0;
//printing for debugging
	fprintf(maze_move,"%d %d %d %d %d 0\n",m.cury,m.curx,m.face,stage,signal);
	signal++;
    	/*for(i=0;i<2*row+1;i++){
	     	for(j=0;j<2*col+1;j++){
			    printf("%c",a[i][j]);
		    }
		    cout<<endl;
        }
	    cout<<endl<<m.face<<endl<<endl;
	    */
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
	delay_rot=0;
	while(m.face !=	nxtface){
	 m.face = rotate(m.face,nxtface,tr,&delay_rot);
    

 
	if(delay_rot==1){m.speed=0;}
//print after rotation
	if(stage==3){	
	if(delay_rot==1)fprintf(maze_move,"%d %d %d %d %d %d\n",m.cury,m.curx,m.face,stage,signal,tr);
	else if(delay_rot==0)fprintf(maze_move,"%d %d %d %d %d 0\n",m.cury,m.curx,m.face,stage,signal);}

	if(stage==4 && delay_rot==1){ideal_t+=tr;}
	
	signal++;
	 /*for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	*/
    }
   
//Mouse Speed Calculation
	m.speed=sqrt(2*acc*180/1000+m.speed*m.speed);
	ts=180*1000/m.speed;
	if(ts<top_spd){ts=top_spd;}

//Movement Mouse

	if(m.face==0)     {a[m.cury-2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury-2;}
	else if(m.face==1){a[m.cury][m.curx-2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx-2;}
	else if(m.face==2){a[m.cury+2][m.curx]='M'; a[m.cury][m.curx]=' '; m.cury=m.cury+2;}
	else if(m.face==3){a[m.cury][m.curx+2]='M'; a[m.cury][m.curx]=' '; m.curx=m.curx+2;} 
//Checking condition of termination
	if((m.curx==n1 || m.curx == n2) && (m.cury == m1 || m.cury == m2)){
		  if(stage==5){ideal_t=ideal_t+ts;
	  		fprintf(maze_move,"0 0 0 5 %d %d\n",signal,ideal_t);
	  		break;}
	}                    
	if((m.curx==n1 || m.curx == n2) && (m.cury == m1 || m.cury == m2))
	{ stage++;
	  if(stage==4){
	  fprintf(maze_move,"%d %d %d %d %d %d\n",m.cury,m.curx,m.face,stage,signal,ts);
	  fprintf(maze_move,"%d %d %d %d %d 0\n",m.cury,m.curx,m.face,stage,signal);
	top_spd=3.1;
	acc=10.1;
	brake=14.1;
	ang_spd_t=0.2;
  //Speed Conversion
	top_spd/=180*1000;//converting top speed into time taken to move a block in that speed
	
	brk_stp_spd=sqrt(2*brake*180/1000);
	brk_stp_spd/=180*1000;
	

  //Speed Calculation part
	m.speed=0;
	if(top_spd<brk_stp_spd){top_spd=brk_stp_spd;}
	tr= ang_spd_t/4*1000*1000;
	a[m.cury][m.curx]=' ';
	
	m.curx=1;
	m.cury=1;
	a[1][1]='M';
	m.face=3;
	ideal_t=-ts;
	  }}
		


//Printing for debugging
	if(stage==3)fprintf(maze_move,"%d %d %d %d %d %d\n",m.cury,m.curx,m.face,stage,signal,ts);
	if(stage==4){ideal_t+=ts;}

	signal++;
	cout<<ideal_t<<endl;	 
 /*   for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			printf("%c",a[i][j]);
		} 
		cout<<endl;}
	
	cout<<endl<<m.face<<endl<<endl;	
    */
    }	
    	//fprintf(maze_move,"0 0 0 0 0 0  \n");
    	cout<<ideal_t<<endl;;
    	fclose(maze_move);
    	fclose(mazegen);
  	return 0;
}
