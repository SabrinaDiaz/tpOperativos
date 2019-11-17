/*
 * Herramientas_fuse.h
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#ifndef HERRAMIENTAS_SAC_H_
#define HERRAMIENTAS_SAC_H_

#include "Contexto_sac.h"

void inicializar_logger();
void inicializar_archivo_de_configuracion();
void obtener_valor_config(char*, t_config*, void(*)(void));
void obtener_listen_port();
void terminar_fuse_correctamente();
void configurae_signals(void);
void capturar_signal(int signo);

#endif /* HERRAMIENTAS_SAC_H_ */
