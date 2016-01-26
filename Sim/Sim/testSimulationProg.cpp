#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

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
    
    srand(time(NULL));
    int random = 0;
    int custNum = 0;

    serverListType serverList(numOfServers);
    
    //Customer Queue
    waitingCustomerQueueType customerQueue;

    customerType customer;

    // Need new random every clock tick
    for (int clock = 1; clock <= sTime; clock++){

    	//update server list & decrements
    	serverList.updateServers(cout);
        
        //customer queue update
        customerQueue.updateWaitingQueue();

        //if customer arrives, increment numcustomers and add customer
        random = rand() % tBetweenCArrival;
        if (!random) { //New Customer Arrived if 0
            
            custNum++; //incremented customer by 1
            //Create Customer
            customer.setCustomerInfo(custNum, clock, 0, transTime);
            customerQueue.addQueue(customer);

        }
        //if server is free and queue nonempty, pair customer with server
        if (serverList.getFreeServerID() != -1 ) {
            if (customerQueue.front().getCustomerNumber() != -1) {
                serverList.setServerBusy(serverList.getFreeServerID(), customer, transTime);
            }
        }
    }

    cout << endl << "Simulation Completed.\n"
    	 << "Simulation time: " << sTime << endl
	 << "Number of servers: " << numOfServers << endl
	 << "transaction time: " << transTime << endl
	 << "tBetweenCArrival" << tBetweenCArrival << endl;
    //display total waiting time and average waiting time

}

