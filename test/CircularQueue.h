
#pragma once

#include "os.h"
#include "RwLock.h"
#include "config.h"
#include "array"
#include <atomic>

namespace SUB2 {
  struct Buf
  {
    char data[LIMIT_MESSAGE_SIZE * QUEUE_SIZE];
  }; 

  struct Elem 
  {    
    char *msg;
    size_t sz;
    bool empty;

    Elem(): msg(0), sz(0), empty(true) {}
  };

  struct QueueElem 
  {
    Elem elem;
    RwLock lock;
  };

  class CircularQueue
  {
  public:
    std::atomic<uint32_t> counter;
    std::array<QueueElem, QUEUE_SIZE> queue;

  public:
    CircularQueue(Buf* _buf);
  public:  
    bool read(Elem* usermem_el,char* buf_address ,std::atomic<uint32_t> *pos);
    bool write(Elem* usermem_el);
  };
}
