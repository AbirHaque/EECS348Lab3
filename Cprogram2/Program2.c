#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0
#define buf_len 100000
#define cur_score (td*6+fg*3+safety*2+td_2c*8+td_fg*7)

struct Set{
	int arr[buf_len][5];
	int len;
};

void append(struct Set * set_val, int* arr, int arr_len){
	////////
	//	Check array exists in the set
	////////
	int not_in=true;
	for(int i = 0; i < set_val->len; i++){
		int is_same=true;
		for (int j = 0; j < arr_len; j++){
			if (set_val->arr[i][j]!=arr[j]){
				is_same=false;
			}
		}
		if (is_same){
			not_in= false;
			break;
		}
	}
	////////

	if(not_in){
		for(int i = 0; i < arr_len; i++){
		set_val->arr[set_val->len][i]=arr[i];
	}
	set_val->len+=1;
	}
}

int rec_score(struct Set * set_val,int score, int td, int fg, int safety, int td_2c, int td_fg){
	int tmp[5]={td_2c,td_fg,td,fg,safety};
	if (cur_score==score){
		append(set_val,tmp,5);
	}
	if (cur_score<score){
		return
		rec_score(set_val, score, td, fg, safety+1, td_2c, td_fg)|
		rec_score(set_val,score, td, fg+1, safety, td_2c, td_fg)|
		rec_score(set_val,score, td+1, fg, safety, td_2c, td_fg)|
		rec_score(set_val,score, td, fg, safety, td_2c, td_fg+1)|
		rec_score(set_val,score, td, fg, safety, td_2c+1, td_fg);
	}
	return 0;
}

int main(void){
	float request_stop=false;
	int nfl_score;
	struct Set set;
	while(true){
		printf("Enter 0 or 1 to STOP: ");
		fflush(stdout);
	    scanf("%f",&request_stop);
		if(request_stop!=(float)0){
			break;
		}
		printf("Enter the NFL score: ");
		fflush(stdout);
	    scanf("%d",&nfl_score);
	    printf("\nPossible combinations of scoring plays: \n");
		set.len=0;
	    rec_score(&set,nfl_score,0,0,0,0,0);
		for(int i = 0; i<set.len;i++){
			printf("%i TD + 2pt, %i TD + FG, %i TD, %i 3pt FG, %i Safety\n",set.arr[i][0],set.arr[i][1],set.arr[i][2],set.arr[i][3],set.arr[i][4]);
		}
	}
	fflush(stdout);
	return 0;
}
