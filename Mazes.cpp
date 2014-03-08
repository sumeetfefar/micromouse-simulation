/*
*  mazes.cpp
*  
*
*  Created by Batch 36 on 08/11/10.
*  Copyright 2010 __MyCompanyName__. All rights reserved.
*
*/
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;
#include "rect.h"
#include "label.h"
#include <cmath>
#include "ezwin.h"
#include <cassert>
SimpleWindow MyWindow("Maze", 25.0, 25.0,
                                          Position(0.0, 0.0));
//Defining functions
void rotatex(float *x, float *y, float *z, float p)
{        
        *z=*z*cos(p) + *y*sin(p);
        *y=*y*cos(p) - *z*sin(p); // Using the rotation formula about x axis
}
 
void rotatey(float *x, float *y, float *z, float p){
        *x=*x*cos(p) + *z*sin(p);
        *z=*z*cos(p) - *x*sin(p); // Using the rotation formula about y axis
}
 
void rotatez(float *x, float *y, float *z, float p){
        *y=*y*cos(p) + *x*sin(p);
        *x=*x*cos(p) - *y*sin(p); // Using the rotation formula about z axis
}
 
//function for measuring distance between two points
float distance(float a1, float b1, float a2, float b2)
{
        float c;
        c=sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
        return c;
}
 
void makequad1(float x[4] , float y[4])
{
        MyWindow.RenderLine(Position(x[0],y[0]), Position(x[1],y[1]), Red, 0.0);
        MyWindow.RenderLine(Position(x[2],y[2]), Position(x[3],y[3]), Red, 0.0);
        MyWindow.RenderLine(Position(x[3],y[3]), Position(x[0],y[0]), Red, 0.0);
        MyWindow.RenderLine(Position(x[1],y[1]), Position(x[2],y[2]), Red, 0.0);
}
 
void boldquad1(float x[4] , float y[4])
{
        MyWindow.RenderLine(Position(x[0],y[0]), Position(x[1],y[1]), Red, 0.1);
        MyWindow.RenderLine(Position(x[2],y[2]), Position(x[3],y[3]), Red, 0.1);
        MyWindow.RenderLine(Position(x[3],y[3]), Position(x[0],y[0]), Red, 0.1);
        MyWindow.RenderLine(Position(x[1],y[1]), Position(x[2],y[2]), Red, 0.1);
}
 
 
//function to make a black sided quadrilateral given four co-ordinates
//similar codes written for different colours
void draw_black(int a, int b)
{
        int i,j;
        float x[4]={a-2, a+2, a+2, a-2}, y[4]={b-2, b-2, b+2, b+2}, z[4]={0, 0, 0, 0};
        for(i=0; i<4; i++){
                rotatex(&x[i], &y[i], &z[i], -0.5);
                rotatey(&x[i], &y[i], &z[i], -0.5);
        }
        float xc,yc,co[4],r[4],si[4];
        for(i=0;i<4;i++)
        {
                MyWindow.RenderLine(Position(x[i],y[i]), Position(x[i],y[i]), Black, 0.0);
                
        }
        //finding point of intersection of diagonal
        xc=(1/((y[3]-y[1])/(x[3]-x[1])-(y[0]-y[2])/(x[0]-x[2])))*(y[2]-y[1]-x[2]*(y[0]-y[2])/(x[0]-x[2])+x[1]*(y[3]-y[1])/(x[3]-x[1]));
        yc=y[2]+(y[0]-y[2])*(xc-x[2])/(x[0]-x[2]);
        
        for(i=0;i<4;i++)
        {
                r[i]=distance(xc,yc,x[i],y[i]);
                co[i]=(x[i]-xc)/r[i];
                si[i]=(y[i]-yc)/r[i]; }
        do{
                for(i=0;i<4;i++)
                {
                        r[i]=r[i]-0.01*r[i];
                }
                for(i=0;i<4;i++)
                {
                        x[i]=xc+r[i]*co[i];
                        y[i]=yc+r[i]*si[i];
                }
                makequad1(x,y);
                
        }
        while(r[0]>0.1);
        MyWindow.RenderLine(Position(xc,yc), Position(xc,yc), Red, 0.1);
        MyWindow.RenderLine(Position(0,yc+1.29), Position(20,yc+1.29), White, 0.01);
        boldquad1(x,y);
 
}
 
int ApiMain(){
        MyWindow.Open();
        assert(MyWindow.GetStatus() == WindowOpen);
        int i, j;
        int coorx[20], coory[20];
        for(i=0;i<20;i++){
                coorx[i]=4*i;
                coory[i]=4*i;
        }
        int maze[5][5]={{1,0,0,0,1},{1,1,1,1,0},{0,0,1,1,1},{1,0,1,0,1},{1,1,1,1,1}};
        for(i=0; i<5; i++){ //20 is an arbitrary no
                for(j=0; j<5; j++){
                        switch (maze[i][j]){
                                case 1:
                                        draw_black(coorx[i], coory[j]);
                                        break;
                                
                                default:
                                        //draw_white(coorx[i], coory[j]);
                                        break;
                        }
                }
        }
}