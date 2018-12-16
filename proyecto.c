#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

int auxC2=1,auxC3=1;
int sNumeros[30];
int s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s24,s25,s26,s27,s28,s29,s30; //la chapuza mas grande de la historia perdon profe

long long k=0;
long long numeroDePisos[30],pisosMaximos,r=1;
long long dinero=50000,start,tiempo;
long long pisosMaximos;
char *dineroCadena;
char *tiempoCadena;
long long dineroGuardado[25];

TTF_Font *letra = NULL;
TTF_Font *letraAlt = NULL;
TTF_Font *letraPor = NULL;
TTF_Font *letraCont = NULL;
TTF_Font *letraDin = NULL;



Mix_Chunk *wave = NULL;
Mix_Music *music = NULL;

SDL_Color letraColor = {255, 255, 255,255};

SDL_Renderer * render;
SDL_Renderer * renderLlamada;
SDL_Renderer * renderPublico;
SDL_Texture * texturamensaje;
SDL_Texture * texturamensaje2;
SDL_Texture * texturafondo;
SDL_Texture * texturaLlamada;
SDL_Window * ventana;
SDL_Window * ventanaLlamada;
SDL_Window * ventanaPublico;
SDL_Surface * imagen;
SDL_Surface * imagenLlamada;
SDL_Surface * imagenPub;
SDL_Surface * mensaje;
SDL_Surface * mensajeAlt;

SDL_Rect srcrect1 = { 0, 0, 1055, 70 }; //Pregunta
SDL_Rect dstrect1 = { 110, 320, 1055, 70 };
SDL_Rect srcrect2 = { 0, 0, 440, 50 }; //alta
SDL_Rect dstrect2 = { 145, 495, 440, 50 };
SDL_Rect srcrect3 = { 0, 0, 440, 50 }; //altb
SDL_Rect dstrect3 = { 690, 495, 440, 50 };
SDL_Rect srcrect4 = { 0, 0, 440, 50 }; //altc
SDL_Rect dstrect4 = { 145, 610, 440, 50 };
SDL_Rect srcrect5 = { 0, 0, 440, 50 }; //altd
SDL_Rect dstrect5 = { 690, 610, 440, 50 };
SDL_Rect srcrect6 = { 0, 0, 300, 70 }; //LLamando a
SDL_Rect dstrect6 = { 140, 200, 300, 70 };
SDL_Rect srcrect7 = { 0, 0, 50, 50 }; //respuestaLlamando
SDL_Rect dstrect7 = { 140, 200, 50, 50 };
SDL_Rect srcrect8 = { 0, 0, 150, 150 };//contador
SDL_Rect dstrect8 = { 570, 100, 150, 150 };
SDL_Rect srcrect9 = { 0, 0, 395, 100 };//dinero actual
SDL_Rect dstrect9 = { 50, 127, 395, 100 };
SDL_Rect srcrect10 = { 0, 0, 395, 110 }; //juego terminado
SDL_Rect dstrect10 = { 450, 320, 395, 110 };

typedef struct{
	long long numpregunta;
	char pregunta[1000];
	char alt1[1000];
	char alt2[400];
	char alt3[400];
	char alt4[400];
	int respuestaCorrecta;
	int respuestaUsuario;
}Pantalla;

void respuestaCorrecta(Pantalla *vector,long long numeropregunta,int respusuario); //preguntas del 1 en adelante.
void comodinLlamada(long long numeropreg,Pantalla *vector);
char alternativa(int numero);
void Imprimir(long long pos, Pantalla *vector);
void comodinPublico(long long numeropregunta,SDL_Window *ventana,long long i,Pantalla *pantallas);
long long Dinero(long long numeropregunta,long long pisoMinimo);
void cambiarImagen(SDL_Texture * texturafondo, SDL_Renderer * render, SDL_Surface * imagen, SDL_Window * ventana);
void imagentexto(SDL_Window *ventana,long long i,Pantalla *pantallas);
void juegoTerminado(SDL_Window *ventana,long long  i,Pantalla* pantallas);
void comodinCincuenta(long long numeropregunta,Pantalla *vector);
void imagenPublico(SDL_Window *ventana,long long i,Pantalla* pantallas,char *por1,char *por2,char *por3,char *por4);
char * numeroacadena(long long entero);
void guardarPartida(long long numero);
long long cargarPartida(void);
void comodinUsado(long long numero,char linea[]);
int leerComodin(char linea[]);
void optimizar(long long tiempo,long long i,Pantalla* pantallas);
void cambiarchapuza();


