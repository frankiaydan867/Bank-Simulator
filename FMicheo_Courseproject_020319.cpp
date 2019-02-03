/* 
 * File:   Bank Simulator.cpp
 * Author: Franki Micheo
 * Course: COP2570C Programming Data Structures
 * Created on January 26, 2019, 9:01 AM
 * 
 */
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <unistd.h>
#include <chrono>
#include <time.h>
#include <sys/wait.h>
#include <iomanip>
#include <random>

using namespace std;


//Classes


class Client{
private:
    string reasonForVisit;
    string lenghtOfService;
    string arrivalTime;
    string waitingTime;
    string Teller;
    bool wasServed;
    string serveTime;
public:
    
    //Setters
    void setReasonForVisit(string n){
        reasonForVisit = n;
    }
    
    void setLenghtOfService(string n){
        lenghtOfService = n;
    }
    
    void setArrivalTime(string n){
        arrivalTime = n;
    }
    
    void setWaitingTime(string n){
        waitingTime = n;
    }
    
    void setTeller(string n){
        Teller = n;
    }
    
    void setWasServed(bool b){
        wasServed = b;
    }
    
    void setServeTime(string n){
        serveTime = n;
    }
    
    //Getters
    string getReasonForVisit(){
        return reasonForVisit;
    }
    
    string getLenghtOfService(){
        return lenghtOfService;
    }
    
    string getArrivalTime(){
        return arrivalTime;
    }
    
    string getWaitingTime(){
        return waitingTime;
    }
    
    string getTeller(){
        return Teller;
    }
    
    bool getWasServer(){
        return wasServed;
    }
    
    string getServerTime(){
        return serveTime;
    }
};

void ClearScreen();

void Header();

void UpdateClientDeques(deque<Client> (&c), bool t, int hour, int min);

void TimedSimulation(deque<Client> &c, bool t);

void Report(deque<Client> c);

void TotalCustomers(deque<Client> c);

void ArrivalTimeAndLOS(deque<Client> c);

void AverageWaitTime(deque<Client> c);

int main(int argc, char** argv) {

    //Variables
    bool TestingMode = false;  //Testing Mode 
    bool tm = TestingMode; //Var to pass as argument
    int selection;
    
    //Clients
    deque<Client> client;
    int TotalClients = 15; 
    //InitializeClients(client, tm, TotalClients);
 
    MAINMENU:
    //Reset the screen
    ClearScreen();
    
    //Display Menu
    cout << "Main Menu:\n\n";
    cout << "1-Run Simulation\n2-Report\n3-Exit\n\nSelection:";
    cin >> selection;
    
    //Menu Functions
    switch(selection){
        case 1:
            client.clear(); //Clear the deque to run new simulation
            TimedSimulation(client, tm);
            goto MAINMENU;
        case 2:
            REPORTS:
            ClearScreen();
            selection = NULL;
            cout << "\n\n1-Total Customers\n2-Arrival Time and Length of Service\n"
                    "3-Average Customer Wait Time\n4-Go Back\n\nSelection:";
            cin >> selection;
            
            switch(selection){
                case 1: //Total Customers
                    ClearScreen();
                    TotalCustomers(client);
                    goto REPORTS;
                case 2:  //Arrival Time and LOS
                    ClearScreen();
                    ArrivalTimeAndLOS(client);
                    goto REPORTS;
                case 3:  //Average customer WT
                    ClearScreen();
                    AverageWaitTime(client);
                    goto REPORTS;
                case 4: //Go back to main menu
                    goto MAINMENU;
                default:
                    cout << "Invalid Selection... Please Try Again.";
                    sleep(1);
                    goto REPORTS;
            }
            //Report(client); //Full report
            goto MAINMENU;
        case 3:
            cout << "\nBye!";
            goto EXIT;
        default:
            goto MAINMENU;
        
    }
    
    //END OF PROGRAM
    EXIT:
    return 0;
}

//Function to clear the screen
void ClearScreen(){
    system("clear");
    Header();
}

void Header(){
    //ClearScreen();
    for(int i = 0; i < 41; i++){
        cout << "*";
    }
    cout << "\n*\tBank Reception Simulator\t*\n";
    for(int i = 0; i < 41; i++){
        cout << "*";
    }
    cout << endl << endl;
}

void UpdateClientDeques(deque<Client> (&c), bool t, int hour, int min){
    //Variables
    Client cl;
    int lenghtofservice;
    int waittime;
    int teller;
    string reason;
    
    
    
        
    srand(time(0));
    int clientload = rand() % 12;
    
    
    
    
    
    //Initialize clients
    for(int i=0;i < clientload;i++){
        
        //reason = "";
        if(t){
            cout << "Initializing client: " << i << endl;
        }
        //Assign Random values
        lenghtofservice = 1 + rand() % 4;
        waittime = 1 + rand() % 5;
        if(lenghtofservice == 1){
            reason = "Open Account";}
        else if(lenghtofservice == 2 ){
            reason = "Close Account";}
        else if(lenghtofservice == 3){
            reason = "Deposit Money";}
        else if(lenghtofservice == 4){
            reason = "Withdrawal";
        }
        
        //Assign random arrival time
        string time = to_string(hour)+":"+to_string(min + rand() % 15);
        
        //Assign values to client       
        cl.setArrivalTime(time);
        cl.setLenghtOfService(to_string(lenghtofservice));
        cl.setReasonForVisit(reason);
        cl.setServeTime(to_string(lenghtofservice+waittime));
        
        //Assign tellers according to client load
        if(i<4){
            cl.setTeller("Teller A");
        }
        
        else if(i > 3 && i < 9){
            cl.setTeller("Teller B");
        }
        else if(i > 8){
            cl.setTeller("Teller C");
        }
            
        cl.setWaitingTime(to_string(waittime));
        cl.setWasServed(true);
        if(t){
            cout << "Client Initialized\n";
        }
        
        //Add to deque
        c.push_front(cl);
        if(t){
            cout << "Added client " << i+1 << " of " << clientload << " to deque\n";
        }
        cout << "Added client " << i+1 << " of " << clientload << " to deque\n";
        
    }
    
    
}

