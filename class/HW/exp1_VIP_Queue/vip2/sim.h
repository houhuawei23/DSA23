#ifndef SIMULATION_CLASS
#define SIMULATION_CLASS

#include <iostream>
#include <iomanip>
using namespace std;
#pragma hdrstop

#include "random.h" // include random number generator

// specifies the two kinds of events
enum EventType
{
    arrival,
    departure
};

// isVip
enum isVip
{
    vip,
    notVip
};

class Event
{
private:
    // members that identify both customer and teller, as
    // well as maintain information on time of the event,
    // the event type, the length of service required by
    // the customer, and the amount of time customer is
    // forced to wait for service
    int time;
    EventType etype;
    int customerID; // customers numbered 1, 2, 3,...
    int tellerID;   // tellers numbered 1, 2, 3,...
    int waittime;
    int servicetime;
    isVip isvip;

public:
    // constructors
    Event(void);
    Event(int t, EventType et, int cn, int tn,
          int wt, int st, isVip isvip);

    // methods to retrieve private data
    int GetTime(void) const;
    int *GetTimePtr(void) { return &time; }
    EventType GetEventType(void) const;
    int GetCustomerID(void) const;
    int GetTellerID(void) const;
    int GetWaitTime(void) const;
    int GetServiceTime(void) const;
    isVip GetIsVip(void) const;
};

// default constructor - data filled by assignment later
Event::Event(void)
{
}

// constructor that initializes all data members of the event
Event::Event(int t, EventType et, int cn, int tn, int wt, int st, isVip isvip) : time(t), etype(et), customerID(cn), tellerID(tn), waittime(wt), servicetime(st), isvip(isvip)
{
}

// return the time the event occurs
int Event::GetTime(void) const
{
    return time;
}

// return the type of event (arrival, departure)
EventType Event::GetEventType(void) const
{
    return etype;
}

// return the customer number
int Event::GetCustomerID(void) const
{
    return customerID;
}

// return the teller number
int Event::GetTellerID(void) const
{
    return tellerID;
}

// return the time the customer waits for service
int Event::GetWaitTime(void) const
{
    return waittime;
}

// return the amount of teller time needed by customer
int Event::GetServiceTime(void) const
{
    return servicetime;
}

// return the isvip
isVip Event::GetIsVip(void) const
{
    return isvip;
}

// compare two Event objects using the ime at
// which the events occur. needed for the priority queue
int operator<(Event e1, Event e2)
{
    return e1.GetTime() < e2.GetTime();
}

typedef Event DataType; // elements are Event objects

#include "apqueue.h"

// Structure for Teller Info
struct TellerStats
{
    int finishService;      // when teller available
    int totalCustomerCount; // total of customers serviced
    int totalCustomerWait;  // total customer waiting time
    int totalService;       // total time servicing customers
};

class Simulation
{
private:
    // data used to run the simulation
    int simulationLength;        // simulation length
    int numTellers;              // number of tellers
    int nextCustomer;            // next customer ID
    int arrivalLow, arrivalHigh; // next arrival range
    int serviceLow, serviceHigh; // service range
    TellerStats tstat[11];       // max 10 tellers
    PQueue pq;                   // priority queue
    RandomNumber rnd;            // use for arrival
                                 // and service times
    char customers[100];         // from 1 to 100
    // private methods used by RunSimulation
    int NextArrivalTime(void);
    int GetServiceTime(void);
    int NextAvailableTeller(isVip isvip);
    int CutIn(int tellerID, int cuttime, int servicetime, int &cnt);

public:
    // constructor
    Simulation(void);

