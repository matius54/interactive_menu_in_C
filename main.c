#include <stdio.h>
#include <stdlib.h>

#include "MenuFun.c"

int main(){
	char asd;
int itera=2;
int seleccion=0;
char a[200];
a[0]='A';
a[1]='\0';

while(0){
	menu("testing",&seleccion,a);
	if('A'+itera/2=='Z')break;
	a[itera-1]=',';
	a[itera]='A'+itera/2;
	a[itera+1]='\0';
	itera+=2;
}
		
seleccion=menu_b("Nuevo menu","hoa xd,como,estas");

	while(1){
		//llamada a la funcion menu con el titulo del menu, el puntero a la seleccion y las opciones separadas por comas.
		menu("Que desea hacer?",&seleccion,"opcion 1,opcion 2,pruebar,salir");
		printf("\n");
		switch(seleccion){
			case 0:
				//opcion 1
				printf("presionaste la opcion 1");
			break;
			case 1:
				//opcion 2
				printf("presionaste la opcion 2");
			break;
			case 2:
				//opcion 3
				for(;;){
					asd=autogetch(3);
					printf("\n%i-%c",asd,asd);
				}
			break;
			case 3:
				//salir
				printf("salir :)");
				return 0;
			break;
		}
		
		printf("\n\n");
		pausefn(); //system("pause"); para windows/linux
	}
}
