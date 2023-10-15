#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
//si es windows
	#include <conio.h>
#elif __unix__
//si es linux
	#include <termios.h>
	#include <unistd.h>
#endif
/*
modo (ex)
0 == flechas
1 == flechas + seleccionar + volver
2 == flechas + seleccionar + volver + wasd + numeros
3 == passtrought only numbers and letters
4 == passtrought all
*/
int autogetch(int ex){
	char c = '\0';
	int iter = 2,i,py1;
	#ifdef __unix__ 
		iter = 3;
		struct termios oldattr, newattr;
	    tcgetattr(STDIN_FILENO, &oldattr);
	    newattr = oldattr;
	    newattr.c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	#endif
	for(i=0;i<iter;i++){
		#ifdef _WIN32
			c = getch();
		#elif __unix__ 
			c = getchar();
		#endif
		if(ex==3)return ((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==8||c==127)?c:'\0';
		if(ex==4)return c;
		if(i==0 && c != 224 && c != -32){
			if(ex<0||ex>=2){
				py1 = (c=='w'||c=='W'||c=='2')?1:(c=='a'||c=='A'||c=='4')?4:(c=='s'||c=='S'||c=='8')?2:(c=='d'||c=='D'||c=='6')?3:(c=='5')?5:0;
				if(py1){
					c = py1-1;
					break;
				}
			}
			if(ex){
				if(c=='\n'||c=='\r'||c==' '){
					c = 4;
					break;
				}
				if(c==8||c==127){
					c = 5;
					break;
				}
        	}
        	#ifdef _WIN32
			    break;
	        #endif
		}
		if(i==1 && c != 91 && c != 72 && c != 80 && c != 77 && c != 75){
			break;
		}else if(i==1){
			c=(c==72)?0:(c==80)?1:(c==77)?2:(c==75)?3:c;
		}
		if(i==2 && c != 'A' && c != 'B' && c != 'C' && c != 'D'){
			break;
		}else if(i==2){
			c=(c>='A'&&c<='D')?c-'A':c;
		}
	}
	#ifdef __unix__ 
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	#endif
	/*
		esta funcion retorna un valor entero entre -1 y 5
	-1		0		1		2		3			4			5
	nada	Arriba	Abajo	Derecha	Izquierda	Seleccion	volver
	*/
	return (c>=0&&c<=5)?c:-1;
}

void pausefn(){//funcion de pausa multiplataforma
	#ifdef _WIN32
		system("pause");
	#elif __unix__ 
	    struct termios old_termios, new_termios;
	    char c;
	    tcgetattr(STDIN_FILENO, &old_termios);
	    new_termios = old_termios;
	    new_termios.c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	    printf("Presione una tecla para continuar . . .\n");
	    read(STDIN_FILENO, &c, 1);
	    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    #endif
}

void clsfn(){//funcion de limpiar pantalla multiplataforma
	#ifdef _WIN32
		system("cls");
	#elif __unix__ 
		system("clear");
	#endif
}
void menuget(int *length,int *opcnmbr,char *strn){
	*length=0;
	*opcnmbr=0;
	while(*(strn+*length)!='\0'){
		if(*(strn+*length)==',')*opcnmbr+=1;
		*length+=1;
	}
}
void menudrawer(int *nmax,int *nmrel,int *sel,char *prefix_a,char *prefix_b,char *opciones,char *sufix_a,char *sufix_b){
	int dx,i,j=0,bx=0,prlen_a=strlen(prefix_a),prlen_b=strlen(prefix_b),sflen_a=strlen(sufix_a),sflen_b=strlen(sufix_b);
	char buffer[*nmax+(*nmrel)*(prlen_b+sflen_b)+(prlen_a+sflen_a)+1];

	buffer[0]='\0';
	for(i=0;i<=*nmrel;i++){
		if(i==*sel){
			for(dx=0;dx<=prlen_a;dx++)buffer[bx+dx]=*(prefix_a+dx);
			bx+=prlen_a;
		}else{
			for(dx=0;dx<=prlen_b;dx++)buffer[bx+dx]=*(prefix_b+dx);
			bx+=prlen_b;
		}
		while(*nmax>=j&&*(opciones+j)!=','){
			buffer[bx]=*(opciones+j);
			bx++;
			j++;
		}
		j++;
		if(i==*nmrel)bx--;
		if(i==*sel){
			for(dx=0;dx<=sflen_a;dx++)buffer[bx+dx]=*(sufix_a+dx);
			bx+=sflen_a;
		}else{
			for(dx=0;dx<=sflen_b;dx++)buffer[bx+dx]=*(sufix_b+dx);
			bx+=sflen_b;
		}
		buffer[bx]='\n';
		if(i!=*nmrel)bx++;
	}
	buffer[bx]='\0';
	puts(buffer);
}
int menulogic(int *nmr,int *sel){
	int infl;
	while(1){
	infl = autogetch(2);
		if(infl==0){//arriba
			if(*sel<=0){
				*sel=*nmr;
			}else{
				*sel-=1;
			}
			break;
		}else if(infl==1){//abajo
			if(*sel>=*nmr){
				*sel=0;
			}else{
				*sel+=1;
			}
			break;
		}else if(infl==4){
			//cerrar menu por seleccion
			return 0;
		}
	}
	//continuar
	return 1;
}

void menu(char *name,int *seleccion,char *opc){
	int i,j;
	menuget(&i,&j,opc);
	if(*seleccion>=j||*seleccion<0)*seleccion=0;
	do{
		clsfn();
		if(name[0])printf("%s\n\n",name);
		menudrawer(&i,&j,seleccion,"\t> ","\t ",opc," <","");
	}while(menulogic(&j,seleccion));
}

int menu_b(char *name,char *opc){
	int b = 0;
	menu(name,&b,opc);
	return b;
}
