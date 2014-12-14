/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */
 
#ifndef Timers_h
#define Timers_h

/**
 * Nombre du registre des timers
 */
#define NMAX_TIMER 15

/**
 * Période minimale du timer principale
 */
#define MAIN_TIMER_MIN_PERIOD 1 // ms = 1000Hz

/**
 * Période efficace du timer principale
 */
#define MAIN_TIMER_EFFICENT_PERIOD 2 // ms = 500Hz

/**
 *	Structure Timer_t (Précision milliseconde)
 *	@var Event_t e 					// évènement associé
 *	@var MilliSec_t timeout 		// période
 *	@var MilliSec_t remains		 	// temps restant avant d'éxécuter la fonction associée
 *	@var bool enable 				// état du timer (on / off)
 *	@var bool one_time 				// expiration unique (ou éxécution réitérée)
 */
struct Timer_t {
	Event_t e;
	MilliSec_t timeout;
	RelativeMilliSec_t remains;
	bool enable;
	bool one_time;
};

/**
 *	Type de la structure
 */
typedef Timer_t Timer_t;

/**
 *	Valeur d'erreur (overflow) (MsTimer2)
 */
extern bool timers_queue_overflow;

/**
 *	Période du timer (en ms)
 */
extern MilliSec_t timer_period;

/**
 *	Registre des timers enregistrés
 */
extern Timer_t TimersQueue[NMAX_TIMER];

/**
 *	Pointeur des timers, indique à quel emplacement ajouter un nouveau timer
 */
extern uint8_t timer_pointer;

/**
 *	Retourne true si une erreur d'overflow à eu lieu
 *	@return bool timers_overflow
 */
bool getTimersError(void);

/**
 *	Ajoute une timer à la liste d'exécution, associé à un évènement
 *	@param Event_t e
 *	@param MilliSec_t timer (ms)
 *	@param bool enabled : état (on / of))
 *	@param bool one_time_timer : exécution réitérée
 *	@return retourne l'indice du timer ajouté
 */
int8_t add_timer(Event_t e, MilliSec_t timeout, bool enable = true, bool one_time = false);

/**
 *	Fonction callback du timer princiaple
 *	pour chaque timer vérifie s'il doit y avoir déclenchement dévènement ou non
 *	@param void
 */
void iter_timers(void);

/**
 *	Met en place le timer princiaple
 *	@param MilliSec_t period (ms), conseillé MAIN_TIMER_MIN_PERIOD (1ms = 1000Hz)
 */
void initialize_timers(MilliSec_t period = MAIN_TIMER_MIN_PERIOD);

/**
 *	Stop temporairement les itérations du timer
 */
void stop(void);

/**
 *	Redémarre les itérations du timer
 */
void start(void);

/**
 * Déphase un timer
 * @param Tiny_t i : id du timer
 * @param MilliSec_t offset : décalage (en ms)
 *
 * !!! : à utiliser avant l'initialisation, quand la valeur de "remain" est égale à celle de "timeout"
 */
void timer_offset(Tiny_t i, MilliSec_t offset);

/**
 *	Change la période du timer à l'indice i
 *	@param Tiny_t i, indice du timer
 *	@param MilliSec_t timeout, nouvelle valeur de la période
 *	@param bool update_remains : si true, reinitialisation du "remain"
 */
void set_timeout(Tiny_t i, MilliSec_t timeout, bool update_remains = false);

/**
 * Change le paramètre one_time du timer (exécution réitérée)
 */
void call_once(Tiny_t i);

/**
 * Réinitialise le remains à 0 à l'indice i (appel de la callback immédiat)
 * @param Tiny_t i
 */
void end_timeout(Tiny_t i);

/**
 * 	On réinitialise le timer, remains = timeout
 * 	@param Tiny_t i : indice du timer
 */
void reset_timer(Tiny_t i);

/**
 *	Active le timer à l'indice i
 *	@param Tiny_t i : indice du Timer
 */
void enable_timer(Tiny_t i);

/**
 *	Désactive le timer à l'indice i
 *	@param Tiny_t i : indice du Timer
 */
void disable_timer(Tiny_t i);

/**
 *	Supprime un timer de la liste d'éxécution
 *	@param Event_t e
 */
void remove_timer(Event_t e);

/**
 *	Fonction de deboguage
 */
// not implemented
//void debug_timers(HardwareSerial *ser = &Serial);

#endif
