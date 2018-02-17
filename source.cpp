// NON-FUNCTIONAL CODE

#include
#include

int main() 
{
  // Initialize variables and data structures
  int current_time = 0;
  
  // Generate event data
  for ( i = 0; i < 100000; ++i ) {
    new_event = getEvent();
    if ( new_event == arrival )
      processArrival(new_event);
    else
      processDeparture(new_event);   
  }
  
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
