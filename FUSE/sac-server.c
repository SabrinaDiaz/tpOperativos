#include "sac-server.h"

/*Es importante que commons, pthread y Shared aparezcan en el -l del Server
lo que hay aca parte o completo formaría parte del servidor*/

void atender_leer_archivo(int cliente, int tamanio) {
	logger(escribir_loguear,l_info,"Voy a recibir cosas del cli");
	tp_fuse_leer contenido_del_paquete = recibir_mensaje_char(tamanio, cliente);
	logger(escribir_loguear,l_info,"Recibi este path para leer, entre otras cosas: %s", contenido_del_paquete->path);
	free(contenido_del_paquete);
}

/* atributo header en funciones.h agregar referencia a ese .h en sac.h
 * header tiene tamanio y tipodemensaje
 * tipodemensaje=que es lo que se va a hacer, el protocolo
 * */

void * escuchar_mensajes_entrantes(int cliente_fd) {
	int status_header = 1;
	while(status_header > 0) {
	t_header header = recibir_header(cliente_fd);
	status_header = header.tamanio;
	decidir_que_hacer_con_el_cliente(cliente_fd, header);
	header = recibir_header(cliente_fd);
	status_header = header.tamanio;
	}
	logger(escribir_loguear,l_error,"El cliente se ha desconectado");
}


void decidir_que_hacer_con_el_cliente(int cliente, t_header header) {
	switch(header.tipo_de_mensaje){
	case FUSE_LEER:
		atender_leer_archivo(cliente, header.tamanio);
		break;
	default:
		break;
	}
}

void inicializar_server_multihilo(int cliente_fd) {

	pthread_t id_thread; //se va a crear un nuevo hilo
	//puntero a idhilo,atributos del hilo=null=por default,funcion que corre el hilo,argumento de esa funcion
	//importante que la funcion que corre hilo sea del tipo void
	int resultado_de_hacer_el_hilo = pthread_create(&id_thread, NULL, (void*)escuchar_mensajes_entrantes, (void*)cliente_fd);
	if(resultado_de_hacer_el_hilo != 0) { //compruba si creacion de hilo fue o no exitosa
	logger(escribir_loguear,l_error,"Error al hacer un hilo");

	}
	pthread_detach(id_thread);//devuelve recurso que usa el hilo ni bien termina
}

uint32_t tamanio_bitmap_en_bloques(uint32_t tamanioDisk) {
		double tamBlok = (tamanioDisk/TAMANIO_DE_BLOQUE/8)/TAMANIO_DE_BLOQUE;
		uint32_t tamanio_bitmap;
		if (tamBlok >= 0 & tamBlok < 1) {
			//cuando el disco es chico de 0,0009 por ejemplo y redondea a 0
			tamanio_bitmap = 1;
		} else {
			tamanio_bitmap = (uint32_t)ceil(tamBlok);
		  }

		return tamanio_bitmap;

}

void escribirHeaderEnDisco(GBlock *discoMapeado,uint32_t tamDisk){
	GHeader* cabecera = (GHeader*) discoMapeado;
			memcpy(cabecera->sac,"SAC",sizeof(cabecera->sac));
			cabecera->version = 1;
			cabecera->blk_bitmap = BLOQUE_DE_INICIO_BITMAP;
			cabecera->size_bitmap = tamanio_bitmap_en_bloques(tamDisk);

	printf("Mostrando header de disco...\n");
	printf("Mostrando nombre de file system %s\n",cabecera->sac);
	printf("Mostrando bloque de inicio de bitmap %u.\n",cabecera->blk_bitmap);
	printf("Mostrando el tamaño del bitmap:%u .\n", cabecera->size_bitmap);

}

void escribirBitmapDisco(GBlock *discoMapeadoConHeader,uint32_t tamDisk) {
	char* bitarray = (char*) discoMapeadoConHeader;

	uint32_t cantBloqBitmap = tamanio_bitmap_en_bloques(tamDisk) * TAMANIO_DE_BLOQUE;
	memset(bitarray,0,cantBloqBitmap);
	t_bitarray* bitmap = bitarray_create_with_mode(bitarray, cantBloqBitmap, LSB_FIRST);
	//1 de header
	int c;
	int bitmapOcupado=1+tamanio_bitmap_en_bloques(tamDisk);
	printf("datos del bitmap...");
	printf("bloques ocupados bitmap %u\n",bitmapOcupado);
		for(c = 0; c < bitmapOcupado; c++ ){
			bitarray_set_bit(bitmap,c);}
	printf("bitamp copiado.\n");


}

uint32_t cant_bloques_de_datos(uint32_t tamanioDisk){

	//tamanioDisk/tamBlok=cant bloques total
	//-1 de cabecera - bloques que ocupa bitmap - bloques de tabla de nodo
	uint32_t cant= tamanioDisk/TAMANIO_DE_BLOQUE-1-tamanio_bitmap_en_bloques(tamanioDisk)-1024;
	return cant;

}
void escribirTablaDeNodosEnDisco(GBlock *discoMapeadoConHeaderYBitmap) {

	GFile* miTablaDeNodos = (GFile*) discoMapeadoConHeaderYBitmap;
	for (int fila = 0; fila < GFILEBYTABLE; fila++) {
		miTablaDeNodos[fila].state = 0;
	}
}

