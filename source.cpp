// NON-FUNCTIONAL CODE

#include
#include

int main() 
{
  // Initialize data structures
  
  // Initialize variables
  const int MAXBUFFER = -1;   // Maximum number of packets the buffer can hold
  int length = 0;             // Number of packets waiting in the queue (including packet in transmission)
  int time = 0;               // Current time
  int dropped_packets = 0;    // Number of dropped packets
  
  // Initialize rates
  int service_rate = 0;
  int arrival_rate = 0;
  
  // Create first arrival event and insert into GEL
  a1_arrival_time = time + ran_lambda;
  Event* a1 = new Arrival(a1_arrival_time, ran_mu);       // NOTE: Sets arrival time to ran_mu
  GEL->insert(a1);
  
  
  // Generate event data
  for ( i = 0; i < 100000; ++i ) {

    Event* curr_event = GEL->getFirst();
    
    // Check if the event is an (1) arrival or a (2) departure
    // (1) If event is an arrival
    if ( curr_event->type == arrival ) {
      
      // Update the current time
      time = curr_event->event_time;

      // Schedule the next arrival event
      next_arrival_time = time + ran_lambda;
      next_service_time = ran_mu;
      Event *new_arrival = new Arrival(next_arrival_time, next_service_time);
      GEL->insert(new_arrival);       
           
      // Process the current arrival event
      // Check if: (a) If the server is ready to transmit a packet, or (b) The server is busy
      // (a) Server isn't busy (no packets in queue or transmitter), so schedule a departure
      if ( length == 0 ) {
        curr_service_time = arrival->service_time;
        curr_departure_time = time + curr_service_time; 
        Event *curr_departure = new Departure (curr_departure_time);
        GEL->insert(curr_departure);
        } // end (a)
      
      // (b) Server is busy
      else {
        // Place packet in queue
        if ( length-1 < MAXBUFFER )
          buffer->insert();
        
        // Queue is full so drop the packet
        else
          ++dropped_packet;
        
        ++length;
        updateStats();          
        } // end (b)
      
    } // end (1)
    
    // (2) If an event is a departure, process service completion
    else {    
      
      // Update the current time
      time = curr_event->event_time;
      
      updateStats();
      --length;
      
        if (length == 0) break;
        
        else {
         buffer->dequeue();
         curr_departure_time = time + curr_event->service_time;
         Event *curr_departure = new Departure (curr_departure_time);
         GEL->insert(curr_departure);
        }
      
    } // end (2)
  
  // Generate statistics from event data
  processStatistics();
}


/* 

Will need to create and initialize the following data structures:
- Doubly linked list for events
- Doubly linked list for GEL
- Priority queue for buffer

Will likely need to write the following functions:

getEvent() --> To get an event from the GEL
processArrival() --> To process arrivals
processDeparture() --> To process departures

*/
