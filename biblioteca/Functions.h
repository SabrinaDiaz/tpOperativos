/*
 * Functions.h
 *
 *  Created on: 2 nov. 2019
 *      Author: utnso
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/string.h>


/*** Enums log***/
enum type_log {
	escribir,
	loguear,
	escribir_loguear,
	l_trace,
	l_debug,
	l_info,
	l_warning,
	l_error
};

/***********************PROTOCOLO DE COMUNICACION***********************************/

enum PROCESOS{
	SUSE,
	MUSE,
	FUSE,
	HILOLAY,
	LIBMUSE,
	sacFUSE

};

enum MENSAJES{
	MUSE_INIT,
	MUSE_CLOSE,
	MUSE_ALLOC,
	MUSE_FREE,
	MUSE_GET,
	MUSE_CPY,
	MUSE_MAP,
	MUSE_SYNC,
	MUSE_UNMAP,
	HILOLAY_INIT,
	SUSE_CREATE,
	SUSE_SCHEDULE_NEXT,
	SUSE_WAIT,
	SUSE_SIGNAL,
	SUSE_JOIN,
	SUSE_CLOSE,
	CHAR_MESSAGE,
	RTA_MUSE_ALLOC_EXITOSA,
	RTA_MUSE_ALLOC_ERROR,
	SEGMENTATION_FAULT,
	RTA_MUSE_FREE_EXITOSO,
	RTA_MUSE_FREE_ERROR,
	RTA_MUSE_GET_EXITOSO,
	RTA_MUSE_GET_ERROR,
	RTA_MUSE_CPY_EXITOSO,
	RTA_MUSE_CPY_ERROR,
	FUSE_OBTENER_ATRIBUTOS,
	FUSE_LEER,
	FUSE_ESCRIBIR,
	FUSE_ABRIR_ARCHIVO,
	FUSE_CREAR_ARCHIVO,
	FUSE_CREAR_DIRECTORIO,
	FUSE_ERROR,
	FUSE_VACIO,
	FUSE_INFO_ARCHIVOS
};

typedef struct
{
	int tamanio;
	enum MENSAJES tipo_de_mensaje;
}__attribute__((packed)) t_header;

typedef struct
{
	void* stream;
} t_buffer;

typedef struct
{
	t_header header;
	t_buffer* buffer;
} t_paquete;

typedef struct stru_mensaje_char{
	char * mensaje;
} t_mensaje_char;
typedef t_mensaje_char* tp_mensaje_char;

typedef struct stru_muse_init{
	char * ip_id;
}t_muse_init;
typedef t_muse_init* tp_muse_init;


typedef struct stru_fuse_leer {
	t_header tipo_de_mensaje;
	char * path;
	char * buffer;
	uint32_t size;
	uint32_t offset;;
}t_fuse_leer;

typedef t_fuse_leer* tp_fuse_leer;


/**************************************************************************************/
int conectarse_a(char*, int);
int escuchar_en(int);
int aceptar_conexion(int);
int enviar_mensaje(int sock, void *mensaje, int tamanio);
int recibir_mensaje(int sock, void *mensaje, int tamanio);
void cerrar_conexion(int);
int enviar_header(int, enum MENSAJES tipo_de_mensaje,int);
t_header recibir_header(int);
t_paquete* crear_paquete(enum MENSAJES tipo_de_mensaje);
void crear_buffer(t_paquete*);
void enviar_paquete(t_paquete*, int);
void* serializar_paquete(t_paquete*, int);
void agregar_string_a_paquete(t_paquete*, void*, int);
void agregar_int_a_paquete(t_paquete*, int);
void eliminar_paquete(t_paquete*);
void enviar_mensaje_char(char*, int);
tp_mensaje_char recibir_mensaje_char(int, int);
void escribir_en_pantalla(int tipo_esc, int tipo_log, char* console_buffer,char* log_colors[8], char* msj_salida);
void definir_nivel_y_loguear(int, int, char*);
void logger(int, int, const char*, ...);
void agregar_uint32_t_a_paquete(t_paquete*, uint32_t);

#endif /* FUNCTIONS_H_ */
