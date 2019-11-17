/*
 * Suse.c
 *
 *  Created on: 18 sep. 2019
 *      Author: utnso
 */

#include "Suse.h"
#include <Functions.c>

int main(){

	inicializar_logger();
	inicializar_archivo_de_configuracion();
	configurar_signals();

	///INICIEN LAS ESTRUCTURAS ACA
	inicializar_listas();
	inicializar_conexiones_de_clientes();

	//CREAMOS LAS LISTAS  DE ESTADOS Y LAS INICIALIZAMOS

/*	t_list* new = list_create();
	t_list* ready = list_create();
	t_list* exec = list_create();
	t_list* blocked = list_create();
	t_list* exit = list_create();*/

	logger(escribir_loguear,l_info,"Suse esta listo para recibir clientes");

	int socket_de_escucha_de_suse = escuchar_en(listen_port);

	escuchar_clientes(socket_de_escucha_de_suse);

}

void recibir_un_mensaje_char(int cliente, int size){
	logger(escribir_loguear,l_info,"Voy a recibir un mensaje");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void inicializar_conexiones_de_clientes(void){
	for (int i = 0; i < MAX_CLIENTES; ++i){
		conexiones_clientes[i].socket = NO_SOCKET;
	}
}

struct sockaddr_in crear_direccion_de_cliente() {
	struct sockaddr_in cliente_addr;
	//Setea la direccion en 0
	memset(&cliente_addr, 0, sizeof(cliente_addr));
	return cliente_addr;
}

void atender_clientes(int serv_socket){
	struct sockaddr_in cliente_addr = crear_direccion_de_cliente();
	socklen_t cliente_len = sizeof(cliente_addr);

	//Acepta la nueva conexion
	int socket_cliente = accept(serv_socket, (struct sockaddr *)&cliente_addr, &cliente_len);
	if (socket_cliente < 0) {
		logger(escribir_loguear,l_error,"Error al aceptar el cliente :(");
	}

	logger(escribir_loguear,l_trace,"Acepte un cliente, conexion (%d)", socket_cliente);

	int cliente_aceptado = agregar_conexion_a_lista_de_clientes(socket_cliente, cliente_addr);

	if(cliente_aceptado==-1){
		logger(escribir_loguear,l_error,"Demasiadas conexiones. Cerrando la conexion nueva\n");
		close(socket_cliente);
	}
}

int agregar_conexion_a_lista_de_clientes(int socket_conexion,struct sockaddr_in dir_cliente){
	//Lo agrego a la lista de conexiones con cliente actuales
	for (int i = 0; i < MAX_CLIENTES; ++i) {

		if (conexiones_clientes[i].socket == NO_SOCKET) {
			conexiones_clientes[i].socket = socket_conexion;
			conexiones_clientes[i].direccion = dir_cliente;

			return socket_conexion;
		}
	}

	return -1;
}

void escuchar_clientes(int server_suse) {
	fd_set readset, writeset, exepset;
	int max_fd;
	struct timeval tv = { 0, 500 };

	logger(escribir_loguear, l_debug, "Me pongo a escuchar clientes...");
	while (true) {
		//Inicializa los file descriptor
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_ZERO(&exepset);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		//Agrega el fd del socket servidor al set de lectura y excepciones
		FD_SET(server_suse, &readset);
		FD_SET(server_suse, &exepset);
		//Agrega el stdin para leer la consola
		FD_SET(STDIN_FILENO, &readset);
		//Seteo el maximo file descriptor necesario para el select
		max_fd = server_suse;
		//Agrega los conexiones existentes
		for (int i = 0; i < MAX_CLIENTES; i++) {
			if (conexiones_clientes[i].socket != NO_SOCKET) {
				FD_SET(conexiones_clientes[i].socket, &readset);
				FD_SET(conexiones_clientes[i].socket, &exepset);
			}
			if (conexiones_clientes[i].socket > max_fd) {
				max_fd = conexiones_clientes[i].socket;
			}
		}
		int result = select(max_fd + 1, &readset, &writeset, &exepset, &tv);
		//logger(loguear, l_debug, "Resultado del select: %d\n", result);
		if (result < 0) {
			logger(escribir_loguear, l_error, "Error en select\n");
			break;
		} else if (errno == EINTR) {
			logger(escribir_loguear, l_error, "Me mataron!\n");
			break;
		} else if (result > 0) //Hubo un cambio en algun fd
				{
			//Acepta la conexión de un cliente
			if (FD_ISSET(server_suse, &readset)) {
				atender_clientes(server_suse);
			}
			else {
				//Manejo de conexiones ya existentes
				for(int i = 0; i < MAX_CLIENTES; ++i){
					if(conexiones_clientes[i].socket != NO_SOCKET ){
						//Mensajes nuevos de algun cliente
						if (FD_ISSET(conexiones_clientes[i].socket, &readset)) {
							int socket_llamador = conexiones_clientes[i].socket;
							t_header header = recibir_header(socket_llamador);
							if(header.tamanio<0){
								close(socket_llamador);
								conexiones_clientes[i].socket = NO_SOCKET;
								continue;
							}

							atender_header(socket_llamador, header);

						} else if (FD_ISSET(conexiones_clientes[i].socket, &exepset)){
							conexiones_clientes[i].socket = NO_SOCKET;
								continue;
						}
					}// if != NO_SOCKET
				}//for conexiones_clientes */
			}
		}
	}
}

void recibir_hilolay_init(int cliente, int size){
	logger(escribir_loguear,l_info,"Voy a recibir a hilolay");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void recibir_suse_create(int cliente, int size){
	logger(escribir_loguear,l_info,"Creo un hilo");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void recibir_schedule_next(int cliente, int size){
	logger(escribir_loguear,l_info,"Digo cual es el siguiente hilo a planificar");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void recibir_suse_join(int cliente, int size){
	logger(escribir_loguear,l_info,"Realizar join");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void recibir_suse_close(int cliente, int size){
	logger(escribir_loguear,l_info,"Terminar programas");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(size, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}



void atender_header(int socket_llamador, t_header header){
	//aca hacen lo que necesiten hacer
	switch(header.tipo_de_mensaje){

	case CHAR_MESSAGE:
		recibir_un_mensaje_char(socket_llamador, header.tamanio);
		break;
	case HILOLAY_INIT:
		recibir_hilolay_init(socket_llamador, header.tamanio);
			break;
	case SUSE_CREATE:
		recibir_suse_create(socket_llamador, header.tamanio);
			break;
	case SUSE_SCHEDULE_NEXT:
		recibir_schedule_next(socket_llamador, header.tamanio);
			break;
	case SUSE_JOIN:
		recibir_suse_join(socket_llamador, header.tamanio);
			break;
	case SUSE_CLOSE:
		recibir_suse_close(socket_llamador, header.tamanio);
			break;
	default:
			break;
	}
}


//Fijarse que ready no tenga mas de 10 hilos
void tope_de_hilos_en_ready(t_list* ready, t_list* blocked, struct TCB* hilo ){
	if(list_size(ready) > 10){
		hilo -> state = BLOCKED;
		list_add(blocked , hilo);
	} else{
		hilo -> state = READY;
		list_add(ready, hilo);
	}
}

void inicializar_listas(){
	lista_TCBs_new = list_create();
	lista_TCBs_exit = list_create();
	lista_TCBs_blocked = list_create();
	colaFIFO = queue_create();
	colaIO = queue_create();
}

