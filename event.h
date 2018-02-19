#ifndef EVENT_H
#define EVENT_H

class Event
{
public:

private:
  double arrival_time;
  double service_time;
  char event_type;
  Event *next_event;
  Event *previous_event;
}

class Arrival: public Event
{
public:
  Arrival( char ev_type = 'a', double arr_time, double ser_time );
}

class Departure: public Event
{
public:
  Departure( char ev_type = 'd', double dep_time );
}

#endif
