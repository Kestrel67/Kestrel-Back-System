/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "KBS.h"

int w_pointer = 0;

int r_pointer = 0;

Tiny_t event_count = 0;

bool queue_overflow = false;

Event_t event_cach = EVENT_NULL;

callback_t TCB[NMAX_EVENT];

Event_t Queue[QUEUE_SIZE];

int display_event_queue(Tiny_t n = 0)
{
	if (n < QUEUE_SIZE)
		return Queue[n];
	return -1;
}

bool get_events_error(void)
{
	return queue_overflow;
}

void cach_event(Event_t e)
{
	event_cach = e;
}

void trig_event(bool keep = true)
{
	if (event_cach != EVENT_NULL)
	{
		event_queue(event_cach);
		
		if (!keep) event_cach = EVENT_NULL;
	}
}

void register_event(Event_t e, callback_t cb)
{
	if (e > EVENT_NULL and e < NMAX_EVENT)
	{
		TCB[e] = cb;

#if KBS_ANALYSER

		registered_events++;

#endif
	}

}

void execute_callback(Event_t e)
{
	if (TCB[e])
		TCB[e]();
}

void dequeue_loop(void)
{
	Event_t e = event_dequeue();

	if (e != EVENT_NULL)
	{

// analyse des évènements
#if KBS_ANALYSER

		unsigned long last_process_time = micros();

#endif

		execute_callback(e);

// analyse des évènements
#if KBS_ANALYSER

		busy_time += micros() - last_process_time;

#endif
	}
}

Event_t event_dequeue(void)
{
	Event_t e;
	
	// on masque les interruptions
	noInterrupts();
	
	// si la file possède au moins un élément et qu'il existe un évènement à l'emplacement du pointeur de lecture
	if (event_count-- && Queue[r_pointer] != EVENT_NULL)
	{
		// on le récupère
		e = Queue[r_pointer];

		// on suprime l'emplacement
		Queue[r_pointer++] = EVENT_NULL;

		// on met à jour le pointeur pour l'itération suivante
		r_pointer %= QUEUE_SIZE;

// analyse des évènements
#if KBS_ANALYSER

		events_processed++;

#endif
	}
	else
	{
		// si events_count == 0 ou si le pointeur est positionné sur un élément null
		e = EVENT_NULL;
		
		// on reset les pointeurs
		r_pointer = w_pointer = event_count = 0;
	}
	
	// s'il y a eu un overflow, on signal qu'une nouvelle place est disponible dans la file
	queue_overflow = false;

	// on démasque les interruptions
	interrupts();
		
	return e;
}

void event_queue(Event_t e)
{
	if (queue_overflow)
		return;
	
	// si il reste 1 emplacement libre dans la file
	if (event_count < QUEUE_SIZE)
	{
		// un evènement en plus
		event_count++;

		// on ajoute l'évènements
		Queue[w_pointer++] = e;
		
		// mise à jour du pointeur
		w_pointer %= QUEUE_SIZE;

// analyse des évènements
#if KBS_ANALYSER

		events_thrown++;

#endif

	}
	else
	{
		// sinon il y a une erreur de pointeur
		queue_overflow = true;

// analyse des évènements
#if KBS_ANALYSER

		events_overflow++;

#endif
	}
}

void dump(void)
{
	noInterrupts();
	
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		Queue[i] = EVENT_NULL;
	}
	
	w_pointer = r_pointer = event_count = 0;
	
	interrupts();
}
