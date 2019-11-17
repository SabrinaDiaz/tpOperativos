/*
 * Herramientas_muse.c
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#include "Herramientas_muse.h"

void inicializar_logger(){
	muse_logger = log_create("muse.log", "Muse", 1, LOG_LEVEL_DEBUG);
	logger(escribir_loguear,l_info,"Hi, bienvenido a Muse");
}

void inicializar_archivo_de_configuracion(){
	config = config_create("muse.config");
	if(config == NULL){
		logger(escribir_loguear,l_error,"El archivo de configuracion no existe. Fijate en la carpeta Debug.");
		terminar_muse_correctamente();
	}else{
		logger(escribir_loguear,l_info,"Cargando el archivo de configuracion...");
		obtener_valor_config(KEY_CONFIG_LISTEN_PORT, config, obtener_el_listen_port);
		obtener_valor_config(KEY_CONFIG_MEMORY_SIZE, config, obtener_el_memory_size);
		obtener_valor_config(KEY_CONFIG_PAGE_SIZE, config, obtener_el_page_size);
		obtener_valor_config(KEY_CONFIG_SWAP_SIZE, config, obtener_el_swap_size);

		logger(escribir_loguear,l_info,"Archivo de configuracion cargado correctamente :)");
		config_destroy(config);

	}

}

void obtener_valor_config(char* key, t_config* file, void(*obtener)(void)){
	if (config_has_property(file, key)){
		obtener();
	}
}

void obtener_el_listen_port(){
	listen_port = config_get_int_value(config, KEY_CONFIG_LISTEN_PORT);
	logger(escribir_loguear,l_debug,"El 'Listen port' es: %d",listen_port);
}

void obtener_el_memory_size(){
	memory_size = config_get_int_value(config, KEY_CONFIG_MEMORY_SIZE);
	logger(escribir_loguear,l_debug,"El 'Memory size' es: %d",memory_size);
}

void obtener_el_page_size(){
	page_size = config_get_int_value(config, KEY_CONFIG_PAGE_SIZE);
	logger(escribir_loguear,l_debug,"El 'Page size' es: %d",page_size);
}

void obtener_el_swap_size(){
	swap_size = config_get_int_value(config, KEY_CONFIG_SWAP_SIZE);
	logger(escribir_loguear,l_debug,"El 'Swap size' es: %d",swap_size);
}

void terminar_muse_correctamente(){
	/*MOSTRAR METRICAS*/
	logger(escribir_loguear,l_info,"Chau!");
	log_destroy(muse_logger);
	free(UPCM);
	exit(EXIT_SUCCESS);
}

void configurar_signals(void){
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
	sigaddset(&signal_struct.sa_mask, SIGSEGV);
	if (sigaction(SIGINT, &signal_struct, NULL) < 0) {
		logger(escribir_loguear, l_error, " SIGACTION error ");
	}
}

void capturar_signal(int signo){

    if(signo == SIGINT)
    {
    	logger(escribir_loguear, l_warning,"\n Muse ha sido asesinado, agh!...");
    	terminar_muse_correctamente();

    }
    else if(signo == SIGPIPE)
    {
    	logger(escribir_loguear, l_error,"Desconectado");
    }
    else if(signo == SIGSEGV)
	{
		logger(escribir_loguear, l_error,"SEGMENTATION FAULT");
	}

}
