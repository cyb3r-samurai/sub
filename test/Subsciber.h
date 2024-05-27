# pragma once

#include "Message.h"
#include "config.h"
#include "CircularQueue.h"
#include <functional>
namespace SUB2 {

  class Subscriber
  {
    public:
      Subscriber(const std::string &bus_name, std::function<void(Elem *)>callback);
    public: 
      void open_memory_segment();
      bool get_message();
      void spin_once();
      void spin();
      Elem receiving_elem;
      std::atomic<uint32_t> count;
      Buf *buf_;
      CircularQueue *queue; 
      char * buf_address;
    private:
      std::function<void(Elem *)> callback_;
      std::string bus_name_;
      
  };

}
