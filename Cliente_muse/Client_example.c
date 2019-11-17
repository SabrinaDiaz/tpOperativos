/*
 ============================================================================
 Name        : Client_example.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Client_example.h"

int main(void){
	t_log * client_logger = log_create("client.log", "Client_example", 1, LOG_LEVEL_DEBUG);
	logger(escribir_loguear,l_info,"Hola, soy un cliente");

	//Pruebo muse_init:
	pid_t pid = getpid();
	muse_init((int)pid, "172.17.0.1", 5003);
	logger(escribir_loguear,l_info,"PID sent: %d", (int)pid);

	//Probando muse_close:
	sleep(10);
	muse_close();

	logger(escribir_loguear,l_info,"Bye");
	return EXIT_SUCCESS;
}
