/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

//***** ANALYSER MODE *****//
#define KBS_ANALYSER 1

#include <Arduino.h>
#include <MsTimer2.h>
#include "Types.h"
#include "Frequencies.h"
#include "Timers.h"
#include "Analyser.h"


#ifndef KBS_h
#define KBS_h

/**
 *	Taille du registre des évènements
 */
#define NMAX_EVENT 20

/**
 *  Taille de la file
 */
#define QUEUE_SIZE 20

/**
 *	Evènement null
 */
#define EVENT_NULL -1

/**
 *	Pointeur d'écriture
 */
extern int w_pointer;

/**
 *  Pointeur de lecture
 */
extern int r_pointer;

/**
 *	Nombre d'évènements dans la file à l'instant t
 */
extern Tiny_t event_count;

/**
 *	erreur d'overflow
 */
extern bool queue_overflow;

/**
 *	Cache de l'évènement en quick-triger
 */
extern Event_t event_cach;

/**
 *	Tables d'associations [event => callback]
 */
extern callback_t TCB[NMAX_EVENT];

/**
 *	File circulaire des évènements
 */
extern Event_t Queue[QUEUE_SIZE];

/**
 *	Retourne le n ème élément du tableau
 *	@param unsigned int n
 */
int display_event_queue(Tiny_t n);

/**
 *	Retourne les erreurs
 */
bool get_events_error(void);

/** 
 *	Place l'évènement e en cache
 *	@param Event_t e
 */
void cach_event(Event_t e);

/**
 *	Déclenche l'évènement en cache
 *	@param bool keep, suppression du cache après déclenchement
 */
void trig_event(bool keep);

/**
 *	Enregistre une association [Event_t => callback_t]
 *	@param Event_t e
 *	@param callback_t cb
 */
void register_event(Event_t e, callback_t cb);

/**
 *	Exécute la callback associée à l'evènement e
 *	@param Event_t e
 */
void execute_callback(Event_t e);

/**
 *	Traitement du 1er évènement de la file
 */
void dequeue_loop(void);

/**
 *	Retourne le premier élément non traité de la file
 *	@return Event_t
 */
Event_t event_dequeue(void);

/**
 *	Ajoute un évènement dans la file
 *	@param Event_t e
 */
void event_queue(Event_t e);

/**
 *	On vide la file des évènements (forcage du vidage)
 */
void dump(void);

#endif
