#include "os.h"
#include "config.h"
#include "CircularQueue.h"
#include <atomic>
#include <cstring>

namespace SUB2 {
  CircularQueue::CircularQueue(Buf* _buf)
  {
   for(int i = 0; i < QUEUE_SIZE; i++)
   {
     queue[i].elem.msg = _buf->data + ((LIMIT_MESSAGE_SIZE)*i);
   }
  }

  bool CircularQueue::write(Elem* usermem_el)
  {
    uint32_t q_pos = counter.load() & (QUEUE_SIZE - 1);
    QueueElem *q_elem = &(queue[q_pos]);
    
    q_elem->lock.lock();
    q_elem->elem.sz = usermem_el->sz;
    std::memcpy(q_elem->elem.msg, usermem_el->msg, q_elem->elem.sz);
    q_elem->elem.empty = false;
    counter++;
    q_elem->lock.unlock(); 

    return true;
  }

  bool CircularQueue:: read(Elem* usermem_el,char * buf_address, std::atomic<uint32_t> *pos)
  {
    int q_pos = *pos & (QUEUE_SIZE - 1);
    QueueElem *q_elem = &(queue[q_pos]);

    q_elem->lock.lock_sharable();
    usermem_el->sz =q_elem->elem.sz;
    std::memcpy(usermem_el->msg, (buf_address +(LIMIT_MESSAGE_SIZE * q_pos)), usermem_el->sz);
    usermem_el->empty = false;
    q_elem->lock.unlock_sharable();
    return true;
  }
}
