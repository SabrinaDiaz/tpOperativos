/*
 * hilolay_alumnos.c
 *
 *  Created on: 1 nov. 2019
 *      Author: utnso
 */

#include "hilolay_alumnos.h"
/*
void hilolay_init(){
	//t_log * client_logger = log_create("client.log", "Client_example", 1, LOG_LEVEL_DEBUG);
		logger(escribir_loguear,l_info,"Hola, soy un cliente");

		sock = conectarse_a("172.17.0.1", 5003);
		char* mi_mensaje = "Soy el cliente hardcodeado y si lees esto es porque me conecte bien y envio bien un mensaje";

		t_paquete* paquete = crear_paquete(CHAR_MESSAGE);//aca deberi ir HILOLAY_INIT
		agregar_string_a_paquete(paquete, mi_mensaje, strlen(mi_mensaje)+1);
		enviar_paquete(paquete, sock);
		eliminar_paquete(paquete);

		logger(escribir_loguear,l_info,"Ya envie lo que me pidieron, chau");
}*/

void hilolay_init(){
		sock = conectarse_a("172.17.0.1", 5003);
	t_paquete* paquete = crear_paquete(HILOLAY_INIT); //lo que mando a suse
	//	agregar_uint32_t_a_paquete(paquete,0);
		enviar_paquete(paquete, sock); //esto lo serializa solo
		eliminar_paquete(paquete);
		init_internal();
}

 //esto no se si va adentro de suse_create
int suse_create(int tid){
	max_tid = 0;
	if (tid > max_tid) max_tid = tid;
	sock = conectarse_a("172.17.0.1", 5003);
	t_paquete* paquete = crear_paquete(SUSE_CREATE); //lo que mando a suse
		agregar_uint32_t_a_paquete(paquete, max_tid);
		enviar_paquete(paquete, sock);
		eliminar_paquete(paquete);
		return 0;
}

int suse_schedule_next(void){ //le pregunta a suse quien es el proximo
	int next_tid = max_tid;
	t_paquete* paquete = crear_paquete(SUSE_SCHEDULE_NEXT);
		agregar_uint32_t_a_paquete(paquete, next_tid);
		enviar_paquete(paquete, sock);
		eliminar_paquete(paquete);
		return 0;
}

int suse_join (int tid){
t_paquete* paquete = crear_paquete(SUSE_JOIN);
	agregar_uint32_t_a_paquete(paquete, tid);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);
	return 0;
}

void suse_close(int tid){
	t_paquete* paquete = crear_paquete(SUSE_CLOSE);
	agregar_uint32_t_a_paquete(paquete, tid);
	enviar_paquete(paquete, sock);
	eliminar_paquete(paquete);

	close(sock);
}

int suse_wait(int tid, char *sem_name){
	// Not supported
	return 0;
}

int suse_signal(int tid, char *sem_name){
	// Not supported
	return 0;
}

/*
	//inicializar todos los recursos de la biblioteca.


		int suse_create(int tid){
			int max_tid = 0; //lo pongo aca adentro porque si lo pongo afuera el max siempre va a ser 0
			if (tid > max_tid) max_tid = tid;
			return 0;
		}

		void inicializar_listas_de_estado(){
		t_list* ready = list_create();
		t_list* exec = list_create();
		t_list* blocked = list_create();
		}
*/
