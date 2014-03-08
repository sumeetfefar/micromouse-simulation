#include<iostream>
using namespace std;
#include "ezwin.h"
#include "bitmap.h"
#include <assert.h>
#include<ctime>

SimpleWindow m("Micromouse simulation",18,14,Position(1.0,1.0));

BitMap Mouse(m);

void delay(unsigned int mseconds){
	clock_t goal = mseconds + clock();
	while(goal>clock()){};
	}

int ApiMain(){
	m.Open();
	assert(m.GetStatus() == WindowOpen);
	
	Mouse.Load("mouse.xpm");
	assert(Mouse.GetStatus() == BitMapOkay);
	
	Mouse.SetPosition(Position(2.0,2.0));
	Mouse.Draw();
	
	for(int i=0;i<1000;i++){
		Mouse.Erase();
		Mouse.SetPosition(Position(2.0+(float)i/100,2.0));
		Mouse.Draw();
		delay(1000);
	}
	
	return 0;
	
}

	
