#include<iostream>
#include<cstdio>
#include<cstdlib>
#include "bitmap.h"
#include <assert.h>
#include <ctime>
#include <cstring>
#include "circle.h"
#include <sys/time.h>
#include <unistd.h>

#include "rect.h"
#include "label.h"
#include <cmath>
#include "ezwin.h"
#include <cassert>
#define SCALE 1

using namespace std;

SimpleWindow m("Micromouse simulation",25,15,Position(1.0,0.0));
SimpleWindow s("Micromouse :: Select the shape and color ",10,7,Position(5.0,5.0));
color Mouse=Green,Face;

float time_u(struct timeval end,struct timeval start)
{
    float mtime, seconds, useconds;    

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0)*1000;

    return mtime;
}

int get_color(const Position &P){
	if(P.GetXDistance()>1.5&&P.GetXDistance()<1.0&&P.GetYDistance()>1.0&&P.GetYDistance()<1.7) 
               Mouse=Blue;
        if(P.GetXDistance()>2.3&&P.GetXDistance()<3.0&&P.GetYDistance()>1.0&&P.GetYDistance()<1.7) 
               Mouse=Black;
        if(P.GetXDistance()>1.5&&P.GetXDistance()<2.2&&P.GetYDistance()>1.8&&P.GetYDistance()<2.5)
               Mouse=Red;
        if(P.GetXDistance()>3.1&&P.GetXDistance()<3.8&&P.GetYDistance()>1.0&&P.GetYDistance()<1.7) 
               Mouse=Yellow;
         return 1;
}

string ftos(float x);
//Copied from www.dreamincode.net	
void delay(unsigned int mseconds){
	clock_t goal = mseconds + clock();
	while(goal>clock()){};
	}	