void TimedSimulation(deque<Client> &c, bool t){
    ClearScreen();
       
    string ampm = "am";
    int h;
    int m;
    int l;
    
    for(int i = 0; i < 3; i++){
        h = ((9 + i) % 12) + 1 ;
        for(int o = 0;o < 4;o++){
            ClearScreen();
            m = (o * 15) % 60;
            if(i >= 2){
                ampm = "pm";
            }
            //Display Time every 15 minutes
            cout << h << ":" << m << ampm << endl;
            
            //Update Deque every 15 minutes
            UpdateClientDeques(c, t, h, m);
            
            //Wait a second for the next 15 minute block
            sleep(1);
        }
    }
   
}

void Report(deque<Client> c){
    ClearScreen();
    string s;
    Client client;
    int index = 1;
    
    //Table Header
    cout << "\nReport\n\n";    
    cout << left << setw(6) << "#"
            << left << setw(20) << "Reason for Visit"
            << left << setw(20) << "Arrival Time"
            << left << setw(15) << "Waiting Time"
            << left << setw(10) << "Teller"
            << left << setw(20) << "Length of Service"
            << left << setw(12) << "Served Time\n";
    
    for(int i = 0; i < 100;i++){
       cout << "-";
    } 
   cout << endl;
   
   
   
   //Print all data for each client
   while(!c.empty()){
       client = c.front();
       cout << left << setw(6) << index
            << left << setw(20) << client.getReasonForVisit()
            << left << setw(20) << client.getArrivalTime()
            << left << setw(15) << client.getWaitingTime()
            << left << setw(10) << client.getTeller()
            << left << setw(20) << client.getLenghtOfService() 
            << left << setw(12) << client.getServerTime() << endl;
       index++;
       c.pop_front();
   }
   
   cout << "Exit? (Y): ";
   cin >> s;
   
}

void TotalCustomers(deque<Client> c){
    
    Client client;
    int TotalCustomers = c.size();
    int CustomersByHour[3] = {0,0,0};
    int count = 0;
    string time;
    string s;
    
    
    while(!c.empty()){
        client = c.front();
        time = client.getArrivalTime();
        time = time.substr(0,2);
        if(time == "10"){
            CustomersByHour[0]++;
        }
        else if(time == "11"){
            CustomersByHour[1]++;
        }
        else if(time == "12"){
            CustomersByHour[2]++;
        }
        
        c.pop_front();
    }
    
    cout << "Stats:\n----------------------------\n";
    cout << "Total Customers Served: " << TotalCustomers;
    cout << "\nCustomers Served from 10am to 11am: " << CustomersByHour[0];
    cout << "\nCustomers Served from 11am to 12pm: " << CustomersByHour[1];
    cout << "\nCustomers Served from 12pm to 1pm: " << CustomersByHour[2];
    
    cout << "\n\nPress any key to exit:";
    cin >> s;
}

void ArrivalTimeAndLOS(deque<Client> c){
    Client client;
    int index = 1;
    string s;

    cout << "\nClients Arrival Time and Length of Service\n\n";

    
    //Table Header
    cout << left << setw(5) << "#"
            << left << setw(15) << "Arrival Time"
            << left << setw(1) << "Length of Service\n";

    
    for(int i = 0; i < 45;i++){
       cout << "-";
    } 
   cout << endl;
   
      
   //Print all data for each client
   while(!c.empty()){
       client = c.back();

       cout << left << setw(5) << index  
            << left << setw(15) << client.getArrivalTime()
            << left << setw(1) << client.getLenghtOfService() << " minute(s)" << endl;
       index++;
       
       c.pop_back();
   }
   
   cout << "\n\nPress any key to continue";
   cin >> s;
}

void AverageWaitTime(deque<Client> c){
    Client client;
    double total[4];
    double AverageTime[4] = {0,0,0,0};
    int AverageByHour[3] = {0,0,0};
    int count = 0;
    string time;
    string arrival;
    string s;
    
    total[0] = c.size(); //Hold the total for the whole time;
    
    while(!c.empty()){
        client = c.front();
        time = client.getWaitingTime();
        arrival = client.getArrivalTime();
        arrival = arrival.substr(0,2);
        AverageTime[0] += stod(time);
        if(arrival == "10"){
            total[1]++;
            AverageTime[1] += stod(time);

        }
        else if(arrival == "11"){
            total[2]++;
            AverageTime[2] += stod(time);
        }
        else if(arrival == "12"){
            total[3]++;
            AverageTime[3] += stod(time);
        }
        
        c.pop_front();
    }
    
    cout << "Stats:\n----------------------------\n";
    cout << "Average Wait Time: " << AverageTime[0] / total[0];
    cout << "\nAverage Wait Time 10am to 11am: " << AverageTime[1]/total[1];
    cout << "\nCAverage Wait Time from 11am to 12pm: " << AverageTime[2]/total[2];
    cout << "\nAverage Wait Time from 12pm to 1pm: " << AverageTime[3]/total[3];
    
    cout << "\n\nPress any key to exit:";
    cin >> s;
}