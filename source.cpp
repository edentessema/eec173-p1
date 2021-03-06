// NON-FUNCTIONAL CODE
/* Still needs:
- Structure for GEL
- Structure for Buffer
- Stats methods

Still to-do:
- Flesh out Event
*/

#include
#include "event.h"

// Prototypes
void processArrival(Event*);
void processDeparture(Event*);
double nedt(double);

int main() 
{
  // Initialize data structures
  
  // Initialize variables
  const int MAXBUFFER = 100;   // Maximum number of packets the buffer can hold (**set manually**)
  int length = 0;              // Number of packets waiting in the queue (including packet in transmission)
  double time = 0;             // Current time
  int dropped_packets = 0;     // Number of dropped packets
  
  // Initialize rates (**set manually**)
  double arrival_rate = 0;
  double service_rate = 0;
  
  // Create first arrival event and insert into GEL
  double a1_arrival_time = time + nedt(arrival_rate);
  double a1_service_time = nedt(service_rate);
  Event* a1 = new Event('a', a1_arrival_time, a1_service_time);       
  GEL->insert(a1);    // NOT CORRECT, must change
  
  
  // Generate event data
  for ( i = 0; i < 100000; ++i ) {

    Event* curr_event = GEL->getFirst();    // NOT CORRECT, must change
    
    // Check if the event is an (1) arrival or a (2) departure
    if ( curr_event->getType() == 'a' ) {
      
      processArrival(curr_event);
      
    } // end (1)
     
    else {    
      
      processDeparture(curr_event);

    } // end (2)
  
  // Generate statistics from event data
  processStats();
} // END MAIN


void processArrival( Event* cur_event )
{
  // Update the current time
      time = cur_event->getArrivalTime();

      // Schedule the next arrival event
      double next_arrival_time = time + nedt(arrival_rate);
      double next_service_time = nedt(service_rate);
      Event *next_arrival = new Event('a', next_arrival_time, next_service_time);
      GEL->insert(next_arrival);       // NOT CORRECT, must change
           
      // Process the current arrival event
      // Check if: (a) If the server is ready to transmit a packet, or (b) The server is busy
      // (a) Server isn't busy (no packets in queue or transmitter), so schedule a departure
      if ( length == 0 ) {
        double curr_service_time = cur_event->getServiceTime();
        double curr_departure_time = time + curr_service_time; 
        Event *curr_departure = new Event('d', 0, curr_service_time, curr_departure_time);
        GEL->insert(curr_departure);    // NOT CORRECT, must change
        } // end (a)
      
      // (b) Server is busy
      else {
        // Place packet in queue
        if ( length-1 < MAXBUFFER )
          buffer->insert();           // NOT CORRECT, must change
        
        // Queue is full so drop the packet
        else
          ++dropped_packets;
        
        ++length;
        updateStats();                
        } // end (b)
      
    } // end (1)
}

void processDeparture( Event* cur_event )
{
       // Update the current time
      time = cur_event->getDepartureTime();
      
      updateStats();
 //     --length;
      
      if (length == 0) break;
        
      else {
 //     --length;
        buffer->dequeue();
        double curr_service_time = cur_event->getServiceTime();
        double curr_departure_time = time + curr_service_time; 
        Event *curr_departure = new Event('d', 0, curr_service_time, curr_departure_time);
        GEL->insert(curr_departure);    // NOT CORRECT, must change
       }
      
}

double nedt( double rate )
{
  double u;
  u = drand48();
  return ((-1/rate)*log(1-u));
}
  


