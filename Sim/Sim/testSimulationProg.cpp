#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>

#include "simulation.h"
#include "queueAsArray.h" 

using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers,
                             int& transTime,
                             int& tBetweenCArrival);

void runSimulation();
 
int main()
{
    runSimulation();

    return 0;
}
//--------------------------- Main Ends -----------------------------------
/*
 * Functions Begin
 *
 */

//Sets Sim Params
void setSimulationParameters(int& sTime, int& numOfServers,
							 int& transTime,
							 int& tBetweenCArrival)
{
    cout << "Enter the simulation time: ";
    cin >> sTime;
    cout << endl;

    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << endl;

    cout << "Enter the transaction time: ";
    cin >> transTime;
    cout << endl;

    cout << "Enter the time between customer arrivals: ";
    cin >> tBetweenCArrival;
    cout << endl;
}

//Runs Simulation
void runSimulation()
{
    /*
     * sTime = Simluation Time
     * numOfServers = Total Number of Servers
     * transtime = Transaction Time
     * tBetweenCArrival = Time b/w customer arrival
     *
     */
    int sTime, numOfServers, transTime, tBetweenCArrival = 0;
 
    setSimulationParameters(sTime, numOfServers, transTime, tBetweenCArrival);
    
    srand(7654321);
    double random = 0;
    double lambda = ((double) 1) / tBetweenCArrival;
    int custNum = 0;
    double cutOff=exp(-1*lambda);
    serverListType serverList(numOfServers);
    
    //Customer Queue
    waitingCustomerQueueType customerQueue;

    customerType customer;
    
    int waitTime = 0;

    // Need new random every clock tick
    for (int clock = 1; clock <= sTime; clock++){

    	//update server list & decrements
    	serverList.updateServers(cout);
        
        //customer queue update
        customerQueue.updateWaitingQueue();

        //if customer arrives, increment numcustomers and add customer
        random = (double)rand() / RAND_MAX;
        
        if (random > cutOff) { //New Customer Arrived if 0
            
            custNum++; //incremented customer by 1
            //Create Customer
            customer.setCustomerInfo(custNum, clock, 0, transTime);
            customerQueue.addQueue(customer);

        }
        //if server is free and queue nonempty, pair customer with server
        if (serverList.getFreeServerID()!= -1 && !customerQueue.isEmptyQueue()){
            if (customerQueue.front().getCustomerNumber() != -1) {
                waitTime += customer.getWaitingTime();
                serverList.setServerBusy(serverList.getFreeServerID(), customer, transTime);
                customerQueue.deleteQueue();
            }
        }
        
    }
    customerQueue.updateWaitingQueue();
    //iterate through customer queue to find remaining wait times
    int numQueuedCustomers = customerQueue.getNumInQueue();//customerQueue.queueWaitTime(waitTime);

    int transactingCustomers = serverList.getNumberOfBusyServers();
    int finishedCustomers = custNum-transactingCustomers-numQueuedCustomers;
    waitTime=customerQueue.getWaitTime();
    
    cout    << endl
            << "========= Info ========="
            << endl
            << "Simulation Time: " << sTime
            << endl
            << "Number Of Servers: " << numOfServers
            << endl
            << "Transaction Time: " << transTime
            << endl
            << "Time Between Customer Arrivals: " << tBetweenCArrival
            << endl
            << "========= Non - Inputs ========="
            << endl
            << "Total Wait Time: "  << waitTime
            << endl
            << "Total Customers: "  << custNum
            << endl
            << "Average Wait Time: " << (float)waitTime/custNum
            << endl
            << "Customers still in queue: " << numQueuedCustomers
            << endl
            << "Customers still in transaction: " << transactingCustomers
            << endl
            << "Customers who finished receiving service: " << finishedCustomers
            << endl
            << "============ Fin ============"
            << endl;
            //display total waiting time and average waiting time
            //More servers than transaction time, no backlog in queue
}
