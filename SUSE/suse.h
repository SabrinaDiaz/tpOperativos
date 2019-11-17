/*
 * suse.h
 *
 *  Created on: 17 nov. 2019
 *      Author: utnso
 */

#ifndef SUSE_H_
#define SUSE_H_

#include "Contexto.h"
#include "Herramientas.h"
#include <commons/collections/queue.h>

void inicializar_conexiones_de_clientes(void);
struct sockaddr_in crear_direccion_de_cliente();
void atender_clientes(int);
int agregar_conexion_a_lista_de_clientes(int,struct sockaddr_in);
void escuchar_clientes(int);
void atender_header(int, t_header);
void recibir_un_mensaje_char(int, int);

enum State {
		NEW,
		READY,
		EXEC,
		BLOCKED,
		EXIT,
	};

// estructura del tcb de suse
typedef struct TCB {
	int tid; //identificador de hilo
	ucontext_t* context;
	enum State state;
	struct TCB *next;
} TCB;

//Listas de estados de planificacion
t_list* lista_TCBs_new;
t_list* lista_TCBs_exit;
t_list* lista_TCBs_blocked;
t_list* lista_TCBs_ready; //ver si va aca o en Hilolay
t_list* lista_TCBs_exec; //ver si va aca o en Hilolay

//cola para FIFO
t_queue* colaFIFO;
t_queue* colaIO;


#endif /* SUSE_H_ */