int ApiMain(){
	struct timeval start,lap1,lap2,lap3;
	float time1,time2,time3;
	FILE *mazegen;
	FILE *mazemove;
	float top_spd, acc,brake, brk_stp_spd,ang_spd_t;
	mazemove=fopen("gui_out.txt","r");
	mazegen=fopen("maze_database.txt","r");
	//mazepar=fopen("maze_parameters.txt","w");
	int row,col,i,j;
	//cout<<"Give no. of rows :";cin>>row;
	//cout<<"Give no. of columns :";cin>>col;
	//fprintf(mazepar,"%d %d ",row,col);
	

	system("g++ -o micro_new micro_new.cpp -I ../EzWindows/include -L/usr/X11R6/lib -lX11 -L../EzWindows/lib -lezwin");
	system("./micro_new");
	
	int code;
	cout<<"Enter 1 to start the simulation of micromouse\n";
	cout<<"Enter 0 to quit \n ";
	cin>>code;
	if(code==1){
	
	m.Open();

	int x_n,y_n,face_n,stage_n,signal_n,x_p,y_p,face_p,stage_p=0,signal_p,count,del;
	float time_n,time_p;
	int sr,sc;

	fscanf(mazegen,"%d %d ",&row,&col);
	fscanf(mazegen,"%f %f %f %f ",&acc,&brake,&top_spd,&ang_spd_t);
	char maze[2*row+1][col*2+1];
	for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+2;j++){
			fscanf(mazegen,"%c",&maze[i][j]);
			
		}
	}
	
	int max=row<col?col:row;
		
				m.RenderText(Position(16.0,3.0),Position(24.0,5.0),"MICROMOUSE", Blue);
				m.RenderText(Position(16.0,4.5),Position(24.0,6.0),"   Status:", Blue);

	for(i=0;i<2*row+1;i++){
		for(j=0;j<2*col+1;j++){
			switch(maze[i][j]){
				case '+':{
					m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(j/2+0.5),16.0/max*(4.0/6.0)*(i/2+0.25)), Position(16.0/max*(4.0/6.0)*(j/2+0.75),16.0/max*(4.0/6.0)*(i/2+0.5)),Black, false); 					break;
				}
				case '|':{
					m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(j/2+0.5),16.0/max*(4.0/6.0)*(i/2+0.5)), Position(16.0/max*(4.0/6.0)*(j/2+0.75),16.0/max*(4.0/6.0)*(i/2+1.25)),Black, false); 					break;		 
				}
				//case ' ':{
				//	m.RenderRectangle(Position(2.5,2.5), Position(5.0,6.0),White, true); break;
				//}
				case '-':{
					m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(j/2+0.75),16.0/max*(4.0/6.0)*(i/2+0.25)), Position(16.0/max*(4.0/6.0)*(j/2+1.5),16.0/max*(4.0/6.0)*(i/2+0.5)),Black, false); 					break;
				}
			}				
		}
	}
	/*
	s.Open();
	
	s.RenderText(Position(0.0,0.0),Position(6.0,1.5),"Click on the Color to select",Blue);
	s.RenderRectangle(Position(1.5,1.0),Position(2.2,1.7),Blue,false);
	s.RenderRectangle(Position(2.3,1.0),Position(3.0,1.7),Black,false);
	s.RenderRectangle(Position(1.5,1.8),Position(2.2,2.5),Red,false);
	s.RenderRectangle(Position(3.1,1.0),Position(3.8,1.7),Yellow,false);
	//s.RenderRectangle(Position(1.5,2.6),Position(2.2,3.3),Green,false);
	
	s.SetMouseClickCallback(get_color);
	
	s.Close();
	*/
	count=-3;
	fscanf(mazemove,"%d %d %d %d %d %d\n",&y_n,&x_n,&face_n,&stage_n,&signal_n,&del);
	CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Mouse,16.0/max*(4.0/6.0)*0.6); 
	C.Draw();
	if(face_n==0){
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.725)),White,16.0/max*0.15);
		C.Draw();
	}
	else if(face_n==1){
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+0.975),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
		C.Draw();
	}
	else if(face_n==2){
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+1.025)),White,16.0/max*0.15);
		C.Draw();
	}
	else if(face_n==3){
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.275),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
		C.Draw();
	}

	delay(del/SCALE);
	m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+0.77),16.0/max*(4.0/6.0)*(y_n/2+0.52)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.48),16.0/max*(4.0/6.0)*(y_n/2+1.23)),White,false);
	
		
	gettimeofday(&start,NULL);	
		while(1){	
			
	fscanf(mazemove,"%d %d %d %d %d %d\n",&y_n,&x_n,&face_n,&stage_n,&signal_n,&del);
	//cout<<y_n<<" "<<x_n<<" ";	cout<<count<<endl;
		
		if(stage_n==3 || stage_n==4){
		//m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+0.76),16.0/max*(4.0/6.0)*(y_n/2+0.51)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.49),16.0/max*(4.0/6.0)*(y_n/2+1.24)),Green,false);
		m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.48),16.0/max*(4.0/6.0)*(y_n/2+1.23)),Green,false);
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Mouse,16.0/max*(4.0/6.0)*0.6); 
		C.Draw();
		if(face_n==0){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.725)),Yellow,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==1){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+0.975),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Yellow,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==2){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+1.025)),Yellow,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==3){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.275),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Yellow,16.0/max*0.15);
			C.Draw();
		}
		
		delay(del/SCALE);
		count++;
		C.Erase();
		m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+0.77),16.0/max*(4.0/6.0)*(y_n/2+0.52)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.48),16.0/max*(4.0/6.0)*(y_n/2+1.23)),Green,false);
		}
		else if(stage_n==1 || stage_n==2){
	//m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+0.76),16.0/max*(4.0/6.0)*(y_n/2+0.51)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.49),16.0/max*(4.0/6.0)*(y_n/2+1.24)),White,false);

		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Blue,16.0/max*(4.0/6.0)*0.6); 
		C.Draw();
		if(face_n==0){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.725)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==1){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+0.975),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==2){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+1.025)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==3){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.275),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
			C.Draw();
		}

		delay(del/SCALE);
		count++;
		C.Erase();
		m.RenderRectangle(Position(16.0/max*(4.0/6.0)*(x_n/2+0.79),16.0/max*(4.0/6.0)*(y_n/2+0.54)),Position(16.0/max*(4.0/6.0)*(x_n/2+1.46),16.0/max*(4.0/6.0)*(y_n/2+1.21)),White,false);
		
	}
	if(stage_n==4){
		CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.875)),Blue,16.0/max*(4.0/6.0)*0.6); 
		C.Draw();
		if(face_n==0){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+0.725)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==1){
					CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+0.975),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==2){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.125),16.0/max*(4.0/6.0)*(y_n/2+1.025)),White,16.0/max*0.15);
			C.Draw();
		}
		else if(face_n==3){
			CircleShape C(m,Position(16.0/max*(4.0/6.0)*(x_n/2+1.275),16.0/max*(4.0/6.0)*(y_n/2+0.875)),White,16.0/max*0.15);
			C.Draw();
		}
	}
	
	if(stage_n==0){
		break;
		m.RenderText(Position(16.0,5.0),Position(24.0,9.0),"Maze is 'UnSolvable'!!!", Red);
		}//Status maze is unsolvable
	if(stage_n==1 && stage_p==0){
		stage_p=1;
		m.RenderText(Position(16.0,4.0),Position(24.0,7.0),"Searching the Maze...", Blue);
		}//print status=searching
	else if(stage_n==2 && stage_p==1){
		stage_p=2; gettimeofday(&lap1,NULL);time1=time_u(lap1,start)/1000000;
		
		m.RenderText(Position(16.0,4.0),Position(24.0,7.0),"Exploring the maze...", Blue);
		m.RenderText(Position(16.0,5.5),Position(24.0,10.0),"Time taken to find Center : "+ftos(time1)+" sec", Black);
		}//print time and exploring time1
	else if(stage_n==3 && stage_p==2){
		stage_p=3;
		gettimeofday(&lap2,NULL);
		time2=time_u(lap2,start)/1000000;
		
		m.RenderText(Position(16.0,4.0),Position(24.0,7.0),"Travelling through Shortest path...", Blue);
		m.RenderText(Position(16.0,6.25),Position(24.0,10.0),"Time taken to explore maze :"+ftos(time2)+" sec", Black);//print of time2
		}//print entire exploring time
	else if(stage_n==4 && stage_p==3){
		stage_p=4;
		
		gettimeofday(&lap3,NULL);
		time3=time_u(lap3,lap2)/1000000;
		m.RenderText(Position(16.0,4.0),Position(24.0,7.0),"Travelling through Shortest path...", Blue);
		m.RenderText(Position(16.0,7.0),Position(24.0,10.0),"Least time taken to reach center :"+ftos(time3)+" sec", Black);//print of time3
		}//final time & probabilty
		
	else if(stage_n==5){
		
		float prob=del/time3*100;
		prob/=1000000;
		cout<<prob<<" "<<del<<" "<<time3<<endl;
		
		if(prob>100)prob=100;//Probability cannot be greater than 100%
		m.RenderText(Position(16.0,6.0),Position(24.0,7.0),"Probability of Mouse winning in techfest :"+ftos(prob)+"%", Blue);
		break;}
	}
	char AnyChar;
  	cin >> AnyChar;
  	m.Close();
  	}
  	else if(code==0){
  		cout<<"Quitting"<<endl;}
  	fclose(mazemove);
  	fclose(mazegen);
return 0;
}

string ftos(float x){
	string b;
	char a[100];
	int count=0;
	int v=(int) x;
	while(v!=0){
		v/=10;
		count++;
		}
	sprintf(a,"%f",x);
       for(int i=0;i<count+3;i++){
		b+=a[i];
		} 
	return b;
}    
