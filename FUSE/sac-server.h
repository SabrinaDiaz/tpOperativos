#ifndef SAC_SERVER_H_
#define SAC_SERVER_H_

#include "Herramientas_sac.h"
#include "Contexto_sac.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include "commons/bitarray.h"
#include "commons/config.h"
#include "commons/string.h"

/*******parte inicial que nos dio la catedra********/

#define GFILEBYTABLE 1024 //cant max filas tabla de nodos
#define GFILEBYBLOCK 1
#define GFILENAMELENGTH 71 //tamanio max nombre arch
#define GHEADERBLOCKS 1     // tamanio del bloque cabecera
#define BLKINDIRECT 1000    //cantidad de bloques indirectos

/********MACROS PROPIAS*************/

#define TAMANIO_DE_BLOQUE 4096
#define CANTIDAD_MAXIMA_ARCHIVOS 1024
#define BLOQUE_DE_INICIO_BITMAP 1

/****STRUCT DE LA CATEDRA***/

typedef uint32_t ptrGBloque;

typedef struct sac_header_t { // un bloque
        unsigned char sac[3]; //identificador
        uint32_t version;
        uint32_t blk_bitmap; //bloque de inicio del bitmap
        uint32_t size_bitmap; // en bloques
        unsigned char padding[4081];
} GHeader;

typedef struct sac_file_t { // un cuarto de bloque (256 bytes)
        uint8_t state; // 0: borrado, 1: archivo, 2: directorio
        unsigned char fname[GFILENAMELENGTH]; //nombre del archivo
	uint32_t parent_dir_block; //direción del bloq padre
        uint32_t file_size; //tamani arch
	uint64_t c_date; //fecha creacion
	uint64_t m_date; //fecha modificacion
        ptrGBloque blk_indirect[BLKINDIRECT];// array de punteros a bloques indirec.simples
} GFile;

/*******STRUCT PROPIOS******/

typedef struct unBloqueDelFs{
	unsigned char bytes_de_un_bloque_del_fs[TAMANIO_DE_BLOQUE];
} GBlock;

/*******FUNCIONES PROPIAS*********/

uint32_t tamanio_bitmap_en_bloques(uint32_t tamanioDisk);
void escribirHeaderEnDisco(GBlock *discoMapeado,uint32_t tamDisk);
void escribirBitmapDisco(GBlock *discoMapeadoConHeader,uint32_t tamanioDisk);
void escribirTablaDeNodosEnDisco(GBlock *discoMapeadoConHeaderYBitmap);
//funciones Ara
void atender_leer_archivo(int cliente, int tamanio);
void * escuchar_mensajes_entrantes(int cliente_fd);
void decidir_que_hacer_con_el_cliente(int cliente, t_header header);
void inicializar_server_multihilo(int cliente_fd);


#endif /* SAC_SERVER_H_ */