int main(int argc, char* args[]){
	int comodinC=1,comodinP=1,comodinL=1,comodinE=1;
	long long pisoMinimo;
	long long i;
	long long cantDePreguntas;
    
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	music = Mix_LoadMUS("sonido/inicio.wav");
	Mix_PlayMusic( music, -1);
	Mix_PlayingMusic();

	char comC[]="comodin50.txt";
	char comL[]="comodinLlamada.txt";
	char comP[]="comodinPublico.txt";
	char comE[]="comodinTiempo.txt";


    																																																																																																																																																																																																																																																																																												
    FILE *f=fopen("preguntas.txt","r");
    fscanf(f,"%lld%lld\n",&cantDePreguntas,&pisoMinimo);    //Escribir al inicio la cant. de preg y el piso mÃ­nimo;
    pisosMaximos=cantDePreguntas/pisoMinimo;
    Pantalla pantallas[cantDePreguntas];  

    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();


    letra = TTF_OpenFont( "museoslab.ttf", 27);
    letraAlt = TTF_OpenFont( "museoslab.ttf", 39);
    letraPor = TTF_OpenFont( "museoslab.ttf", 30);
    letraCont = TTF_OpenFont( "museoslab.ttf", 130);
    letraDin = TTF_OpenFont( "museoslab.ttf", 50);


    
    ventana = SDL_CreateWindow("Quien quiere ser millonario?",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(ventana, -1, 0);
    
    imagen = SDL_LoadBMP("res/fondoprincipal.bmp");
    cambiarImagen(texturafondo,render,imagen,ventana);     
    SDL_Delay(900);
    imagen = SDL_LoadBMP("res/menuPrincipal.bmp");
    cambiarImagen(texturafondo,render,imagen,ventana);     
	Uint32 SDL_GetTicks();

    numeroDePisos[0]=50000;
    comodinC=leerComodin(comC);
    comodinL=leerComodin(comL);
    comodinP=leerComodin(comP);
    comodinE=leerComodin(comE);
    for(i=0;i<cantDePreguntas;i++){
        fscanf(f,"%lld\n",&pantallas[i].numpregunta); 
        fscanf(f,"%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d",pantallas[i].pregunta,pantallas[i].alt1,pantallas[i].alt2,pantallas[i].alt3,pantallas[i].alt4,&pantallas[i].respuestaCorrecta); 
        }//Este for llena el vector de estructuras con el txt 
    fclose(f); 
                                        	printf("%d",leerComodin(comC));

    bool quit = false;
    SDL_Event e;
        SDL_Event d;

        while( !quit ) {//Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ){//User requests quit
                    if( e.type == SDL_QUIT ){
                        quit = true;
                    }
                }
                	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

                	if(currentKeyStates[SDL_SCANCODE_F1]) {
                        comodinC=1;
                        comodinL=1;
                        comodinP=1;
                        comodinE=1;
                        comodinUsado(1,comC);
                        comodinUsado(1,comL);
                        comodinUsado(1,comP);
                        comodinUsado(1,comE);
                		goto partNueva;              
                }
                else if(currentKeyStates[SDL_SCANCODE_F2]){
                	printf("Partida cargada\n");
                	printf("%lld\n",cargarPartida() );

                	i=cargarPartida()-1;                	
                	printf("%lld\n",cargarPartida());

                	int j=0;
                    
                    for(j=0;j<i;j++){
                    	Dinero(pantallas[j].numpregunta,pisoMinimo); 

                    }


                	if(cargarPartida()==0){
                		partNueva:
                		printf("Partida Nueva\n");
                		printf("%lld\n",i);
                		i=0;
                	}            	               	
                	for(i;i<cantDePreguntas;i++){

                            cambiarchapuza();

                			music = Mix_LoadMUS("sonido/cambio.wav");
	                        Mix_PlayMusic( music, -1);
	                        Mix_PlayingMusic();
                            sleep(1); 

                			Imprimir(i,pantallas);
                			printf("Ingrese la alternativa correcta: \n");
	                       
                			imagentexto(ventana,i,pantallas);
                            SDL_Delay(80); 

	                        music = Mix_LoadMUS("sonido/pregunta.wav");
	                        Mix_PlayMusic( music, -1);
	                        Mix_PlayingMusic();
                			start=SDL_GetTicks(); 
                			bool quit = false;
                			while( !quit ){ //Handle events on queue
                      			while( SDL_PollEvent( &d ) != 0 ){//User requests quit
                                	if( d.type == SDL_QUIT ){
                                          quit = true;
                                 	}
                         		}
                        		const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL); 
                         		tiempo=(SDL_GetTicks()-start)/1000;
                         		SDL_Delay(40); 
                                
                                
                                optimizar(tiempo,i,pantallas);

                        		if(tiempo>=30)goto etiqueta;

                         		if (currentKeyStates[SDL_SCANCODE_A]) {
                                 pantallas[i].respuestaUsuario=1;
                                 sleep(1);         
                                 break;
                         		}
                        		if (currentKeyStates[SDL_SCANCODE_B]) {
                                 pantallas[i].respuestaUsuario=2;
                                 sleep(1);         
                                 break;
                         		}
                         		if (currentKeyStates[SDL_SCANCODE_C]) {
                                 pantallas[i].respuestaUsuario=3;
                                 sleep(1);         
                                 break;
                                 }
                         		if (currentKeyStates[SDL_SCANCODE_D]) {
                                 pantallas[i].respuestaUsuario=4;
                                 sleep(1);         
                                 break;
                        		 }                         
                        			 //comodines
                        		 if (currentKeyStates[SDL_SCANCODE_1] && comodinC==1) {
                                comodinC=0;
                                comodinUsado(0,comC);
                         	    comodinCincuenta(pantallas[i].numpregunta,pantallas);
                                imagentexto(ventana,i,pantallas);

                          
                               		sleep(1);
                         		}
                         		
                         		if (currentKeyStates[SDL_SCANCODE_2] && comodinL==1) {
                                 comodinL=0;
                                 comodinUsado(0,comL);
                                 comodinLlamada(i,pantallas);
                                 sleep(1); 
                         		}
                         		
                        		 if (currentKeyStates[SDL_SCANCODE_3] && comodinP==1) {

                                 comodinP=0;
                                 comodinUsado(0,comP);
                                 comodinPublico(pantallas[i].numpregunta,ventana,i,pantallas);

                  				}
                  				
                        		 if (currentKeyStates[SDL_SCANCODE_4] && comodinE==1) {
                         	     comodinE=0;
                         	     start=SDL_GetTicks();
                         	     cambiarchapuza();
                         	     comodinUsado(0,comE);

                         		}
                         		else
                         		if (currentKeyStates[SDL_SCANCODE_R] && i>0) {//retirarse
                         		r=1;
                         		goto retirar;
                         		}
                         		else
                        		if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {//Guardar partida
                         		
                        		printf("guardarPartida\n");
                        		
                         		guardarPartida(i+1);
                         		r=0; //Guarda de la partida 1 en adelante (0+1);
                         		goto terminar;
                         		}
                 			}       
               			 if(pantallas[i].respuestaUsuario==pantallas[i].respuestaCorrecta){      
                	   		 Dinero(pantallas[i].numpregunta,pisoMinimo); 
                	   		 if(i==cantDePreguntas-1){
                	   		 	goto retirar;
                	   		 }      
                			}
                			else if(pantallas[i].respuestaUsuario!=pantallas[i].respuestaCorrecta){
                        	etiqueta:
                        	r=0;
                        	retirar:
                        	juegoTerminado(ventana,i,pantallas); 
                        	guardarPartida(1);   
              
                        	goto terminar;
                			}
                			

                		}        


                }

                if (currentKeyStates[SDL_SCANCODE_F3]) {
                        imagen = SDL_LoadBMP("res/instrucciones.bmp");
                        cambiarImagen(texturafondo,render,imagen,ventana);
                }
                if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {

                        SDL_Quit();
                        break;
                }
               

        }//cierra while 62

        SDL_Delay(330);

        SDL_DestroyTexture(texturafondo);
        SDL_FreeSurface(imagen);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);

        SDL_Quit();
    terminar:
    return 0;
}


