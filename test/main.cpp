#include "CircularQueue.h"
#include "Message.h"
#include "os.h"
#include "test.h"
#include"RwLock.h"
#include "config.h"
#include "Subsciber.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <cmath>

class Stat {
 public:
  Stat() { clear(); }

  void clear() {
    n = 0;
    lost = 0;
  }

  void add(double value) {
    n++;
  }
  void count_check(uint32_t count)
  {
    size_t dif = count - last_count;
    if ((dif>1)&& (dif<1000) )
      lost += dif; 
    last_count = count;
  }
  size_t size() const { return n; }
  size_t loss() const { return lost;}
  friend std::ostream& operator<<(std::ostream& o, const Stat& s);

 private:
  size_t n{};
  size_t lost{};
  uint32_t last_count{};
};

std::ostream& operator<<(std::ostream& o, const Stat& s) {
  return o <<" msg per second: "<< " (" << s.size() << ")"
    << "lost msg count: "<< s.loss();}

using namespace SUB2;

#define TIMESCALE std::chrono::seconds
#define TIMESCALE_COUNT 1e6
#define TIMESCALE_NAME "us"

uint64_t current_time() {
  auto time_since_epoch = std::chrono::system_clock::now().time_since_epoch();
  auto casted_time = std::chrono::duration_cast<TIMESCALE>(time_since_epoch);
  return casted_time.count();
}
Stat per_sec_lag;

void callback(Elem *el)
{
  Message *msg = reinterpret_cast<Message*>(el->msg);
//  std::cout << msg->count << ' ';
  auto lag = current_time()- msg->TimeStep;
  per_sec_lag.add(lag);
  per_sec_lag.count_check(msg->count);
}


int main()
{
  Subscriber sub("proba", callback);
  sub.open_memory_segment();
  int seconds = 10;
  for (int sec = 0; sec < seconds; ++sec) {
    auto start = std::chrono::steady_clock::now();
    for (auto now = start; now < start + std::chrono::seconds(1);
         now = std::chrono::steady_clock::now()) {
      sub.spin_once();
    }
    std::cout << per_sec_lag << std::endl;
    per_sec_lag.clear();
  }

}
