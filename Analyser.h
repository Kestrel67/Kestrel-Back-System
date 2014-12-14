/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Analyser_h
#define Analyser_h

/**
 * Evènement attaché à l'analyseur (par défaut dernier évènement attribuable
 */
#define EVENT_ANALYSER NMAX_EVENT - 1

/**
 * Nombre d'itérations de la boucle principale depuis la dernière analyse
 */
extern Counter_t loop_counter;

/**
 * Temps processeur passé à traiter la boucle principale (depuis la dernière analyse)
 */
extern LongMicroSec_t loop_last_measurement;

/**
 * Ttemps passé à éxécuter des fonctions (depuis la dernière analyse)
 */
extern LongMicroSec_t busy_time;

/**
 * Fréquence d'éxécution de la boucle principale
 */
extern HighFrequency system_frequency;

/**
 * Pourcentage d'utilisation CPU
 */
extern fPercentage_t CPU_use;

/**
 * Nombre d'évènements enregistrés
 */
extern Tiny_t registered_events;

/**
 * Nombre d'évènements lancés
 */
extern unsigned long events_thrown;

/**
 * Nombre d'évènements traités
 */
extern unsigned long events_processed;

/**
 * Nombre dévènements perdus (passés en overflow)
 */
extern unsigned int events_overflow;

/**
 * Nombre timers ayant expirés
 */
extern unsigned long timers_expired;

/**
 * Mise en place de la fonction d'analyse
 */
void set_CPU_Analyser(MilliSec_t period = FREQUENCY_10Hz);

/**
 * Callback associée à la fonction d'analyse
 */
void CbAnalyser(void);

#endif