long long Dinero(long long numeropregunta,long long  pisoMinimo){ //el piso queda guardado en la posicion K(variable global)
    long long j;
        dinero=2*dinero;           
        
        for(j=1;j<pisosMaximos;j++){
            if(numeropregunta==pisoMinimo*j){
            k++;
            numeroDePisos[k]=dinero;
            }            

        }

    return dinero;

}

char alternativa(int numero){
    char c;
    if(numero==1){
        c='a';
    }
    if(numero==2){
        c='b';
    }
    if(numero==3){
        c='c';
    }
    if(numero==4){
        c='d';
    }
    return c;
}

void comodinLlamada(long long numeropreg,Pantalla *vector){
    srand(time(NULL));
    int alternativacorrecta=vector[numeropreg].respuestaCorrecta;
    char let=alternativa(alternativacorrecta);
    const char *letras=&let;
    char nombre[16];
    int i,a;
    nombre[0]=rand()%26+65;
    for(i=1;i<16;i++){
        nombre[i]=rand()%26+97;
        if(i==7){
            nombre[i]=' ';
        }
    }
    nombre[8]=rand()%26+65;
    nombre[15]='\0';
    a=rand()%4+1;
    
    ventanaLlamada = SDL_CreateWindow("Comodin llamada",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1000,400,SDL_WINDOW_OPENGL);
    renderLlamada = SDL_CreateRenderer(ventanaLlamada, -1, 0);
    imagenLlamada = SDL_LoadBMP("res/fondoLlamando.bmp");
    mensaje=TTF_RenderText_Solid( letra, nombre ,letraColor );
    texturaLlamada = SDL_CreateTextureFromSurface(renderLlamada, imagenLlamada);
    SDL_RenderCopy(renderLlamada, texturaLlamada, NULL, NULL);
    SDL_RenderPresent(renderLlamada);
    texturamensaje = SDL_CreateTextureFromSurface(renderLlamada, mensaje);
    SDL_RenderCopy(renderLlamada, texturamensaje, &srcrect6, &dstrect6);
    SDL_RenderPresent(renderLlamada); 
    sleep(2);         
    imagenLlamada = SDL_LoadBMP("res/respuesta.bmp");
    mensaje=TTF_RenderText_Solid( letra, letras ,letraColor );
    texturaLlamada = SDL_CreateTextureFromSurface(renderLlamada, imagenLlamada);
    SDL_RenderCopy(renderLlamada, texturaLlamada, NULL, NULL);
    SDL_RenderPresent(renderLlamada);  
    texturamensaje = SDL_CreateTextureFromSurface(renderLlamada, mensaje);
    SDL_RenderCopy(renderLlamada, texturamensaje, &srcrect7, &dstrect7);
    SDL_RenderPresent(renderLlamada); 
    SDL_UpdateWindowSurface(ventanaLlamada);
    sleep(2);
    tiempo=tiempo-5;         
    SDL_DestroyWindow(ventanaLlamada);
}

