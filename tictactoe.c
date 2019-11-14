#include <stdio.h>
int main(){

    int player =0;
    int winner =0;
    int choice =0;
    int row =0;
    int column =0;
    int line =0;
    int i;

    char grid [3][3]={{'1','2','3'},
                        {'4','5','6'},
                        {'7','8','9'}
                            };

    for( i=0;i<9 && winner ==0;i++){
        printf("\n\n");
        printf("%c  | %c | %c\n",grid[0][0],grid[0][1],grid[0][2]);

        printf("---|---|---\n");



        printf("%c  | %c | %c\n",grid[1][0],grid[1][1],grid[1][2]);

        printf("---|---|---\n");

        printf("%c  | %c | %c\n",grid[2][0],grid[2][1],grid[2][2]);

        printf("---|---|---\n");


        player =i%2+1;

        do{
            printf("\nplayer %d ,please enter the number of the square " "where you want to place your %c:",player ,(player ==1)?'x':'0');
            scanf("%d",&choice );
            row =--choice /3;
            column=choice %3;


        }while(choice <0 || choice >9 || grid [row][column]>'9');

            grid [row][column]=(player == 1) ?'x':'0';
                if((grid[0][0]==grid[1][1] && grid[0][0]==grid [2][2]) || (grid[0][2]==grid[1][1] && grid[0][2]==grid [2][0])  )

                    winner =player ;

                    else
                        for(line =0;line <=2;line++)

                              if((grid[line][0]==grid[line][1] && grid[line][0]==grid [line][2]) ||( grid[0][line]==grid[1][line] && grid[0][line]==grid [2][line])  )winner =player ;

    }

                               printf("\n\n");
                                printf("%c | %c | %c\n",grid[0][0],grid[0][1],grid[0][2]);

                                printf("---|---|---\n");



                                printf("%c | %c | %c\n",grid[1][0],grid[1][1],grid[1][2]);

                                printf("---|---|---\n");

                                printf("%c | %c | %c\n",grid[2][0],grid[2][1],grid[2][2]);

                                printf("---|---|---\n");

                                    if(winner ==0)
                                        printf("The game is a drawn \n");

                                            else
                                                printf("player %d has won\n",winner );

                                                return 0;



}
