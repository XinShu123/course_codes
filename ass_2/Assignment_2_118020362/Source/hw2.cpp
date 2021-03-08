#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>

#define ROW 10
#define COLUMN 50 
#define NUM_THREAD 9
int frog_x=10;
int frog_y=24;

bool LOSE_FLAG = false;
bool WIN_FLAG = false;
int isQuit=0;
char dir=' ';




pthread_mutex_t mutex;

struct Node {
    int x, y;
    Node(int _x, int _y) : x(_x), y(_y) {};
    Node() {};
} frog;





char map[ROW + 10][COLUMN];

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


void* logs_move(void* t) {
	int log_num=(int)t;
	//canshu* t=(canshu*)s;

    /*  Move the logs  */
    //int log_num=t->log_num;
    

    //left move when log_num is odd



    srand((unsigned)clock());
    int start = rand() % (COLUMN - 1);
    
    int i;
    

    while ((!isQuit && !LOSE_FLAG)&&!WIN_FLAG) {
    	pthread_mutex_lock(&mutex);
    	if(kbhit()){
                dir=getchar();
            	if(dir=='w'||dir=='W'){
            		//t->node->x--;
            		frog_x--;

            		if(frog_x<0){
                	LOSE_FLAG=true;
                    }
                    /*if(frog_x==0){
                    	WIN_FLAG=true;
                    	map[frog_x][frog_y]='0';
                    	printf("\033[%d;1H\033[?25J",0);
                    	puts(map[0]);
                    }*/


            	}
            	if(dir=='a'||dir=='A'){
            		frog_y--;
            		if(frog_y<0){
                	LOSE_FLAG=true;
                    }


            	}
            	if(dir=='d'||dir=='D'){
            		frog_y++;
            		if(frog_y>COLUMN-2){
                	LOSE_FLAG=true;
                    }

            	}
            	if(dir=='s'||dir=='S'){
            		frog_x++;
            		if(frog_x>ROW){
                	LOSE_FLAG=true;
                    }

            	}
            	if(dir=='q'||dir=='Q'){
            		isQuit=1;
            	}
            }
            pthread_mutex_unlock(&mutex);
    	

        pthread_mutex_lock(&mutex);
        if(frog_x==0 && log_num==1){
                    	WIN_FLAG=true;
                    	map[frog_x][frog_y]='0';
                    	printf("\033[%d;1H\033[?25J",0);
                    	puts(map[0]);
                    }
        pthread_mutex_unlock(&mutex);
        if (log_num <= NUM_THREAD && log_num>0) {//logs move

            
            
            for (i = start; i < (start + 15); i++) {
                map[log_num][i % (COLUMN - 1)] = '=';//log move

            }
            pthread_mutex_lock(&mutex);
            if (log_num==frog_x) {
           
                
                


                bool tiaojian1=frog_y < start%(COLUMN-1) || frog_y >= (start + 15)%(COLUMN-1);
                //bool tiaojian2=frog_y <= start%(COLUMN-1) && frog_y < (start + 15)%(COLUMN-1);
                //bool tiaojian3=frog_y > start%(COLUMN-1) && frog_y > (start + 15)%(COLUMN-1);
                bool tiaojian2=(start%(COLUMN-1))>((start+15)%(COLUMN-1));
                bool tiaojian3=(frog_y>=(start+15)%(COLUMN-1)&&frog_y<start%(COLUMN-1));

                //bool tiaojian=tiaojian1&&(!(tiaojian2||tiaojian3));
                bool tiaojian=(tiaojian1&&(!tiaojian2))||(tiaojian2&&tiaojian3);
                if (tiaojian) {
                    
                    LOSE_FLAG = true;
                    

                }
            
                else{
            	      map[log_num][frog_y] = '0';
                }
                
                    
            }
            
            /*else if((log_num-1==t->node->x||log_num+1==t->node->x)){
            	map[log_num][t->node->y]='=';
            }*/


            // pthread_mutex_unlock(&mutex);
            //pthread_mutex_lock(&mutex);
            printf("\033[%d;1H", log_num + 1);
            puts(map[log_num]);
            //printf("%d,%d",log_num,LOSE_FLAG);


            //pthread_mutex_unlock(&mutex);
            
            for (i = start; i < (start + 15); i++) {
                map[log_num][i % (COLUMN - 1)] = ' ';
            }
            if (log_num % 2 != 0) {//left move
                start--;
                if (start < 0) {
                    start += COLUMN-1;
                }
                //printf("%d.%d",log_num,frog.x);
                if (log_num==frog_x) {
                    
                    frog_y--;
                    if(frog_y<0/*||frog_y<(start)%(COLUMN-1)*/){
                	    LOSE_FLAG=true;
                    }
                    /*else{
                    	map[log_num][t->node->y+ 1] = '=';

                    }*/
                    
                }
                /*else if(log_num==frog_x+1&&(dir=='w'||dir=='W')){
                    if(frog_y<0){
                        LOSE_FLAG=true;
                    }
                }
                else if(log_num==frog_x-1&&(dir=='s'||dir=='S')){
                    if(frog_y<0){
                        LOSE_FLAG=true;
                    }
                }*/
            }

            else{
                start++;
                if (start > COLUMN - 1) {
                    start -= COLUMN-1;
                }
                if (log_num==frog_x) {
                    
                        
                    
                    frog_y++;
                    if(frog_y>COLUMN-2/*||frog_y>(start+15)%(COLUMN-1)*/){
                	    LOSE_FLAG=true;
                    }
                    /*else{
                    	map[log_num][t->node->y- 1] = '=';

                    }*/
                }
                /*else if(log_num==frog_x+1&&(dir=='w'||dir=='W')){
                    if(frog_y<0){
                        LOSE_FLAG=true;
                    }
                }
                else if(log_num==frog_x-1&&(dir=='s'||dir=='S')){
                    if(frog_y<0){
                        LOSE_FLAG=true;
                    }
                }*/
            }
            
            pthread_mutex_unlock(&mutex);

            //usleep(100000);
        }
        
        else if(log_num==ROW){
        	pthread_mutex_lock(&mutex);
        	if(frog_x==ROW){
        		map[log_num][frog_y]='0';
        	}
        	//map[log_num][frog_y]='0';
        	if(dir=='a'||dir=='A'){
        		map[log_num][frog_y+1]='|';
        	}
        	else if(dir=='d'||dir=='D'){
        		map[log_num][frog_y-1]='|';
        	}
        	else if(dir=='w'||dir=='W'){
            for(int i=0;i<COLUMN-1;i++){
              map[log_num][i]='|';
            }
        		

        	}
        	else if((dir=='s'||dir=='S')&&frog_x==ROW){
        		LOSE_FLAG=true;
        	}
        	//pthread_mutex_lock(&mutex);
        	printf("\033[%d;1H\033[?25J", log_num + 1);
            puts(map[log_num]);
            //printf("%d.%d",frog_x,frog_y);
            
            pthread_mutex_unlock(&mutex);
        }
        
        

        
        
        
        /*printf("\033[%d;1H", log_num + 1);
        puts(map[log_num]);*/
        //pthread_mutex_unlock(&mutex);
        usleep(100000);
        //sleep(0.5);

 
    }
    pthread_exit(NULL);


}
int main(int argc, char* argv[]) {

    // Initialize the river map and frog's starting position
    memset(map, 0, sizeof(map));
    int i, j;
    for (i = 1; i < ROW; ++i) {
        for (j = 0; j < COLUMN - 1; ++j)
            map[i][j] = ' ';
    }

    for (j = 0; j < COLUMN - 1; ++j)
        map[ROW][j] = map[0][j] = '|';
    
    
    frog = Node(ROW, (COLUMN - 1) / 2);
    map[frog.x][frog.y] = '0';
    printf("\033[2J\033[H");
    //Print the map into screen
    for (i = 0; i <= ROW; ++i)
        puts(map[i]);

    pthread_t threads[NUM_THREAD+1];
    int rc;
    int k;
    int l;

    for (k = 1; k <= NUM_THREAD+1; ++k) {
        //arg = canshu(&frog, k);
        rc = pthread_create(&threads[k-1], NULL, logs_move, (void*)k);
        if (rc) {
            printf("ERROR: return code from pthread_create is %d.", rc);
            exit(1);
        }
    }
    pthread_mutex_init(&mutex, NULL);
    for(k=1;k<=NUM_THREAD+1;++k){
    	pthread_join(threads[k-1],NULL);
    }
    
    if(LOSE_FLAG){
    	printf("\033[%d;1H", ROW+2);
    	//printf("%d.%d",frog_x,frog_y);
    	printf("You lose the game!!\n");
    }
    else if(WIN_FLAG){
    	printf("\033[%d;1H", ROW+2);
    	printf("You win the game!!\n");
    }
    else if(isQuit){
    	printf("\033[%d;1H", ROW+2);
    	printf("You quit the game!!\n");
    }
    pthread_mutex_destroy(&mutex);


    pthread_exit(NULL);
    /*  Display the output for user: win, lose or quit.  */

    return 0;

}