void comodinPublico(long long numeropregunta,SDL_Window *ventana,long long i,Pantalla *pantallas){
    srand(time(NULL));
    int alter1,alter2,alter3,alter4;
        alter1=rand()%(30)+5;
        alter2=rand()%30;
        alter3=rand()%30;
        alter4=100-alter1-alter2-alter3;
        printf("Alternativa a: %d%% \nAlternativa b: %d%%\n",alter1,alter2);
        printf("Alternativa c: %d%% \nAlternativa d: %d%%\n",alter3,alter4);

        ventanaPublico = SDL_CreateWindow("Porcentaje publico",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,SDL_WINDOW_OPENGL);
        char *por1=numeroacadena(alter1);
        char *por2=numeroacadena(alter2);
        char *por3=numeroacadena(alter3);
        char *por4=numeroacadena(alter4);

        imagenPublico(ventanaPublico,i,pantallas,por1,por2,por3,por4);
        
        free(por1); 
        free(por2); 
        free(por3); 
        free(por4); 
}

int correctaRespuesta(Pantalla *vector,long long numeropregunta,int respusuario){
    if((vector[numeropregunta-1].respuestaCorrecta) == respusuario){
        printf("Respuesta correcta\n");

    }
    else{     
        printf("Respuesta incorrecta. Usted ganó: %lld",numeroDePisos[k]);                                // monto del ultimo piso
    }
}  

