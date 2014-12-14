/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "KBS.h"

Counter_t loop_counter;

LongMicroSec_t loop_last_measurement;

LongMicroSec_t busy_time = 0;

HighFrequency system_frequency;

Tiny_t registered_events;

unsigned long events_thrown;

unsigned long events_processed;

unsigned int events_overflow;

unsigned long timers_expired;

fPercentage_t CPU_use;

void set_CPU_Analyser(MilliSec_t period)
{
	register_event(EVENT_ANALYSER, CbAnalyser);

	add_timer(EVENT_ANALYSER, period);
}

void CbAnalyser(void)
{
	// diff de temps (µs)
	LongMicroSec_t period = (micros() - loop_last_measurement);

	loop_last_measurement = micros();

	// freq boucle principale
	system_frequency = 1000000.0 * loop_counter / period;

	// temps CPU (%)
	CPU_use = 100.0 * busy_time / period;

	busy_time = loop_counter = 0;
}
