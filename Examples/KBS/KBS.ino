#include <MsTimer2.h>
#include <KBS.h>

void func(void);
void exe(void);
void disp(void);

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // event definition
  register_event(0, func);
  register_event(1, exe);
  register_event(2, disp);
  
  // timer definition
  add_timer(0, 2);
  add_timer(1, 2);
  add_timer(2, 100);
  
  // cpu analyser
  set_CPU_Analyser(1000);
  
  // system refresh rate
  initialize_timers(1);
}

void loop()
{
  // redefined simplified loop
  while(1)
  {
    loop_counter++;
    dequeue_loop();
  }
}

void func(void)
{
  digitalWrite(13, !digitalRead(13));
}

void exe(void)
{
  float r = 0.0;
  for(int a = 0; a < 20; a++)
    r += random();
}

void disp(void)
{
  Serial.print(system_frequency);
  Serial.print("\t");
  Serial.print(events_thrown);
  Serial.print("\t");
  Serial.print(CPU_use);
  Serial.print("\t");
  Serial.println(events_overflow);
}
