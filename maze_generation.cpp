//Lab batch 57-A
/*references 
            cplusplus.com
            cohoon and davidson
            google.com
            wikipedia
                                     */ 
                                     

/*****************************************************************
 * C++ Headers
 *****************************************************************/
                                     

#include <stdlib.h>
#include <time.h>
#include<iostream>
#include<cstdio>
using namespace std;



unsigned int j=time(NULL);


/*****************************************************************
 *Function prototypes
 *****************************************************************/

 
//direction function
int dir();

//position of block to be closed
int closingblock(int row,int col); 


//index of the wall to be dismantled b/w two neighbouring blocks
void wall_index(int prow,int pcol,int crow,int ccol,int *row,int *col);
 
 
//getting position from coordinates. 
int get_pos(int cur_row,int cur_col,int tot_col);

//Getting co-ordinates from the position	
int rev_pos(int pos,int *cur_row,int *cur_col,int tot_col);

//find goal, given number of rows and columns
void find_end(int *row,int *col);




/*****************************************************************

 Main Function
 *****************************************************************/
int main()
{
	FILE *out,*in;
	out=fopen("maze_database.txt","w");
	int i,k;
	int row,col,c_row,c_col,w_row,w_col,sr,sc;
	float top_spd, acc,brake, ang_spd_t;
 	
 	
 	//Taking inputs from the user
 	cout<<"Enter no. of rows : ";
 	cin>>row;  cout<<endl;
 	c_row=row;
 	cout<<"Enter no.of columns : ";
 	cin>>col;
 	c_col=col;
 	cout<<"Enter Acceleration(in cm/[s*s]) : ";
 	cin>>acc;
 	acc/=100;
 	cout<<"Enter Brake Power(deceleration in cm/[s*s]) : ";
 	cin>>brake;
 	brake/=100;
 	cout<<"Enter Top Speed(in cm/s) : ";
 	cin>>top_spd;
 	top_spd/=100;
 	cout<<"Enter Angular Speed(time taken to complete round rotation in millisec) : ";
 	cin>>ang_spd_t;
 	ang_spd_t/=1000;
 	
 	//database of maze in grid form
	int maze_out[2*row+1][2*col+1];
	
	//database of maze  in numeric form
	int maze[row+2][col+2];	
	
	//starting row,col
        sr=1;sc=1;
        
        //making maze grid
        
        //    - Suppose we have 5 rows and 8 columns ...
        // then the grid looks like...
// 
//       +-+-+-+-+-+-+-+-+
//       | | | | | | | | |
//       +-+-+-+-+-+-+-+-+
//       | | | | | | | | |
//       +-+-+-+-+-+-+-+-+
//       | | | | | | | | |
//       +-+-+-+-+-+-+-+-+
//       | | | | | | | | |
//       +-+-+-+-+-+-+-+-+
//       | | | | | | | | |
//       +-+-+-+-+-+-+-+-+
        
	for(i=0;i<2*row+1;i++){
		for(k=0;k<2*col+1;k++){
			if(i%2==0 && k%2==0){
				maze_out[i][k]='+';
			}
			if(i%2!=0 && k%2!=0){
				maze_out[i][k]=' ';
			}
			if(i%2==0 && k%2!=0){
				maze_out[i][k]='-';
			}
			if(i%2!=0 && k%2==0){
				maze_out[i][k]='|';
			}
		}
	}
        
        
        
        //making maze in numeric form
        for(int index1=0; index1<row+2 ; index1++){		
                for( int index2=0;index2<col+2;index2++){	
                        maze[index1][index2]=1;
		}
	}
       for(int index1=0 ; index1<(row+2) ; index1+=(row+1)){
                for( int index2=0;index2<(col+2);index2++){	
                        maze[index1][index2] = 0;
                    }
        }
        for(int index1=0 ; index1<(col+2) ; index1+=(col+1)){
                for( int index2=0;index2<(row+2);index2++){
                        maze[index2][index1] = 0;
                    }
	}
	
	
	//randomly closing all the boundaries of particular block
	for(int k=0;k<=(row)*(col);k++)
        {
                int count=0;
        	int r1=row;
        	int c1=col;
        	rev_pos(closingblock(row,col),&r1,&c1,col);
        	 for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(maze[r1+i][c1+j]==1)
			count++;
		}
	       }
         if(count==9)	maze[r1][c1]=4;      	
         }
	
	
	int ppos=get_pos(sr,sc,row);//present position
	int prow=sr;//present row
	int pcol=sc;//present col
	int dirt; //variable store direction
	int lpos=0;//last position
	int nrow;//new row;
	int ncol;//new col;

	maze[sr][sc]=2;

	find_end(&c_row,&c_col);
        maze[c_row][c_col]=1;
        
        int nr,nc;
        
	int goalpos=get_pos(c_row,c_col-1,col);      
		
	//randomly removing the walls to reach the goal
	while(ppos!=goalpos){
	        
	        //storing previous direction
	        
	        
	        //randomly getting direction
	        dirt=dir();
	        
	       
	        
	        //changing co-ordinates on basis of random direction
		switch(dirt){
		
			case 0:
			nrow=prow-1;
			ncol=pcol;
			break;
			
			case 1:
			ncol=pcol-1;
			nrow=prow;
			break;
		
			case 2:		
			nrow=prow+1;
			ncol=pcol;
			break;
	
			case 3:
			ncol=pcol+1;
			nrow=prow;
			break;		
		}
		
                
                //main algorithm  
		if((maze[nrow][ncol]!=0)&&(maze[nrow][ncol]!=4)){
			if((get_pos(nrow,ncol,col)!=lpos)){
				maze[nrow][ncol]=2;
				wall_index(prow,pcol,nrow,ncol,&w_row,&w_col);
				maze_out[w_row][w_col]=' ';				
				lpos=ppos;
				ppos=get_pos(nrow,ncol,col);
				prow=nrow;
				pcol=ncol;
				  }
					
                 }
                
  }
               
	maze[c_row][c_col]=5;     //random value
	            
	//making boundaries around goal
	if(row%2==0 && col%2==0){
	 wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
         maze_out[nr][nc]=' ';maze[c_row+1][c_col]=5;
         wall_index(c_row,c_col,c_row,c_col+1,&nr,&nc);
         maze_out[nr][nc]=' ';maze[c_row][c_col+1]=5;
         wall_index(c_row+1,c_col,c_row+1,c_col+1,&nr,&nc);
         maze_out[nr][nc]=' ';maze[c_row+1][c_col+1]=5;
	 wall_index(c_row,c_col+1,c_row+1,c_col+1,&nr,&nc);
         maze_out[nr][nc]=' ';
         wall_index(c_row+1,c_col,c_row+1,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col+1,c_row-1,c_col+1,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row+1,c_col+1,c_row+1,c_col+2,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col+1,c_row,c_col+2,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row+1,c_col,c_row+2,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row+1,c_col+1,c_row+2,c_col+1,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col,c_row-1,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
         
         }
        else if(row%2==0 && col%2!=0){
        wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
        maze_out[nr][nc]=' ';maze[c_row+1][c_col]=5;
        wall_index(c_row,c_col,c_row,c_col+1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row+1,c_col,c_row+2,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row+1,c_col,c_row+1,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row+1,c_col,c_row+1,c_col+1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col,c_row-1,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
        }
        else if(row%2!=0 && col%2==0){
        wall_index(c_row,c_col,c_row,c_col+1,&nr,&nc);
        maze_out[nr][nc]=' ';maze[c_row][c_col+1]=5;
        wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row,c_col+1,c_row,c_col+2,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col+1,c_row-1,c_col+1,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row,c_col+1,c_row+1,c_col+1,&nr,&nc);
         maze_out[nr][nc]='-';
         wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col,c_row-1,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
        }
        else if(row%2!=0 && col%2!=0){
        wall_index(c_row,c_col,c_row,c_col+1,&nr,&nc);
        maze_out[nr][nc]='|';
        wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
        maze_out[nr][nc]='-';
        wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         maze_out[nr][nc]='|';
         wall_index(c_row,c_col,c_row-1,c_col,&nr,&nc);
         maze_out[nr][nc]='-';
        }
       
       	
         	//knocking down walls  of the the block not been visited
         	for(prow=1;prow<row+1;prow++){
         	for(pcol=1;pcol<col+1;pcol++){
         		
	         	if(maze[prow][pcol]==4 ||maze[prow][pcol]==1){
	         	
                                //int k=9;
	         		for(int i=maze[prow][pcol]/4;i<=1;){
	         			int dirn=dir();
					switch(dirn){
						case 0:
						nrow=prow-1;
						ncol=pcol;
						break;
							
						case 1:
						ncol=pcol-1;
						nrow=prow;
						break;
					
						case 2:				
					
						nrow=prow+1;
						ncol=pcol;
						break;
				
						case 3:
						ncol=pcol+1;
						nrow=prow;
						break;		
					}
					if((maze[nrow][ncol]!=0)&&(maze[nrow][ncol]!=5)){
				//		if(k!=dirn)
						{
						wall_index(prow,pcol,nrow,ncol,&w_row,&w_col);
						maze_out[w_row][w_col]=' ';i++;
						}
				//		k=dirn;
						
					}
						
						

					
	         		}
		         }
		  }
	}
	
	
	//removing corners if no walls are present around it
	for(i=1;i<row;i++){
         	for(j=1;j<col;j++){
         		if(maze_out[2*i-1][2*j]==' ' && maze_out[2*i+1][2*j]==' ' && maze_out[2*i][2*j-1]==' ' && maze_out[2*i][2*j+1]==' ')
         			{maze_out[2*i][2*j]=' ';}}}
	
	
	
	//opening atleast one wall for the goal
	wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         maze_out[nr][nc]=' ';
			
         
         //showing start and goal in grid form
                  maze_out[2*c_row-1][2*c_col-1]='G';
                  maze_out[2*sr-1][2*sc-1]='S';
                  
                  
                  
       // printing the maze database to a file           
	fprintf(out,"%d %d ",row,col);
	fprintf(out,"%f %f %f %f ",acc,brake,top_spd,ang_spd_t);
	for(i=0;i<2*row+1;i++){
		for(k=0;k<2*col+1;k++){
			fprintf(out,"%c",maze_out[i][k]);
		}
		fprintf(out,"\n");
	}
	
	fclose(out);
	return 0;
}


