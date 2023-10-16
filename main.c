#include <stdio.h>
#include <stdlib.h>

#include "MenuFun.c"

int main(){
int selection;
//short call to the menu function without the selection pointer.
selection=menu_b("New menu","heo xd,how,are,u");

	while(1){
		//call to the menu function with the menu title, the pointer to the selection and the options comma separated.
		menu("What do you want to do?",&selection,"option 1,option 2,nothing,exit");
		printf("\n");
		switch(selection){
			case 0:
				//option 1
				printf("presionaste la opcion 1");
			break;
			case 1:
				//option 2
				printf("presionaste la opcion 2");
			break;
			case 2:
				//option 3
				
			break;
			case 3:
				//exit
				printf("exit :)");
				return 0;
			break;
		}
		
		printf("\n\n");
		pausefn(); //system("pause"); for windows/linux
	}
}
