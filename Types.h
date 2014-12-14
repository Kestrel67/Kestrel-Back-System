/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Types_h
#define Types_h

/**
 * Fréquence basse ~~ 65kHz
 */
typedef unsigned int LowFrequency;

/**
 *	Fréquence haute ~~4GHz
 */
typedef unsigned long HighFrequency;

/**
 *	Durée en millisecondes ms (int : 65535) ~~ +1,1 minutes
 */
typedef unsigned int MilliSec_t;

/**
 * Durée en millisecondes (ms mais relatif +/- 25 jours) : Pour le remains dans les timers
 */
typedef long RelativeMilliSec_t;

/**
 * 	Durée en millisecondes (long) ~~ 50 days
 */
typedef unsigned long LongMilliSec_t;

/**
 *	Durée en microsecondes ~~ 65 ms
 */
typedef unsigned int MicroSec_t;

/**
 *	Durée en microseconds (long) ~~ 71 minutes
 */
typedef unsigned long LongMicroSec_t;

/**
 * Durée en secondes (unsigned int)
 */
typedef unsigned int Sec_t;

/**
 *	fonction callback (sans argument, retourn void)
 */
typedef void (*callback_t)(void);

/**
 *	Petit nombre positif (1 octet)
 */
typedef uint8_t Tiny_t;

/**
 *	Evènement
 */
typedef int8_t Event_t;

/**
 * Pourcentage : 0% à 100%
 */
typedef uint8_t Percentage_t;

/**
 * Pourcentage en float : 0% à 100%
 */
typedef float fPercentage_t;

/**
 * Compteur max : 2**32 (4,2 milliards)
 */
typedef unsigned long Counter_t;

#endif
