
#include "os.h"
#include "RwLock.h"
#include <cstring>
#include "test.h"

namespace SUB2 {

    void test::read(void* shmem, void* usrmem, size_t size) 
    {
       lock.lock_sharable(); 
       std::memcpy(usrmem, shmem, size);
       lock.unlock_sharable();
       
    }

    void test::write(void* shmem, void* usrmem, size_t size) 
    {
       lock.lock(); 
       std::memcpy(shmem, usrmem, size);
       lock.unlock();
    }


}
