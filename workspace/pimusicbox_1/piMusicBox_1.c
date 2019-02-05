/*
 *	piMusicBox_1.h
 *	Main program body
 */

/* Includes -----------------------------------------------------------------*/
#include "piMusicBox_1.h"
#include "fsm.h"
#include "tmr.h"
#include "mfrc522.h"
#include "rfid.h"
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/* Defines -----------------------------------------------------------------*/
#define GPIO_SALIDA 18
#define GPIO_ENTRADA 5
#define DEBOUNCE_TIME 500

/* Private variables -----------------------------------------------------------------*/
int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};

int *frecuencias[] = {frecuenciaDespacito,frecuenciaGOT,frecuenciaTetris,frecuenciaStarwars};
int *tiempos[] = {tiempoDespacito,tiempoGOT,tiempoTetris,tiempoStarwars};
char *arruid[] = {"","","906DDFA4","6431B979"};
char *nombres[] = {"Despacito", "GOT", "Tetris", "StarWars"};
int numNotas[] = {160,518,55,59};

enum fsm_state{
	WAIT_START,
	WAIT_NEXT,
	WAIT_END,
	WAIT_CARD,
	WAIT_CHECK,
	WAIT_PLAY
};

volatile int flags = 0;
int debounceTime = DEBOUNCE_TIME;

char* UID1 = "906DDFA4";
char* UID2 = "6431B979";
//char* UIDleido =(char*)malloc(9*sizeof(char));
char* UIDleido = "00000000";
//int posicion = 0;

tmr_t* timer_tmr;

/**
 * Subrutina de atención a interrupción del timer
*/
static void timer_isr (){
	piLock (FLAGS_KEY);
	flags |= FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);
}


//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

/**
 * Inicializa las variables para la reproducción
 *
 * @param melodia				Melodía a inicializar
 * @param nombre				Nombre de la melodía
 * @param array_frecuencias		frecuencias seleccionadas
 * @param array_duraciones		duraciones seleccionadas
 * @param num_notas				número total de notas de la melodía
 * @return num_notas			número total de notas de la melodía
*/
int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	strcpy(melodia->nombre,nombre);
	int i;
	for(i=0;i<num_notas;i++){
		melodia->duraciones[i]=array_duraciones[i];
		melodia->frecuencias[i]=array_frecuencias[i];
	}
	melodia->num_notas = num_notas;
	return melodia->num_notas;
}

