
switch(dirt){
	case 0:
		switch(dirt1){
			case 0:
				if(row%2==0){
					wall_index(c_row+1,c_col,c_row+2,c_col,&nr,&nc);
	      				maze_out[nr][nc]=' ';
				}
				else if(row%2!=0){
					wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
					maze_out[nr][nc]=' ';
				}
				break;
			case 1:
				//2:2,1
				//1:
				//0:
				break;
			case 2: 
				//not possible
				break;
			case 3:
				if(row%2==0){
					wall_index(c_row+1,c_col,c_row+1,c_col-1,&nr,&nc);
	      				maze_out[nr][nc]=' ';
				}
				else if(row%2!=0){
					wall_index(c_row,c_col,c_row+1,c_col,&nr,&nc);
					maze_out[nr][nc]=' ';
				}
				break;
				}
	
	case 1:
		switch(dirt
	
	
	case 2:
		wall_index(c_row,c_col,c_row-1,c_col,&nr,&nc);
	        maze_out[nr][nc]=' ';
	
	case 3:
		wall_index(c_row,c_col,c_row,c_col-1,&nr,&nc);
         	maze_out[nr][nc]=' ';
		
