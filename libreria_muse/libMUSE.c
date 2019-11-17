/*
 * libMUSE.c
 *
 *  Created on: 2 oct. 2019
 *      Author: utnso
 */

#include "libMUSE.h"

int muse_init(int id, char* ip, int puerto){
	//Primero se conecta a muse
	struct sockaddr_in DireccionServidor;
	DireccionServidor.sin_family = AF_INET;
	DireccionServidor.sin_addr.s_addr = inet_addr(ip);
	DireccionServidor.sin_port = htons(puerto);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (void*) &DireccionServidor, sizeof(DireccionServidor)) != 0) {
		perror("Cannot connect");
		return -1;
	}

	//Convierto el id a un string
	char word[30];
	sprintf(word, "%.9g", (double)id);

	//Concateno el ip con el id para que tengan la forma "IP-ID"
	char * ip_id = malloc(strlen(ip)+strlen(word)+1);
	ip_id[0] = '\0';
	strcat(ip_id,ip);
	strcat(ip_id,"-");
	strcat(ip_id,word);

	//Envío el IP-ID
	t_paquete* paquete = crear_paquete(MUSE_INIT);
	agregar_string_a_paquete(paquete, ip_id, strlen(ip_id)+1);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	free(ip_id);
    return 0;
}

void muse_close(){
	t_paquete* paquete = crear_paquete(MUSE_CLOSE);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	close(sock);
}

uint32_t muse_alloc(uint32_t tam){
	t_paquete* paquete = crear_paquete(MUSE_ALLOC);
	agregar_uint32_t_a_paquete(paquete, tam);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	t_header header = recibir_header(sock);
	if(header.tipo_de_mensaje == RTA_MUSE_ALLOC_EXITOSA){

		tp_muse_alloc contenido_del_paquete = recibir_direccion_de_memoria(header.tamanio, sock);
		void * dir = contenido_del_paquete->direccion_de_memoria;
		free(contenido_del_paquete);
		return (uint32_t)dir;

	}else if(header.tipo_de_mensaje == RTA_MUSE_ALLOC_ERROR){
		logger(escribir_loguear,l_error,"Segmentation fault");

		//Enviar señal al proceso de seg fault
		raise(SIGSEGV);

		return 0;
	}

}

void muse_free(uint32_t dir) {
	t_paquete* paquete = crear_paquete(MUSE_FREE);
	agregar_uint32_t_a_paquete(paquete, dir);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	t_header header = recibir_header(sock);
	if(header.tipo_de_mensaje == RTA_MUSE_FREE_EXITOSO){
		logger(escribir_loguear,l_info,"Se liberó la porción de memoria pedida");

	}else if(header.tipo_de_mensaje == RTA_MUSE_FREE_ERROR){
		logger(escribir_loguear,l_error,"Segmentation fault");

		//Enviar señal al proceso de seg fault
		raise(SIGSEGV);
	}

}

int muse_get(void* dst, uint32_t src, size_t n){
	t_paquete* paquete = crear_paquete(MUSE_GET);
	agregar_string_a_paquete(paquete, dst);
	agregar_uint32_t_a_paquete(paquete, src);
	agregar_int_a_paquete(paquete, n);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	t_header header = recibir_header(sock);
	if(header.tipo_de_mensaje == RTA_MUSE_GET_EXITOSO){
		logger(escribir_loguear,l_info,"Copiado");
		return 0;

	}else if(header.tipo_de_mensaje == RTA_MUSE_GET_ERROR){
		logger(escribir_loguear,l_error,"Segmentation fault");

		//Enviar señal al proceso de seg fault
		raise(SIGSEGV);
		return -1;
	}
    //memcpy(dst, (void*) src, n);
}

int muse_cpy(uint32_t dst, void* src, int n){
	t_paquete* paquete = crear_paquete(MUSE_CPY);
	agregar_uint32_t_a_paquete(paquete, dst);
	agregar_string_a_paquete(paquete, src);
	agregar_int_a_paquete(paquete, n);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	t_header header = recibir_header(sock);
	if(header.tipo_de_mensaje == RTA_MUSE_CPY_EXITOSO){
		logger(escribir_loguear,l_info,"Copiado");
		return 0;

	}else if(header.tipo_de_mensaje == RTA_MUSE_CPY_ERROR){
		logger(escribir_loguear,l_error,"Segmentation fault");

		//Enviar señal al proceso de seg fault
		raise(SIGSEGV);

    //memcpy((void*) dst, src, n);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t muse_map(char *path, size_t length, int flags){
    return 0;
}

int muse_sync(uint32_t addr, size_t len){
    return 0;
}

int muse_unmap(uint32_t dir){
    return 0;
}
