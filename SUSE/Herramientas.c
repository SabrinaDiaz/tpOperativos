/*
 * Herramientas.c
 *
 *  Created on: 17 nov. 2019
 *      Author: utnso
 */



#include "Herramientas.h"

void inicializar_logger(){
	suse_logger = log_create("suse.log", "Suse", 1, LOG_LEVEL_DEBUG);
	logger(escribir_loguear,l_info,"Bienvenido a Suse");
}

void inicializar_archivo_de_configuracion(){
	config = config_create("suse.config");
	if(config == NULL){
		logger(escribir_loguear,l_error,"No existe el archivo de configuracion, fijate si esta en la carpeta de debug");
		terminar_suse_correctamente();
	}else{
		logger(escribir_loguear,l_info,"Leyendo el archivo de configuracion...");
		obtener_valor_config(KEY_CONFIG_LISTEN_PORT, config, obtener_puerto_de_escucha);
		obtener_valor_config(KEY_CONFIG_METRICS_TIMER, config, obtener_timer_de_metricas);
		obtener_valor_config(KEY_CONFIG_MAX_MULTIPROG, config, obtener_el_maximo_de_multiprogramacion);
		obtener_valor_config(KEY_CONFIG_SEM_IDS, config, obtener_ids_semaforos);
		obtener_valor_config(KEY_CONFIG_SEM_INIT, config, obtener_inits_de_semaforos);
		obtener_valor_config(KEY_CONFIG_SEM_MAX, config, obtener_max_de_semaforos);
		obtener_valor_config(KEY_CONFIG_ALPHA_SJF, config, obtener_alfa_para_sjf);

		logger(escribir_loguear,l_info,"Archivo de configuracion cargado correctamente :)");
		config_destroy(config);

	}

}

void obtener_valor_config(char* key, t_config* file, void(*obtener)(void)){
	if (config_has_property(file, key)){
		obtener();
	}
}

void obtener_puerto_de_escucha(){
	listen_port = config_get_int_value(config, KEY_CONFIG_LISTEN_PORT);
	logger(escribir_loguear,l_debug,"El 'Puerto de escucha' es: %d",listen_port);
}

void obtener_timer_de_metricas(){
	metrics_timer = config_get_int_value(config, KEY_CONFIG_METRICS_TIMER);
	logger(escribir_loguear,l_debug,"El 'Metrics timer' es: %d", metrics_timer);
}

void obtener_el_maximo_de_multiprogramacion(){
	max_multiprog = config_get_int_value(config, KEY_CONFIG_MAX_MULTIPROG);
	logger(escribir_loguear,l_debug,"El 'Max multiprog' es: %d", max_multiprog);
}

void obtener_ids_semaforos(){
	sem_ids = config_get_array_value(config, KEY_CONFIG_SEM_IDS);
	logger(escribir_loguear,l_debug,"Obtenido 'sem_ids'");
}

void obtener_inits_de_semaforos(){
	sem_init = config_get_array_value(config, KEY_CONFIG_SEM_INIT);
	logger(escribir_loguear,l_debug,"Obtenido 'sem_init'");
}

void obtener_max_de_semaforos(){
	sem_max = config_get_array_value(config, KEY_CONFIG_SEM_MAX);
	logger(escribir_loguear,l_debug,"Obtenido 'sem_max'");
}

void obtener_alfa_para_sjf(){
	alpha_sjf = config_get_string_value(config, KEY_CONFIG_ALPHA_SJF);
	logger(escribir_loguear,l_debug,"Obtenido 'Alpha': %s", alpha_sjf);
}


void terminar_suse_correctamente(){
	logger(escribir_loguear,l_info,"BYe");
	log_destroy(suse_logger);
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

}

void capturar_signal(int signo){

    if(signo == SIGINT)
    {
    	logger(escribir_loguear, l_warning,"Terminando suse...");
    	terminar_suse_correctamente();

    }
    else if(signo == SIGPIPE)
    {
    	logger(escribir_loguear, l_error,"Desconectado");
    }

}
