#include <functional>
#include <unistd.h>
#include "CircularQueue.h"
#include "Subsciber.h"
#include "config.h"


namespace SUB2 {
  Subscriber::Subscriber(const std::string &bus_name, 
                         std::function<void(Elem *)> callback)
    :bus_name_(bus_name), callback_(std::move(callback)) {};
  
  void Subscriber::open_memory_segment()
  {
    int shm;
    const std::string storage = "/SHM"+ bus_name_;
    shm = shm_open(storage.c_str(), O_CREAT | O_RDWR, SHM_MODE);
    if (shm == -1)
      perror("shm_open");
    auto *ptr = mmap(nullptr,sizeof(Buf)+12800 , PROT_READ | PROT_WRITE,
                   MAP_SHARED, shm, 0);
 

  //init memory   
  auto *base_address= reinterpret_cast<char*>(ptr);
  buf_address = base_address;
  auto *queue_address = base_address + sizeof(Buf);

  buf_  = reinterpret_cast<Buf *>(buf_address);
  queue = reinterpret_cast<CircularQueue *>(queue_address);
 
  

  receiving_elem.msg = (char*)malloc(LIMIT_MESSAGE_SIZE);
  }

  bool Subscriber::get_message()
  {
    if(queue->counter.load() <= count)
    {
      return false;
    }
    
    if (queue->counter.load() - count >= QUEUE_SIZE) {
      count = queue->counter.load() - QUEUE_SIZE/2;
    }


    queue->read(&receiving_elem, buf_address, &count);
    return true;
  }

  void Subscriber::spin_once()
  {
    if (get_message())
    {
      callback_(&receiving_elem);
      count++;
    }
  }











  
}