void comodinCincuenta(long long numeropregunta,Pantalla *vector){
    srand(time(NULL));
    int i;
    int res1,res2,aleatorio,valorborrado=-1;
    res1=vector[numeropregunta-1].respuestaCorrecta;
    aleatorio=rand()%4+1;
    i=0;
    while(i<2){
        if(aleatorio!=res1 && valorborrado!=aleatorio){
            i++;
            valorborrado=aleatorio;
            switch(aleatorio){
                case 1: vector[numeropregunta-1].alt1[0]='\0';
                    break;
                case 2:vector[numeropregunta-1].alt2[0]='\0';
                    break;
                case 3: vector[numeropregunta-1].alt3[0]='\0';
                    break;
                case 4: vector[numeropregunta-1].alt4[0]='\0';
                    break;
            }
        }else aleatorio=rand()%4+1;
    }
}

void Imprimir(long long pos, Pantalla *vector){
    printf("%s\n%s\n%s\n",vector[pos].pregunta,vector[pos].alt1,vector[pos].alt2);
    printf("%s\n%s\n",vector[pos].alt3,vector[pos].alt4);
}
void cambiarImagen(SDL_Texture * texturafondo, SDL_Renderer * render, SDL_Surface * imagen, SDL_Window * ventana){
        SDL_RenderClear(render);
        texturafondo = SDL_CreateTextureFromSurface(render, imagen);
        SDL_RenderCopy(render, texturafondo, NULL, NULL);
        SDL_RenderPresent(render);     
        }
void imagentexto(SDL_Window *ventana,long long i,Pantalla* pantallas){

        imagen = SDL_LoadBMP("res/jugar.bmp");
        mensaje=TTF_RenderText_Solid( letra, pantallas[i].pregunta, letraColor );
        SDL_RenderClear(render);

        texturafondo = SDL_CreateTextureFromSurface(render, imagen);
        SDL_RenderCopy(render, texturafondo, NULL, NULL);

        texturamensaje = SDL_CreateTextureFromSurface(render, mensaje);
        SDL_RenderCopy(render, texturamensaje, &srcrect1, &dstrect1);

        mensajeAlt=TTF_RenderText_Solid( letraAlt, pantallas[i].alt1, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect2, &dstrect2);

        mensajeAlt=TTF_RenderText_Solid( letraAlt, pantallas[i].alt2, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect3, &dstrect3);

        mensajeAlt=TTF_RenderText_Solid( letraAlt, pantallas[i].alt3, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect4, &dstrect4);

        mensajeAlt=TTF_RenderText_Solid( letraAlt, pantallas[i].alt4, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect5, &dstrect5);

        tiempoCadena = numeroacadena(tiempo);
        dineroCadena = numeroacadena(dinero);


        mensajeAlt=TTF_RenderText_Solid( letraCont, tiempoCadena, letraColor );  //tiempo
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect8, &dstrect8);

        mensajeAlt=TTF_RenderText_Solid( letraDin, dineroCadena, letraColor );  //monto actual
        texturamensaje = SDL_CreateTextureFromSurface(render, mensajeAlt);
        SDL_RenderCopy(render, texturamensaje, &srcrect9, &dstrect9);
        SDL_RenderPresent(render);

        free(tiempoCadena);
        free(dineroCadena);

        SDL_UpdateWindowSurface(ventana);
        
        
       
}

