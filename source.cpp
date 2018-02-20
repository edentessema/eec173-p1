// NON-FUNCTIONAL CODE
/* Still needs:
- Stats methods

Still to-do:
- Flesh out Event
*/

#include
#include "event.h"

// Prototypes
void processArrival(Event*);
void processDeparture(Event*);
void insertGEL(Event *, Event *&, Event *&);
void insertBuffer(Event *, Event *&, Event *&);
Event* removeEvent(Event *&);
double nedt(double);

int main() 
{
  // Initialize data structures
  Event *headGEL = NULL;    //initializing head of GEL Queue
  Event *tailGEL = NULL;    //initializing tail of GEL Queue
  Event *headBuffer = NULL;    //initializing head of Buffer Queue
  Event *tailBuffer = NULL;    //initializing tail of Buffer Queue

  
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

  // if you agree with how insertGEL looks :D
  insertGEL (a1, headGEL, tailGEL);                   // insert function for insert into GEL
                                                      // pass in event node, head of GEL, and tail of GEL
  
  // implemented in line above: GEL->insert(a1);    // NOT CORRECT, must change
  
  
  // Generate event data
  for ( i = 0; i < 100000; ++i ) {

    // "getFirst" implemented by a dequeue from GEL
    Event* curr_event = removeEvent(headGEL);
    // implemented in line above: Event* curr_event = GEL->getFirst();    // NOT CORRECT, must change
    
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
     
      // if you agree with how insertGEL looks :D
      insertGEL (next_arrival, headGEL, tailGEL);
      //implemented in line above: GEL->insert(next_arrival);       // NOT CORRECT, must change
           
      // Process the current arrival event
      // Check if: (a) If the server is ready to transmit a packet, or (b) The server is busy
      // (a) Server isn't busy (no packets in queue or transmitter), so schedule a departure
      if ( length == 0 ) {
        double curr_service_time = cur_event->getServiceTime();
        double curr_departure_time = time + curr_service_time; 
        Event *curr_departure = new Event('d', 0, curr_service_time, curr_departure_time);
        
        // if you agree with how insertGEL looks :D
        insertGEL (curr_departure, headGEL, tailGEL);
        //implemented in line above: GEL->insert(curr_departure);    // NOT CORRECT, must change
        } // end (a)
      
      // (b) Server is busy
      else {
        // Place packet in queue
        if ( length-1 < MAXBUFFER )
          
          //if you agree with how insertBuffer looks :D
          insertBuffer(cur_event, headBuffer, tailBuffer);
          // implemented in the line above: buffer->insert();           // NOT CORRECT, must change
        
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
        //deque
        buffer->dequeue();                                      /* NEED TO GRAB GENERAL DEQUEUE METHOD*/
        double curr_service_time = cur_event->getServiceTime();
        double curr_departure_time = time + curr_service_time; 
        Event *curr_departure = new Event('d', 0, curr_service_time, curr_departure_time);
      
        // if you agree with how insertGEL looks :D
        insertGEL (curr_departure, headGEL, tailGEL);
        //implemented in line above: GEL->insert(curr_departure);    // NOT CORRECT, must change
       }
      
}

void insertGEL(Event *e_insert, Event *&head, Event *&tail)
{
  if (head == NULL && tail == NULL)
  {
    head = e_insert;
    tail = e_insert;
  } else {
    Event *iterator = head;         //create pointer to iterate through queue to check priority
    
    while (iterator->service_time < e_insert->service_time)
      {iterator = iterator->next_event;}          // increment iterator until the priority is reached/just-passed
    if (iterator->service_time > e_insert->service_time)
    {
      head = e_insert;
      e_insert->next_event = iterator;
      iterator->previous_event = e_insert;
    }
  }
}

/*THIS insertBuffer() CAN ALSO BE REPLACED WITH A REGULAR ENQUEUE IF WE FIND ONE*/
void insertBuffer(Event *e_insert, Event *&head, Event *&tail)
{
  Event *temp  = tail;
  if (head == NULL && tail == NULL)
  {
    head = e_insert;
    tail = e_insert;
  } else {
      tail = e_insert;
      tail->previous_event = temp;
      temp->next_event = e_insert;
  }
}

Event* removeEvent(Event *&head)
{
  Event *temp = head;
  
  if(!is.empty())
  {
    head = head->next_event;
    head->previous_event = NULL;
    temp->next_event = NULL;
    return temp;
  } else {
    cout << "empty queue. returning passed in head";
    return temp;
  }
  
}


double nedt( double rate )
{
  double u;
  u = drand48();
  return ((-1/rate)*log(1-u));
}
  


