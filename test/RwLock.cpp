#include "os.h"
#include "RwLock.h"


namespace SUB2 {

RwLock::RwLock() {
int res = pthread_rwlockattr_init(&attr);
 if (res != 0)
  std::cerr << "pthread_rwlockattr_init failed" << std::endl;
 res = pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
  if (res != 0)
    std::cerr << "pthread_rwlockattr_setpshared failed" << std::endl;
res = pthread_rwlock_init(&rwlock, &attr);
  if (res != 0)
    std::cerr << "pthread_rwlock_init failed " <<std:: endl;
}
RwLock::~RwLock() {
  pthread_rwlockattr_destroy(&attr);
  pthread_rwlock_destroy(&rwlock);
}

void RwLock::lock() { pthread_rwlock_wrlock(&rwlock); }
bool RwLock::try_lock() {
  return (!pthread_rwlock_trywrlock(&rwlock));
}
void RwLock::unlock() { pthread_rwlock_unlock(&rwlock); }
void RwLock::lock_sharable() { pthread_rwlock_rdlock(&rwlock); }
bool RwLock::try_lock_sharable() {
  return (!pthread_rwlock_tryrdlock(&rwlock));
}
void RwLock::unlock_sharable() {
  pthread_rwlock_unlock(&rwlock);
}

void RwLock::reset() {
  pthread_rwlock_destroy(&rwlock);
  pthread_rwlock_init(&rwlock, &attr);
}
}