/*****************************************************************
 *Functions
 *****************************************************************/



     
//direction function
int dir(){
	int random;
	srand(j);	  /* initialize random seed: */
	random = rand() %4;  /* generate random number: */
	j+=random*random+1;//changing seed value

   	return random;

}


//position of block to be closed
int closingblock(int row,int col){
	int random;
	srand(j);	// initialize random seed: 
	random = (rand() %(row*col))+1;  // generate random number: 
	j+=random*random+1;//changing seed value

   	return random;
}


//index of the wall to be dismantled b/w two neighbouring blocks
void wall_index(int prow,int pcol,int crow,int ccol,int *row,int *col){
	*row=((2*prow-1)+(2*crow-1))/2;
	*col=((2*pcol-1)+(2*ccol-1))/2;
	}
	
//getting position from coordinates. 
int get_pos(int cur_row,int cur_col,int tot_col){
	return (cur_row-1)*tot_col+cur_col;
}
//Getting co-ordinates from the position	
int rev_pos(int pos,int *cur_row,int *cur_col,int tot_col){
	*cur_row=pos/tot_col+1;
	*cur_col=pos%tot_col;
}

//find goal, given number of rows and columns
void find_end(int *row,int *col){
	if(*row%2==0 && *col%2==0){
		*row=*row/2;
		*col=*col/2;
	}
	else if(*row%2!=0 && *col%2!=0){
		*row=*row/2+1;
		*col=*col/2+1;
	}
	else if(*row%2!=0 && *col%2==0){
		*row=*row/2+1;
		*col=*col/2;
	}
	else if(*row%2==0 && *col!=0){
		*row=*row/2;
		*col=*col/2+1;
	}
}


