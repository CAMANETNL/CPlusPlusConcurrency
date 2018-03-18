#ifndef THREADGUARD_H
#define THREADGUARD_H
#include <iostream>
#include <thread>
#include <chrono>

// Using RAII to wait for a thread to complete
// Listing 2.3

class ThreadGuard
{

 public:

  // Constructor
  template <class _Fp>
  ThreadGuard(std::string _name, _Fp _function, bool _debug) : name(_name), debug(_debug)
  {
   startTime = std::chrono::high_resolution_clock::now();
   if (debug) {
    std::cout << name << ": start thread " << std::endl;
   }
   t = std::thread(_function);
  }

  // Destructor
  ~ThreadGuard()
  {
   std::cout << name << ": at the end of lifetime at " << getElapsedTime(startTime, std::chrono::high_resolution_clock::now()) << " after start" << std::endl;
   if(t.joinable()) {
    joinTime = std::chrono::high_resolution_clock::now();
    std::cout << name << ": join " << name << ".thread at " << getElapsedTime(startTime, joinTime) << " after start" << std::endl;
    t.join();
   }
  }

  // Public functions
  void detach() {
   detachTime = std::chrono::high_resolution_clock::now();
   std::cout << name << ": detach " << name << ".thread at " << getElapsedTime(startTime, detachTime) << " after start" << std::endl;
   t.detach();
  }



 private:
  std::thread t;
  const std::string name;
  const bool debug = true;
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> startTime;
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> joinTime = startTime;
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> detachTime = startTime;

  std::string getElapsedTime(std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> from, std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> untill)
  {
   auto elapsedTime = (untill - from).count();
   return std::to_string(elapsedTime / 1000000) + " milliseconds";
  }

};

#endif // THREADGUARD_H
