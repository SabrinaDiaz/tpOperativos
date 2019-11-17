 /*============================================================================
 Name        : Client_example.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Client_example.h"

int main(){

	hilolay_init();
	int x = 0;

	hilolay_t thread; //le doy un id al hilo creado, la estructura se encuentra en hilolay.h

	hilolay_create(&thread, NULL, suse_create(),&x);
}