void juegoTerminado(SDL_Window *ventana,long long i,Pantalla* pantallas){

		music = Mix_LoadMUS("sonido/final.wav");
	    Mix_PlayMusic( music, -1);
	    Mix_PlayingMusic(); 
        dineroCadena= numeroacadena(dinero);

	    imagen = SDL_LoadBMP("res/juegoTerminado.bmp");
	           SDL_RenderPresent(render);

	    if(pantallas[i].respuestaUsuario!=pantallas[i].respuestaCorrecta && r==0){
	    	dineroCadena= numeroacadena(numeroDePisos[k]);
	    	mensaje=TTF_RenderText_Solid( letraDin, dineroCadena, letraColor ); //numeroDePisos[k]
            }   
        else{
        	dineroCadena= numeroacadena(dinero);
        	mensaje=TTF_RenderText_Solid( letraDin, dineroCadena, letraColor );
        	//dinero
            }     

    
        texturafondo = SDL_CreateTextureFromSurface(render, imagen);
        SDL_RenderCopy(render, texturafondo, NULL, NULL);
        texturamensaje = SDL_CreateTextureFromSurface(render, mensaje);
        SDL_RenderCopy(render, texturamensaje, &srcrect10, &dstrect10);
        SDL_RenderPresent(render);
        SDL_UpdateWindowSurface(ventana);
        free(dineroCadena);
        SDL_Delay(3000); 


}

