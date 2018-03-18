#include <iostream>
#include "threadguard.h"
#include "test_function.h"

using namespace std;

int main()
{

 auto startTime = chrono::high_resolution_clock::now();
 cout << "main-thread started. " << endl;
 ThreadGuard tg1("tg1", TestFunction::sleep1Seconds, true);
 ThreadGuard tg2("tg2", TestFunction::sleep2Seconds, true);
 tg2.detach();
 cout << "main thread: " << TestFunction::sleepXMilliSeconds(4000) << endl;
 tg1.detach();
 ThreadGuard tg3("tg3", TestFunction::sleep1Seconds, true);

 // function with parameter(s) ////////////////////////////////////////////////
 long long durationInSec =  1;
 TestFunction::functionWithParameters functionWithPars(durationInSec);
 ThreadGuard tg4("tg4", functionWithPars, true);
 tg4.detach();
 cout << "main thread: " << TestFunction::sleepXMilliSeconds(2000) << endl;
 cout << "main-thread ending " << to_string((chrono::high_resolution_clock::now() - startTime).count()/1000000) << endl;
 return 0;
}

