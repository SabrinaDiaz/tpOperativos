/*
 * Herramientas_fuse.c
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#include "Herramientas_sac.h"

void inicializar_logger(){
	fuse_logger = log_create("fuse.log", "Fuse", 1, LOG_LEVEL_DEBUG);
	logger(escribir_loguear,l_info,"Yo soy Fuse, hola!");
}

void inicializar_archivo_de_configuracion(){
	config = config_create("sac.config");
	if(config == NULL){
		logger(escribir_loguear,l_error,"El archivo de configuracion no existe, fijate si esta en la carpeta de debug");
		terminar_fuse_correctamente();
	}else{
		logger(escribir_loguear,l_info,"Leyendo archivo de configuracion...");
		obtener_valor_config(KEY_CONFIG_LISTEN_PORT, config, obtener_listen_port);

		logger(escribir_loguear,l_info,"Archivo de configuracion cargado correctamente :)");
		config_destroy(config);

	}

}

void obtener_valor_config(char* key, t_config* file, void(*obtener)(void)){
	if (config_has_property(file, key)){
		obtener();
	}
}

void obtener_listen_port(){
	listen_port = config_get_int_value(config, KEY_CONFIG_LISTEN_PORT);
	logger(escribir_loguear,l_debug,"El 'Puerto de escucha' es: %d",listen_port);
}

void terminar_fuse_correctamente(){
	logger(escribir_loguear,l_info,"Adios!");
	log_destroy(fuse_logger);
	exit(EXIT_SUCCESS);
}

void configurar_signals(void){
	//
	struct sigaction signal_struct;
	signal_struct.sa_handler = capturar_signal;
	signal_struct.sa_flags = 0;

	sigemptyset(&signal_struct.sa_mask);

	sigaddset(&signal_struct.sa_mask, SIGPIPE);
	if (sigaction(SIGPIPE, &signal_struct, NULL) < 0) {
		logger(escribir_loguear, l_error, " SIGACTION error ");
	}

	sigaddset(&signal_struct.sa_mask, SIGINT);
	if (sigaction(SIGINT, &signal_struct, NULL) < 0) {
		logger(escribir_loguear, l_error, " SIGACTION error ");
	}

}

void capturar_signal(int signo){

    if(signo == SIGINT)
    {
    	logger(escribir_loguear, l_warning,"Fuse esta en el Upside-down ahora, chau...");
    	terminar_fuse_correctamente();

    }
    else if(signo == SIGPIPE)
    {
    	logger(escribir_loguear, l_error,"Desconectado");
    }

}

