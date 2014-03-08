#include<iostream>
#include"ezwin.h"
using namespace std;

SimpleWindow m("Micromouse simulation",18,14,Position(1.0,1.0));

void draw_r(){
	int i=6,j=5;
	m.RenderRectangle(Position(j/2+0.5,i/2+0.5), Position(j/2+0.75,i/2+0.75),Blue, true); 
}

int ApiMain(){
	m.Open();
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	char AnyChar;
	cin>>AnyChar;
	m.Close();
	}
