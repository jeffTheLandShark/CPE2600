/**********************************************
*  Filename:  user_interface.c
*  Description: using pthread
*  Author: Group 2
*  Date: 12/11/2024
*  Note: gcc -o 
*  Note user_interface is using:
            0 for displaying information to the user
            1 for asking the user to enter information
***********************************************/  

#include <stdio.h>
#include <stdlib.h>
#include "user_interface.h"

int *speed_setp = 0;
int *position_setp = 0;
int *cruise_control = 0;
int *manual_accleration = 0;
int *manual_brake = 0;
int *current_speed = 0;
int *current_position = 40;
int *force_change = 0;
int user_input = 0;
int array_pointers[8];

int user_interface(int mode){


    if(mode == 0){
        printf("Current Speed is: %d\t Current Position is: %d", current_speed, current_position);
    } else if(mode == 1){
        printf("Would you like to change a value? (1 for yes or 0 for no)\n");
        scanf("%d", &user_input);
        if(user_input == 1){
            do{
                printf("Please input the the value you would like to change:\n");
                printf("1 to set the speed\t 2 to set the position\t 3 to turn on or off cruise control\n");
                printf("4 to set the accleration\t 5 to set the brake\n");
                scanf("%d", &user_input);
                if(check_user_value(user_input) != 1){
                    printf("You have entered a invalid option, please try again\n");
                } else{
                    change_value_mode(user_input);
                }
            } while(check_user_value(user_input) != 1);
        }
    } else{
        return -1;
    }

    
    return 0;
}

int check_user_value(int value){
    if(value == 1, value == 2, value == 3, value == 4, value == 5){
        return 1;
    } else{
        return 0;
    }
}

int change_value_mode(int option){
    int return_value = 0;
    int change_value = 0;
    int cont = 1;
    switch (option){
    case 1:
        do{
            printf("Input Speed (20-100):\n");
            scanf("%d", &change_value);
            if(change_value < 20 || change_value > 100){
                cont = 0;
                speed_setp = change_value;
            } else{
                printf("Invalid Input\n");
            }
        }while(cont == 1);
        break;
    case 2:
        do{
            printf("Input Position (40, 60, 80):\n");
            scanf("%d", &change_value);
            if(change_value == 40 || change_value == 60 || change_value == 80){
                cont = 0;
                position_setp = change_value;
            } else{
                printf("Invalid Input\n");
            }
        }while(cont == 1);
        break;
    case 3:
        do{
            printf("Turn on or off cruise control(0 for off or 1 for on):\n");
            scanf("%d", &change_value);
            if(change_value == 0 || change_value == 1){
                cont = 0;
                cruise_control = change_value;
            } else{
                printf("Invalid Input\n");
            }
        }while(cont == 1);
        break;
    case 4:
        do{
            printf("Set the accleration (0 - 100\n");
            scanf("%d", &change_value);
            if(change_value < 0 || change_value > 100){
                cont = 0;
                manual_accleration = change_value;
            } else{
                printf("Invalid Input\n");
            }
        }while(cont == 1);
        break;
    case 5:
        do{
            printf("Set the brake (0-100\n");
            scanf("%d", &change_value);
            if(change_value < 0 || change_value > 100){
                cont = 0;
                cruise_control = 0;
                manual_brake = change_value;
            } else{
                printf("Invalid Input\n");
            }
        }while(cont == 1);
        break;
    default:
        break;
    }
}