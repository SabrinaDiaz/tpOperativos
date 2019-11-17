/*
 * Herramientas_muse.h
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#ifndef HERRAMIENTAS_MUSE_H_
#define HERRAMIENTAS_MUSE_H_

#include "Contexto_muse.h"

void inicializar_logger();
void inicializar_archivo_de_configuracion();
void obtener_valor_config(char*, t_config*, void(*)(void));
void obtener_el_listen_port();
void obtener_el_memory_size();
void obtener_el_page_size();
void obtener_el_swap_size();
void terminar_muse_correctamente();
void configurar_signals(void);
void capturar_signal(int signo);

#endif /* HERRAMIENTAS_MUSE_H_ */