    void RunSimulation(void);          // execute study
    void PrintSimulationResults(void); // print stats
};
// 返回插入后要等待的时间
int Simulation::CutIn(int tellerID, int cuttime, int servicetime, int &cnt)
{
    printf("CUT IN\n");
    int len = pq.PQLength();
    int min_detime = INT_MAX;
    int hasvip = 0;
    // 如果有vip在排队，就插入在vip后面
    for (int i = 0; i < len; i++)
    {
        Event *e = pq.PQGetItem(i);
        if (e->GetTellerID() == tellerID &&
            e->GetEventType() == departure &&
            e->GetTime() > cuttime &&
            e->GetIsVip() == vip)
        {
            hasvip = 1;
            break;
        }
    }
    // 没有vip在排队，就插入在departure time最小的后面
    if (hasvip == 0) // 没有vip
    {
        // printf("no vip\n");
        for (int i = 0; i < len; i++)
        {
            Event *e = pq.PQGetItem(i);

            // 找到departure time最小的，且比cuttime大的，要插入在其后
            if (e->GetTellerID() == tellerID &&
                e->GetEventType() == departure &&
                e->GetTime() > cuttime &&
                e->GetTime() < min_detime) // <
            {
                min_detime = e->GetTime();
            }
        }
    }
    else
    { // 有vip在排队，就插入在最大departure time 的 vip后面
        // printf("has vip\n");
        min_detime = 0;
        for (int i = 0; i < len; i++)
        {
            Event *e = pq.PQGetItem(i);
            if (e->GetTellerID() == tellerID &&
                e->GetEventType() == departure &&
                e->GetTime() > cuttime &&
                e->GetIsVip() == vip &&
                e->GetTime() > min_detime) // >
            {
                min_detime = e->GetTime();
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        Event *e = pq.PQGetItem(i);
        // 找到所有比min_detime大的，departure time都加上servicetime
        if (e->GetTellerID() == tellerID &&
            e->GetEventType() == departure &&
            e->GetIsVip() == notVip &&
            e->GetTime() > min_detime)
        {
            // printf("before: e->GetTime(): %d\n", e->GetTime());

            *(e->GetTimePtr()) += servicetime;
            // printf("then: e->GetTime(): %d\n", e->GetTime());
            cnt++;
        }
        // printf("cnt: %d\n", cnt);
    }
    if (min_detime == INT_MAX)
    {
        min_detime = cuttime;
    }
    return min_detime;
}

isVip CustomerType(char type)
{
    if (type == '1')
    {
        return vip;
    }
    else
    {
        return notVip;
    }
}
// constructor initializes simulation data and prompts client
// for simulation parameters
Simulation::Simulation(void)
{
    int i;
    Event firstevent;

    // Initialize Teller Information Parameters
    for (i = 1; i <= 10; i++)
    {
        tstat[i].finishService = 0;
        tstat[i].totalService = 0;
        tstat[i].totalCustomerWait = 0;
        tstat[i].totalCustomerCount = 0;
    }
    nextCustomer = 1;

    // reads client input for the study
    cout << "Enter the simulation time in minutes: ";
    cin >> simulationLength;
    cout << "Enter the number of bank tellers: ";
    cin >> numTellers;
    cout << "Enter the range of arrival times in minutes: ";
    cin >> arrivalLow >> arrivalHigh;
    cout << "Enter the range of service times in minutes: ";
    cin >> serviceLow >> serviceHigh;
    cout << "Enter the str of customers: ";
    cin >> customers;
    // generate first arrival event
    // teller#/waittime/servicetime not used for arrival
    pq.PQInsert(Event(0, arrival, 1, 0, 0, 0, CustomerType(customers[1])));
}

// determine random time of next arrival
int Simulation::NextArrivalTime(void)
{
    return arrivalLow + rnd.Random(arrivalHigh - arrivalLow + 1);
}

// determine random time for customer service
int Simulation::GetServiceTime(void)
{
    return serviceLow + rnd.Random(serviceHigh - serviceLow + 1);
}

// return first available teller
int Simulation::NextAvailableTeller(isVip isvip)
{
    // initially assume all tellers finish at closing time
    int minfinish = simulationLength;

    // assign random teller to customer who arrives
    // before closing but obtains service after closing
    int minfinishindex = rnd.Random(numTellers) + 1;
    int start = 1;

    if (isvip == notVip)
    {
        start = 2;
    }

    // find teller who is free first
    for (int i = start; i <= numTellers; i++)
    {
        printf("tstat[%d].finishService: %d\n", i, tstat[i].finishService);
        // 1 is vip teller
        if (tstat[i].finishService < minfinish)
        {
            minfinish = tstat[i].finishService;
            minfinishindex = i;
        }
    }
    return minfinishindex;
}

// implements the simulation
void Simulation::RunSimulation(void)
{
    Event e, newevent;
    int nexttime;
    int tellerID;
    int servicetime;
    int waittime;

    // run till priority queue is empty
    while (!pq.PQEmpty())
    {
        // get next event (time measures the priority)
        e = pq.PQDelete();

        // handle an arrival event
        if (e.GetEventType() == arrival)
        {
            // compute time for next arrival.
            nexttime = e.GetTime() + NextArrivalTime();
            cout << "customer id: " << e.GetCustomerID() << "   nexttime: " << nexttime << endl;
            if (nexttime <= simulationLength)
            {
                // generate arrival for next customer. put in queue
                nextCustomer++;
                newevent = Event(nexttime, arrival, nextCustomer, 0, 0, 0, CustomerType(customers[nextCustomer]));
                // cout<<"customer id: "<<newevent.GetCustomerID()<<endl;
                pq.PQInsert(newevent);
            }
            cout << endl;
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  "
                 << "arrival of customer "
                 << e.GetCustomerID();
            if (e.GetIsVip() == vip)
            {
                cout << "       VIP" << endl;
            }
            else
            {
                cout << "       not VIP" << endl;
            }
            // generate departure event for current customer

            // time the customer takes
            servicetime = GetServiceTime();
            // teller who services customer
            tellerID = NextAvailableTeller(e.GetIsVip());
            // if teller free, update sign to current time
            if (tstat[tellerID].finishService == 0)
                tstat[tellerID].finishService = e.GetTime();

            // compute time customer waits by subtracting the
            // current time from time on the teller's sign
            int cnt = 0;
            int min_detime = 0;
            if (e.GetIsVip() == vip)
            {
                min_detime = CutIn(tellerID, e.GetTime(), servicetime, cnt);
                tstat[tellerID].totalCustomerWait += (min_detime - e.GetTime()) * cnt;
            }
            else
            {
                waittime = tstat[tellerID].finishService - e.GetTime();
                tstat[tellerID].totalCustomerWait += waittime;
            }
            // update teller statistics

            tstat[tellerID].totalCustomerCount++;
            tstat[tellerID].totalService += servicetime;
            tstat[tellerID].finishService += servicetime;

            if (e.GetIsVip() == vip)
            {
                newevent = Event(min_detime + servicetime,
                                 departure, e.GetCustomerID(), tellerID,
                                 waittime, servicetime, e.GetIsVip());
                printf("min + service: %d\n", min_detime + servicetime);
                printf("min: %d\n", min_detime);
                printf("service: %d\n", servicetime);
            }
            else
            {
                // create a departure object and put in the queue
                newevent = Event(tstat[tellerID].finishService,
                                 departure, e.GetCustomerID(), tellerID,
                                 waittime, servicetime, e.GetIsVip());
            }

            pq.PQInsert(newevent);
        }
        // handle a departure event
        else
        {
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  "
                 << "departure of customer "
                 << e.GetCustomerID() << endl;
            cout << "       Teller " << e.GetTellerID()
                 << "  Wait " << e.GetWaitTime()
                 << "  Service " << e.GetServiceTime();

            if (e.GetIsVip() == vip)
            {
                cout << "       VIP" << endl;
            }
            else
            {
                cout << "       not VIP" << endl;
            }

            tellerID = e.GetTellerID();
            // if nobody waiting for teller, mark teller free
            if (e.GetTime() == tstat[tellerID].finishService)
                tstat[tellerID].finishService = 0;
        }
    }

    // adjust simulation to account for overtime by tellers
    simulationLength = (e.GetTime() <= simulationLength)
                           ? simulationLength
                           : e.GetTime();
}

// summarize the simulation results
void Simulation::PrintSimulationResults(void)
{
    int cumCustomers = 0, cumWait = 0, i;
    int avgCustWait, tellerWorkPercent;
    float tellerWork;

    for (i = 1; i <= numTellers; i++)
    {
        cumCustomers += tstat[i].totalCustomerCount;
        cumWait += tstat[i].totalCustomerWait;
    }

    cout << endl;
    cout << "******** Simulation Summary ********" << endl;
    cout << "Simulation of " << simulationLength
         << " minutes" << endl;
    cout << "   No. of Customers:  " << cumCustomers << endl;
    cout << "   Average Customer Wait: ";

    avgCustWait = int(float(cumWait) / cumCustomers + 0.5);
    cout << avgCustWait << " minutes" << endl;
    for (i = 1; i <= numTellers; i++)
    {
        cout << "    Teller #" << i << "  % Working: ";
        // display percent rounded to nearest integer value
        tellerWork = float(tstat[i].totalService) / simulationLength;
        tellerWorkPercent = int(tellerWork * 100.0 + 0.5);
        cout << tellerWorkPercent << endl;
    }
}

#endif // SIMULATION_CLASS