//Ver en algun momento de sacar cosas del main y mandarlas a función aparte, como mapearMemoria
//(hasta obtener el disco mapeado por ej.)

int main(void) {

	inicializar_logger();
	logger(escribir_loguear,l_info,"Fuse esta listo para recibir peticiones");
	struct stat disco;
	t_config* configuracion = config_create("/home/utnso/tp-2019-2c-The-PowerFuse-girls/FUSE/sac.config");
	printf("La ruta del archivo de configuración es: %s.\n",configuracion->path);
	char* rutaDelDisco = config_get_string_value(configuracion,"RUTA_DEL_DISCO");
	printf("La ruta de disco es %s.\n", rutaDelDisco);
	printf("Los atributos del disco son\n");
	stat(rutaDelDisco, &disco);
	printf("Tamaño del archivo %d bytes.\n",disco.st_size);

	uint32_t tamanioDisk = disco.st_size;
	uint32_t  fd = open(rutaDelDisco,O_RDWR);
	GBlock* discoMapeado;
	discoMapeado = mmap(NULL, disco.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	escribirHeaderEnDisco(discoMapeado,tamanioDisk);
	GBlock* discoMapeadoConHeader = discoMapeado + 1;
	escribirBitmapDisco(discoMapeadoConHeader,tamanioDisk);
	GBlock* discoMapeadoConHeaderYBitmap = discoMapeadoConHeader + tamanio_bitmap_en_bloques(tamanioDisk);
	escribirTablaDeNodosEnDisco(discoMapeadoConHeaderYBitmap);

	munmap(discoMapeado,tamanioDisk);
	close(fd);

	configurar_signals();

	int listen_socket_sac = escuchar_en(listen_port);
	while(1) {
		int cliente_fd = aceptar_conexion(listen_socket_sac);
		inicializar_server_multihilo(cliente_fd);
	}

	close(listen_socket_sac);
	return 0;
}


char* recibir_path(int sacCli){
	//chequear si hace lo que queremos
	//si no revision de sockets recibir
	t_header header = recibir_header(sacCli);
	char* path=recibir_mensaje_char(header.tamanio,sacCli);
	return path;
}

GFile* obtenerNodosCandidatos(char* nombreArch,GFile* tablaNodos){
	//se carga nodosCandidatos con los nodos que cumplen con que
	//nombre de archivo igual a nombreArch
	GFile* nodosCandidatos;
	int desplazamiento=0;
	//recorrer tabla de nodos
	for(int pos=0;pos<GFILEBYTABLE;pos++){
		//compara nombre nodo con el nombre pasado por parametro
		if(string_equals_ignore_case(tablaNodos[pos].fname,nombreArch)){
			//duda no se cual de los dos va
			//primera opcion
		nodosCandidatos+desplazamiento=tablaNodos[pos];
		//segunda opcion
		memcpy(nodosCandidatos+desplazamiento,tablaNodos[pos],sizeof(GFile));
		desplazamiento=desplazamiento+1;
		}

	}

	return nodosCandidatos;
}


GFile* obtenerTablaDeNodosDelDisco(){

	t_config* configuracion = config_create("/home/utnso/tp-2019-2c-The-PowerFuse-girls/FUSE/sac.config");
	printf("La ruta del archivo de configuración es: %s.\n",configuracion->path);
	char* rutaDelDisco = config_get_string_value(configuracion,"RUTA_DEL_DISCO");
	printf("La ruta de disco es %s.\n", rutaDelDisco);
	printf("Los atributos del disco son\n");
	struct stat disco;
	stat(rutaDelDisco, &disco);
	printf("Tamaño del archivo %d bytes.\n",disco.st_size);

	uint32_t tamanioDisk = disco.st_size;
	uint32_t  fd = open(rutaDelDisco,O_RDWR);
	GBlock* discoMapeado;
	discoMapeado = mmap(NULL, disco.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	GBlock* discoMapeadoConHeaderYBitmap = discoMapeado+1+tamanio_bitmap_en_bloques(tamanioDisk);
	GFile* nodos=(GFile*) discoMapeadoConHeaderYBitmap;
	return nodos;
}

GFile* obtener_nodo(char* path,GFile* tablaDeNodos){
	//Separa un string dado un separador
	char** listaDeRutas= string_split(path,"/");
	//path=home/utnso/speakSpanish/idioma/nativo
	//lista de rutas=[home,utnso,speakSpanish,idioma,nativo]
	int tamanioLista=sizeof(listaDeRutas);
	int posMax=tamanioLista-1;
}

//lista de rutas, la ultima se busca en tabla de nodos
	//por nombre
	//ver cómo acceder a tabla de nodos
	//si la lista obtenida tiene más de un elemento hay que buscar
	// los padres y ver si coinciden con la anteultima ruta
	//y asi
	//hasta llegar a / que debe devolver 0 y ahi no exite archivo