/**
 * Inicializa el reproductor
 *
 * @param this		gestor de máquina de estados
*/
void InicializaPlayer(fsm_t* this){
	TipoPlayer *p_player;
    p_player=(TipoPlayer*)(this->user_data);

	p_player->posicion_nota_actual = 0;
//	p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[0]*1.2;
//	p_player->duracion_nota_actual = p_player->melodia->duraciones[0]*0.6;
	p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[0];
	p_player->duracion_nota_actual = p_player->melodia->duraciones[0];

	tmr_startms(timer_tmr, p_player->duracion_nota_actual);

	piLock(FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START; //desactivar todos los flags
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY); //imprimir estado actual
	printf("[PLAYER][InicializaPlayer][NOTA %d][FREC %d][DURA %d]\n",p_player->posicion_nota_actual+1,p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
	softToneWrite(GPIO_SALIDA,p_player->frecuencia_nota_actual); //salida de onda cuadrada en GPIO_SALIDA
	piUnlock (STD_IO_BUFFER_KEY);

}

/**
 * Actualiza a la nota siguiente
 *
 * @param this		gestor de máquina de estados
*/
void ActualizaPlayer(fsm_t* this){
	TipoPlayer *p_player;
	p_player=(TipoPlayer*)(this->user_data);
	p_player->posicion_nota_actual++;



	piLock(FLAGS_KEY); //desactivar flag
	flags &= ~FLAG_PLAYER_START;
	piUnlock(FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY); //imprimir estado actual
	if(p_player->posicion_nota_actual< p_player->melodia->num_notas){
		//	p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[p_player->posicion_nota_actual]*1.2;
		//	p_player->duracion_nota_actual = p_player->melodia->duraciones[p_player->posicion_nota_actual]*0.6;
		p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[p_player->posicion_nota_actual];
		p_player->duracion_nota_actual = p_player->melodia->duraciones[p_player->posicion_nota_actual];

		printf("\n[PLAYER][ActualizaPlayer][NUEVA NOTA %d de %d]\n",p_player->posicion_nota_actual+1, p_player->melodia->num_notas);
		printf("[PLAYER][ComienzaNuevaNota][NOTA %d][FREC %d][DURA %d]\n",p_player->posicion_nota_actual+1,p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
	}else{
		softToneWrite(GPIO_SALIDA,0);
		piLock (FLAGS_KEY);
			flags |= FLAG_PLAYER_END;
			flags |= FLAG_SYSTEM_END; //para que acabe tambien en el detector de tarjetas
		piUnlock (FLAGS_KEY);
		printf("\n[PLAYER][ActualizaPlayer][REPRODUCIDAS TODAS LAS NOTAS]\n");
	}
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * Para el reproductor
 *
 * @param this		gestor de máquina de estados
*/
void StopPlayer(fsm_t* this){
	TipoPlayer *p_player;
    p_player=(TipoPlayer*)(this->user_data);

	softToneWrite(GPIO_SALIDA,0);
	p_player->frecuencia_nota_actual = 0;
	p_player->duracion_nota_actual = 0;

	piLock(FLAGS_KEY); //desactivar todos los flags
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY); //imprimir estado actual
	printf("\n[PLAYER][StopPlayer]\n");
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * Pone a reproducir la nota actual
 *
 * @param this		gestor de máquina de estados
*/
void ComienzaNuevaNota(fsm_t* this){
	TipoPlayer *p_player;
	p_player=(TipoPlayer*)(this->user_data);

	tmr_startms(timer_tmr, p_player->duracion_nota_actual); //empieza el timer correspondiente a la nota actual

	piLock(FLAGS_KEY); //desactivar flag
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);


	piLock (STD_IO_BUFFER_KEY);
	softToneWrite(GPIO_SALIDA,p_player->frecuencia_nota_actual); //salida de onda cuadrada en GPIO_SALIDA
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * Indica que no queda notas por reproducir
 *
 * @param this		gestor de máquina de estados
*/
void FinalMelodia(fsm_t* this){

	piLock(FLAGS_KEY); //desactivar todos los flags
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	flags |= FLAG_SYSTEM_END;
	piUnlock(FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY); //indica el estado actual
	printf("\n[PLAYER][FinalMelodia]\n");
	printf("[FinalMelodia][FLAG_PLAYER_END]\n");
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * Inicializa el hw de deteccion y lectura.
 *
 * @param this		gestor de máquina de estados
*/
void ComienzaSistema(fsm_t* this){
	piLock (STD_IO_BUFFER_KEY);
	printf("\nSistema de deteccion de tarjetas esta listo \n");
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * No hace nada mientras espera
 *
 * @param this		gestor de máquina de estados
*/
void EsperoTarjeta(fsm_t* this){}

/**
 * Analiza  si el id de la tarjeta detectada es valido.
 *
 * @param this		gestor de maquina de estados
*/
void LeerTarjeta(fsm_t* this){
	TipoSistema *p_sistema;
	p_sistema=(TipoSistema*)(this->user_data);
	UIDleido = read_id();

	int i;
	for(i=0; i<4; i++){
		if(strcmp(UIDleido,arruid[i]) == 0){
			//posicion = i;
			p_sistema->uid_tarjeta_actual_string = UIDleido;
			p_sistema->pos_tarjeta_actual=i;

			piLock (STD_IO_BUFFER_KEY);
			printf("\nTarjeta valida \n");
			piUnlock (STD_IO_BUFFER_KEY);

			piLock (FLAGS_KEY);
			flags |= FLAG_VALID_CARD;
			piUnlock (FLAGS_KEY);
		}
	}
}

/**
 * Si el id de la tarjeta no es valido.
 *
 * @param this		gestor de máquina de estados
*/
void DescartaTarjeta(fsm_t* this){
	piLock (STD_IO_BUFFER_KEY);
	printf("\nTarjeta descartada \n");
	piUnlock (STD_IO_BUFFER_KEY);
}

/**
 * Inicializa una de las melodias en funcion del id detectado.
 *
 * @param this		gestor de máquina de estados
*/
void ComienzaReproduccion(fsm_t* this){
	TipoSistema *p_sistema;
	p_sistema=(TipoSistema*)(this->user_data);
	int posicion = p_sistema->pos_tarjeta_actual;

	InicializaMelodia(p_sistema->player.melodia,
			nombres[posicion],frecuencias[posicion],tiempos[posicion],numNotas[posicion]);


	piLock(FLAGS_KEY);
	flags |= FLAG_PLAYER_START; //El sistema esta listo para empezar a reproducir
	piUnlock(FLAGS_KEY);


}

/**
 * Miro si la tarjeta continua.
 *
 * @param this		gestor de maquina de estados
*/
void ComprueboTarjeta(fsm_t* this){
	if(strcmp(UIDleido,"00000000")== 0){
		piLock (FLAGS_KEY);
		flags &= ~FLAG_CARD_IN; //la tarjeta ya no esta disponible
		piUnlock (FLAGS_KEY);
	}
}

/**
 * Para la reproduccion cuando detecta que se ha retirado la tarjeta.
 *
 * @param this		gestor de maquina de estados
*/
void CancelaReproduccion(fsm_t* this){
	piLock(FLAGS_KEY);
	flags |= FLAG_PLAYER_STOP; //parar la reproduccion en la otra maquina de estados
	flags &= ~FLAG_SYSTEM_END;
	flags &= ~FLAG_CARD_IN;
	flags &= ~FLAG_VALID_CARD;
	piUnlock(FLAGS_KEY);
}

/**
 * Indica que no queda notas por reproducir
 *
 * @param this		gestor de maquina de estados
*/
void FinalizaReproduccion(fsm_t* this){
	piLock(FLAGS_KEY);
	flags &= ~FLAG_SYSTEM_END;
	flags &= ~FLAG_CARD_IN;
	flags &= ~FLAG_VALID_CARD;
	piUnlock (FLAGS_KEY);
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaPlayerStart(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaFinalMelodia(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaNuevaNota(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & ~FLAG_PLAYER_END); //aseguramos que el flag esté a 0 para seguir reproduciendo
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaPlayerStop(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaNotaTimeout(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);

	return result;
}


/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaComienzo(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_SYSTEM_START);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int TarjetaNoDisponible(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & ~FLAG_CARD_IN); // nos aseguramos de que no hay tarjeta
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int TarjetaDisponible(fsm_t* this){

	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_CARD_IN);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int TarjetaNoValida(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & ~FLAG_VALID_CARD); //nos aseguramos de que la tarjeta no es valida
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int TarjetaValida(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_VALID_CARD);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Subrutina de comprobacion del flag
 *
 * @param this		gestor de máquina de estados
*/
int CompruebaFinalReproduccion(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_SYSTEM_END);
	piUnlock (FLAGS_KEY);

	return result;
}


//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

// int systemSetup (void): procedimiento de configuracion del sistema.
// Realizará, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerías (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periódicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int systemSetup (void) {
	int x=0;

	piLock (STD_IO_BUFFER_KEY); //cerrojo para asegurar mutex
	if(wiringPiSetupGpio() < 0){ //setup de wiringPi
		printf("Error Setup\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}

	//pinMode(PIN, OUTPUT);
	if(softToneCreate(GPIO_SALIDA)==-1){ //inicialización del generador de ondas cuadradas
		printf("Error softtone\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}

	x = piThreadCreate (thread_explora_teclado); //hebra encargada de detectar pulsaciones del teclado

	if (x != 0){
		printf("Error init teclado\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}

	pinMode(GPIO_ENTRADA, INPUT); //configurar el puerto de entrada
	wiringPiISR(GPIO_ENTRADA, INT_EDGE_BOTH, &detecta_tarjeta); //detección de flancos de subida y bajada
	piUnlock (STD_IO_BUFFER_KEY);

	initialize_rfid();

	piLock(FLAGS_KEY);
	flags |= FLAG_SYSTEM_START;
	piUnlock(FLAGS_KEY);
	return 1;
}

/**
 * Inicialización de la máquina de estados
 *
 * @param reproductor_fsm		gestor de máquina de estados
*/
void fsm_setup(fsm_t* reproductor_fsm){
	piLock(FLAGS_KEY);
	flags = 0;
	piUnlock(FLAGS_KEY);
}

// wait until next_activation (absolute time)
void delay_until (unsigned int next){
  unsigned int now = millis();
  if (next > now) {
	  delay (next - now);
  }
}

//------------------------------------------------------
// PI_THREAD (thread_explora_teclado): Thread function for keystrokes detection and interpretation
//------------------------------------------------------
PI_THREAD (thread_explora_teclado) {
	char teclaPulsada;

	while(1) {
		delay(10); // Wiring Pi function: pauses program execution for at least 10 ms

		piLock (STD_IO_BUFFER_KEY);

		if(kbhit()) {
			teclaPulsada = kbread();
			printf("\n[KBHIT][%c]\n", teclaPulsada);

			switch(teclaPulsada) { //modo piano
	/*			case 's':
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_START;
					flags |= FLAG_NOTA_TIMEOUT;
					piUnlock (FLAGS_KEY);
					break;

				case 't':
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_STOP;
					flags |= FLAG_PLAYER_END;
					piUnlock (FLAGS_KEY);
					break;*/

				case 'r':
					UIDleido = read_id();
					break;

				case 'q':
					exit(0);
					break;

				default:
					piLock (FLAGS_KEY);
					//flags |= FLAG_PLAYER_START;
					flags |= FLAG_SYSTEM_START;
					piUnlock (FLAGS_KEY);
					break;
			}
		}
		piUnlock (STD_IO_BUFFER_KEY);
	}
}

/**
 * Subrutina de atención a interrupción
 * se llama cuando detecta una tarjeta
*/
void detecta_tarjeta(){
	if(millis () < debounceTime){ //evita rebote
		debounceTime = millis () + DEBOUNCE_TIME ;
	}

	if (digitalRead(GPIO_ENTRADA) == HIGH) { //cuando detecta un flanco de subida
		piLock (FLAGS_KEY);
		//flags |= FLAG_PLAYER_START;
		flags |= FLAG_CARD_IN;
		piUnlock (FLAGS_KEY);
		piLock (STD_IO_BUFFER_KEY);
		printf("\nTarjeta detectada \n");
		piUnlock (STD_IO_BUFFER_KEY);
	} else {								//cuando detecta un flanco de bajada
		piLock (FLAGS_KEY);
		flags &= ~FLAG_CARD_IN;
		piUnlock (FLAGS_KEY);
		piLock (STD_IO_BUFFER_KEY);
		printf("\nTarjeta sacada \n");
		piUnlock (STD_IO_BUFFER_KEY);
	}

	while (digitalRead (GPIO_ENTRADA) == LOW) {  //evita rebote
		delay(1);
	}

	debounceTime = millis () + DEBOUNCE_TIME;
}

//------------------------------------------------------
// main() programa principal
//------------------------------------------------------
int main ()
{
	/* Variables locales*/
	TipoSistema sistema;
	TipoMelodia melodia;
	TipoPlayer player;
	//char * nombre = "Tetris";
	unsigned int next;


	// Máquina de estados: lista de transiciones
	// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
	fsm_trans_t reproductor[] ={
			{WAIT_START,CompruebaPlayerStart,WAIT_NEXT,InicializaPlayer},
			{WAIT_NEXT,CompruebaNotaTimeout,WAIT_END,ActualizaPlayer},
			{WAIT_END,CompruebaFinalMelodia,WAIT_START,FinalMelodia},
			{WAIT_END,CompruebaNuevaNota,WAIT_NEXT,ComienzaNuevaNota},
			{WAIT_NEXT,CompruebaPlayerStop,WAIT_START,StopPlayer},
			{-1,NULL,-1,NULL},
	};

	fsm_trans_t tarjeta[] ={
			{WAIT_START,CompruebaComienzo,WAIT_CARD,ComienzaSistema},
			{WAIT_CARD,TarjetaDisponible,WAIT_CHECK,LeerTarjeta},
			{WAIT_CARD,TarjetaNoDisponible,WAIT_CARD,EsperoTarjeta},
			{WAIT_CHECK,TarjetaValida,WAIT_PLAY,ComienzaReproduccion},
			{WAIT_CHECK,TarjetaNoValida,WAIT_CARD,DescartaTarjeta},
			{WAIT_PLAY,TarjetaDisponible,WAIT_PLAY,ComprueboTarjeta},
			{WAIT_PLAY,CompruebaFinalReproduccion,WAIT_START,FinalizaReproduccion},
			{WAIT_PLAY,TarjetaNoDisponible,WAIT_START,CancelaReproduccion},
			{-1,NULL,-1,NULL},
	};

	fsm_t* reproductor_fsm = fsm_new(WAIT_START, reproductor, &(sistema.player)); //creamos una máquina de estados
	fsm_t* tarjeta_fsm = fsm_new(WAIT_START, tarjeta, &(sistema)); //creamos una máquina de estados

	/* Inicialización*/
	//InicializaMelodia(&melodia,nombre,frecuenciaTetris,tiempoTetris,sizeof(tiempoTetris)/sizeof(int));
	player.melodia = &melodia;
	sistema.player = player;
	fsm_setup(reproductor_fsm);
	fsm_setup(tarjeta_fsm);
	timer_tmr = tmr_new(timer_isr);
	systemSetup();

	/* Bucle infinito*/
	next = millis();
	while (1){
		fsm_fire (reproductor_fsm); //cambio de estados
		fsm_fire (tarjeta_fsm); //cambio de estados
		next += CLK_MS;
		delay_until (next);
	}

	/* Libera memoria*/
	fsm_destroy (reproductor_fsm);
	fsm_destroy (tarjeta_fsm);
	tmr_destroy (timer_tmr);



}
