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
    
    // Need new random every clock tick
    for (int clock = 1; clock <= sTime; clock++){
        random = rand() % tBetweenCArrival;
        if (!random) {
            //add customer
            custNum++;
            customerType customer;
            customer.setCustomerInfo(custNum, clock, 0, transTime);
            
        }
        
    }
    

}