void imagenPublico(SDL_Window *ventanaPublico,long long i,Pantalla* pantallas,char *por1,char *por2,char *por3,char *por4){
        renderPublico = SDL_CreateRenderer(ventanaPublico, -1, 0);
        imagenPub = SDL_LoadBMP("res/jugar.bmp");
        mensaje=TTF_RenderText_Solid( letra, "El publico dice:", letraColor );
        SDL_RenderClear(renderPublico);

        texturafondo = SDL_CreateTextureFromSurface(renderPublico, imagenPub);
        SDL_RenderCopy(renderPublico, texturafondo, NULL, NULL);

        texturamensaje = SDL_CreateTextureFromSurface(renderPublico, mensaje);
        SDL_RenderCopy(renderPublico, texturamensaje, &srcrect1, &dstrect1);

        mensajeAlt=TTF_RenderText_Solid( letraPor, por1, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(renderPublico, mensajeAlt);
        SDL_RenderCopy(renderPublico, texturamensaje, &srcrect2, &dstrect2);

        mensajeAlt=TTF_RenderText_Solid( letraPor, por2, letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(renderPublico, mensajeAlt);
        SDL_RenderCopy(renderPublico, texturamensaje, &srcrect3, &dstrect3);

        mensajeAlt=TTF_RenderText_Solid( letraPor, por3 , letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(renderPublico, mensajeAlt);
        SDL_RenderCopy(renderPublico, texturamensaje, &srcrect4, &dstrect4);

        mensajeAlt=TTF_RenderText_Solid( letraPor, por4 , letraColor );
        texturamensaje = SDL_CreateTextureFromSurface(renderPublico, mensajeAlt);
        SDL_RenderCopy(renderPublico, texturamensaje, &srcrect5, &dstrect5);
        SDL_RenderPresent(renderPublico);
        
        SDL_UpdateWindowSurface(ventanaPublico);
        sleep(4);
        SDL_DestroyWindow(ventanaPublico);

}
char * numeroacadena(long long entero){
	char* cadena=(char *)malloc(30*sizeof(char));
	sprintf(cadena,"%lld",entero);
	return cadena;
}

void guardarPartida(long long numero){
	char *texto=(char*)malloc(16*sizeof(char));
	texto=numeroacadena(numero);
	FILE *guardar;
	guardar=fopen("partidaguardada.txt","w");	
	if(guardar == NULL){
		printf("No se pudo guardar la partida\n");
		exit (1);
	}
	fputs(texto,guardar);
	free(texto);
	fclose(guardar);	
}

long long cargarPartida(void){
	FILE *guardar;
	guardar=fopen("partidaguardada.txt","r");
	char *datos;
	fgets(datos,20,guardar);
	long long pos=atoll(datos);
	fclose(guardar);
	return pos;		
}

void comodinUsado(long long numero,char linea[]){ // modifica el valor y lo guarda en el txt
	char *cadena=(char*)malloc(8*sizeof(char));
	cadena=numeroacadena(numero);
	FILE *guardar;
	guardar=fopen(linea,"w");
	if(guardar == NULL){
		printf("No se pudo guardar la partida\n");
		exit (1);
	}
	fputs(cadena,guardar);	
	fclose(guardar);
    free(cadena);	
}
int leerComodin(char linea[]){
	FILE *ol;
	ol=fopen(linea,"r");
	char *datos;
	fgets(datos,2,ol);
	int m=atoi(datos);
	fclose(ol);
	return m;
}

void optimizar(long long tiempo,long long i,Pantalla* pantallas){

    if(tiempo==1 && s1==1){
        s1=0;
    	imagentexto(ventana,i,pantallas);
    	}
	if(tiempo==2 &&s2==1){
    	s2=0;
    	imagentexto(ventana,i,pantallas);
		}
	if(tiempo==3&&s3==1){
    	s3=0;
    	imagentexto(ventana,i,pantallas);
		}
	if(tiempo==4&&s4==1){
    s4=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==5&&s5==1){
    s5=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==6&&s6==1){
    s6=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==7&&s7==1){
    s7=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==8&&s8==1){
    s8=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==9&&s9==1){
    s9=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==10&&s10==1){
    s10=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==11&&s11==1){
    s11=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==12&&s12==1){
    s12=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==13&&s13==1){
    s13=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==14&&s14==1){
    s14=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==15&&s15==1){
    s15=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==16&&s16==1){
    s16=0;
    imagentexto(ventana,i,pantallas);
	}	

	if(tiempo==17&&s17==1){
    s17=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==18&&s18==1){
    s18=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==19&&s19==1){
    s19=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==20&&s20==1){
    s20=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==21&&s21==1){
    s21=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==22&&s22==1){
    s22=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==23&&s23==1){
    s23=0;
    imagentexto(ventana,i,pantallas);
	}
	if(tiempo==24&&s24==1){
    s24=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==25&&s25==1){
    s25=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==26&&s26==1){
    s26=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==27&&s27==1){
    s27=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==28&&s28==1){
    s28=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==29&&s29==1){
    s29=0;
    imagentexto(ventana,i,pantallas);
		}
	if(tiempo==30&&s30==1){
    s30=0;
    imagentexto(ventana,i,pantallas);
	}


}

void cambiarchapuza(){
    s1=1;
    s2=1;
    s3=1;
    s4=1;
    s5=1;
    s6=1;
    s7=1;
    s8=1;
    s9=1;
    s10=1;
    s11=1;
    s12=1;
    s13=1;
    s14=1;
    s15=1;
    s16=1;
    s17=1;
    s18=1;
    s19=1;
    s20=1;
    s21=1;
    s22=1;
    s23=1;
    s24=1;
    s25=1;
    s26=1;
    s27=1;
    s28=1;
    s29=1;
    s30=1;


}



