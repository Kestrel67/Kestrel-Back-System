/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "KBS.h"

// erreur d'overflow
bool timers_queue_overflow = false;

// pointeur
uint8_t timer_pointer = 0;

// ms timer period
MilliSec_t timer_period;

// timers register
Timer_t TimersQueue[NMAX_TIMER];

// retourne l'erreur courante
bool getTimersError(void)
{
	return timers_queue_overflow;
}

// ajoute un timer
int8_t add_timer(Event_t e, MilliSec_t timeout, bool enable, bool one_time)
{
	if (timers_queue_overflow || timeout == 0)
		return -1;
		
	if (timer_pointer < NMAX_TIMER)
	{
		Timer_t timer = {e, timeout, timeout, enable, one_time};
		TimersQueue[timer_pointer] = timer;
		return timer_pointer++;
	}
	else
	{
		timers_queue_overflow = true;
		return -1;
	}
}

// iteration sur la liste des timers
void iter_timers(void)
{
	// bloque les interruptions
	noInterrupts();

	// pour chaque timer
	for (int i = 0; i < timer_pointer; i++)
	{
		if (!TimersQueue[i].enable)
			continue;

		TimersQueue[i].remains -= timer_period;

		// on regarde si le remain est à zero
		if (TimersQueue[i].remains <= 0)
		{

#if KBS_ANALYSER

			timers_expired++;

#endif

			// dans ce cas on lance/déclenche l'évènement
			event_queue(TimersQueue[i].e);

			// on remet le timer à sa position initiale
			TimersQueue[i].remains += TimersQueue[i].timeout; // + GAP = TimersQueue[i].remains; // qui correspond au temps perdu dans la boucle

			// si le timer ne doit être exécuté qu'une fois, on le désactive
			if (TimersQueue[i].one_time)
				TimersQueue[i].enable = false;
		}
	}

	// on réactive les interruptions
	interrupts();
}

// met en place le timer principale
void initialize_timers(MilliSec_t period)
{
	MsTimer2::set(period, /* void *callback(void) */ iter_timers);
	MsTimer2::start();

	timer_period = period;
}

void stop()
{
	MsTimer2::stop();
}

void start()
{
	MsTimer2::start();
}

// déphase le timer, avant initialisation
void timer_offset(Tiny_t i, MilliSec_t offset)
{
	TimersQueue[i].remains -= offset % TimersQueue[i].timeout;
}

// modifie le timeout
void set_timeout(Tiny_t i, MilliSec_t timeout, bool update_remains)
{
	if (update_remains)
		TimersQueue[i].remains += timeout - TimersQueue[i].timeout;

	TimersQueue[i].timeout = timeout;
}

// on change le paramètre one_time
void call_once(Tiny_t i)
{
	TimersQueue[i].one_time = true;
}

// vide le remains
void end_timeout(Tiny_t i)
{
	TimersQueue[i].remains = 0;
}

// reset le timer
void reset_timer(Tiny_t i)
{
	TimersQueue[i].remains = TimersQueue[i].timeout;
}

// active le timer
void enable_timer(Tiny_t i)
{
	TimersQueue[i].enable = true;
}

// désactive le timer
void disable_timer(Tiny_t i)
{
	TimersQueue[i].enable = false;
}

void debug_timers(HardwareSerial *ser)
{
	for (int i = 0; i < timer_pointer; i++)
	{
		ser->print("Event : ");
		ser->print(int(TimersQueue[i].e));
		ser->print("\ttimout");
		ser->print(TimersQueue[i].timeout);
		ser->print("\tremains:");
		ser->print(TimersQueue[i].remains);
		ser->print("\tenabled:");
		ser->print(TimersQueue[i].enable);
		ser->print("\teonetime:");
		ser->println(TimersQueue[i].one_time);
	}
}
