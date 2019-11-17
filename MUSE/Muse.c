/*
 * Muse.c
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#include "Muse.h"

void atender_muse_init(int cliente, int tamanio){
	logger(escribir_loguear,l_info,"Voy a recibir el pid del caller");
	tp_muse_init contenido_del_paquete = recibir_mensaje_char(tamanio, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->ip_id);
	free(contenido_del_paquete);

	agregar_cliente_a_lista_de_clientes_conectados();
}

void atender_muse_close(int cliente, int tamanio){
	logger(escribir_loguear,l_info,"The client se ha desconectado");
	eliminar_cliente_de_lista_de_clientes_conectados();
}

void atender_muse_alloc(int cliente, int tamanio){

}

void atender_muse_free(int cliente, int tamanio){

}

void atender_muse_get(int cliente, int tamanio){

}

void atender_muse_cpy(int cliente, int tamanio){

}

void atender_muse_map(int cliente, int tamanio){

}

void atender_muse_sync(int cliente, int tamanio){

}

void atender_muse_unmap(int cliente, int tamanio){

}

void recibir_un_mensaje_char(int cliente, int tamanio){
	logger(escribir_loguear,l_info,"Voy a recibir un mensaje de texto");
	tp_mensaje_char contenido_del_paquete = recibir_mensaje_char(tamanio, cliente);
	logger(escribir_loguear,l_info,"Esto es lo que recibi: %s", contenido_del_paquete->mensaje);
	free(contenido_del_paquete->mensaje);
	free(contenido_del_paquete);
}

void decidir_que_hacer_con_el_cliente(int cliente, t_header header){
	switch(header.tipo_de_mensaje){
	case MUSE_INIT:
		atender_muse_init(cliente, header.tamanio);
		break;
	case MUSE_ALLOC:
		atender_muse_alloc(cliente, header.tamanio);
		break;
	case MUSE_FREE:
		atender_muse_free(cliente, header.tamanio);
		break;
	case MUSE_GET:
		atender_muse_get(cliente, header.tamanio);
		break;
	case MUSE_CPY:
		atender_muse_cpy(cliente, header.tamanio);
		break;
	case MUSE_MAP:
		atender_muse_map(cliente, header.tamanio);
		break;
	case MUSE_SYNC:
		atender_muse_sync(cliente, header.tamanio);
		break;
	case MUSE_UNMAP:
		atender_muse_unmap(cliente, header.tamanio);
		break;
	case CHAR_MESSAGE:
		recibir_un_mensaje_char(cliente, header.tamanio);
		break;
	default:
		break;
	}

}

char* reservar_UPCM(){
	return malloc(memory_size);
}

void * escuchar_mensajes_entrantes(int cliente_fd){
	int status_header = 1;
	while(status_header > 0){
		t_header header = recibir_header(cliente_fd);
		status_header = header.tamanio;

		if(header.tipo_de_mensaje != MUSE_CLOSE){
			decidir_que_hacer_con_el_cliente(cliente_fd, header);
		}else if(header.tipo_de_mensaje == MUSE_CLOSE){
			atender_muse_close(cliente_fd, header.tamanio);
			status_header = -1;
		}

		header = recibir_header(cliente_fd);
		status_header = header.tamanio;
	}
	logger(escribir_loguear,l_error,"El cliente se ha desconectado");
}

void inicializar_server_multihilo(int cliente_fd){
	pthread_t id_thread;
	int resultado_de_hacer_el_hilo = pthread_create(&id_thread, NULL, (void*)escuchar_mensajes_entrantes, (void*)cliente_fd);
	if(resultado_de_hacer_el_hilo != 0){
		logger(escribir_loguear,l_error,"Error al hacer un hilo");
		terminar_muse_correctamente();
	}
	pthread_detach(id_thread);
}

int main(){

	inicializar_logger();
	inicializar_archivo_de_configuracion();
	configurar_signals();

	/*Reservo la porcion grande de memoria y la llamo UPCM por "única porción central de memoria"*/
	UPCM = reservar_UPCM();

	int tamanio_marco = obtener_tamanio_marco();
	logger(escribir_loguear,l_debug, "Tamaño de marco: %d",tamanio_marco);
	int cantidad_marcos = obtener_cantidad_marcos_en_MP(tamanio_marco);
	logger(escribir_loguear,l_info, "Memoria inicializada con %d marcos",cantidad_marcos);
	inicializar_bitmap_marcos();
	inicializar_tabla_segmentos();

	logger(escribir_loguear,l_info,"Muse esta listo para recibir pedidos");

	int listen_socket_muse = escuchar_en(listen_port);

	while(1){
		int cliente_fd = aceptar_conexion(listen_socket_muse);
		inicializar_server_multihilo(cliente_fd);
	}

	close(listen_socket_muse);
	terminar_muse_correctamente();

}

