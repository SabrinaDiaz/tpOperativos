#ifndef hilolay_h__
#define hilolay_h__

#include <Functions.h>

	/* Interface for programs, this is what the programs should use and is implemented in hilolay_internal
Interfaz para programas, esto es lo que los programas deberían usar y se implementa en hilolay_internal */

	/* TODO: Not working in program without struct, even though it has typedef
	No funciona en un programa sin estructura, a pesar de que tiene typedef */

	typedef struct hilolay_t {
		int tid;
	} hilolay_t;

	typedef struct hilolay_attr_t {
		int attrs;
	} hilolay_attr_t;

	/**
	 * Initializes the library. Implemented in the client interface.
     Inicializa la biblioteca. Implementado en la interfaz del cliente
	 *
	 * Must call hilolay.c#_init function
	 */
	void hilolay_init(void);

	/**
	 * TODO
	 */
	int hilolay_create(hilolay_t *thread, const hilolay_attr_t *attr, void *(*start_routine)(void *), void *arg);

	/**
	 * TODO
	 */
	int hilolay_yield(void);

	/**
	 * TODO
	 */
	int hilolay_join(hilolay_t *thread);

	/**
	 * TODO
	 */
	int hilolay_get_tid(void);
#endif // hilolay_h__
