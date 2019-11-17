/*
 * Herramientas.h
 *
 *  Created on: 17 nov. 2019
 *      Author: utnso
 */

#ifndef HERRAMIENTAS_H_
#define HERRAMIENTAS_H_

#include "Contexto.h"

void inicializar_logger();
void inicializar_archivo_de_configuracion();
void obtener_valor_config(char*, t_config*, void(*)(void));
void obtener_puerto_de_escucha();
void obtener_timer_de_metricas();
void obtener_el_maximo_de_multiprogramacion();
void obtener_ids_semaforos();
void obtener_inits_de_semaforos();
void obtener_max_de_semaforos();
void obtener_alfa_para_sjf();
void terminar_suse_correctamente();
void escribir_en_pantalla(int tipo_esc, int tipo_log, char* console_buffer,
		char* log_colors[8], char* msj_salida);
void definir_nivel_y_loguear(int, int, char*);
void logger(int, int, const char*, ...);
void configurar_signals(void);
void capturar_signal(int signo);

#endif /* HERRAMIENTAS_H_ */
