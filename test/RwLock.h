#pragma once
#include "os.h"

namespace SUB2{
class RwLock {
 public:
  RwLock();
  ~RwLock();

  void lock();
  bool try_lock();
  void unlock();
  void lock_sharable();
  bool try_lock_sharable();
  void unlock_sharable();
  void reset();

 private:
  pthread_rwlock_t rwlock{};
  pthread_rwlockattr_t attr{};
};

}
