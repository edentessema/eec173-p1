#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
  Event ( char ev_type, double arr_time = 0, double ser_time = 0, double dep_time = 0, Event* prev = NULL, Event* next = NULL )
  {
    event_type = ev_type;
    arrival_time = arr_time;
    service_time = ser_time;
    departure_time = dep_time;
    prev_event = prev;
    next_event = next;
  }
  char getType(void) { return event_type; }
  double getArrivalTime(void) { return arrival_time; }
  double getServiceTime(void) { return service_time; }
  double getDepartureTime(void) { return departure_time; }

private:
  char event_type;
  double arrival_time;
  double service_time;
  double departure_time;
  Event *next_event;
  Event *previous_event;
}


#endif
