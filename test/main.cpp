#include "os.h"
#include "test.h"
#include"RwLock.h"
#include "config.h"
#include <cstdint>

#include <iostream>
#define STORAGE_ID "/SHM_TEST"
int main()
{
    SUB2::RwLock r ;
    SUB2::test t ;
    
    int res;
  int shm;
  SUB2::test* test_;
  auto test_size = sizeof(SUB2::test);
  auto lock_size = sizeof(SUB2::RwLock);

  pid_t pid;
  pid = getpid();
     shm  = shm_open(STORAGE_ID, O_CREAT | O_RDWR, SHM_MODE);
  if (shm == -1)
    perror("shm_open");
  auto *ptr = mmap(nullptr, sizeof(SUB2::test) , PROT_READ | PROT_WRITE,
                   MAP_SHARED, shm, 0);	


  auto *base_address= reinterpret_cast<uintptr_t*>(ptr);
  auto *test_address = base_address;
  auto *int_address = base_address + lock_size;

    
test_ = reinterpret_cast<SUB2::test*>(test_address);

  
  uint8_t recieved = 0;
  
   double time_counter = 0;

  clock_t this_time = clock();
  clock_t last_time = this_time;

   while(true)
    { 
        this_time = clock();

        time_counter += (double)(this_time - last_time);

        last_time = this_time;

        if(time_counter > (double)(3 * CLOCKS_PER_SEC))
        {
            time_counter -= (double)(3 * CLOCKS_PER_SEC);
            test_->read(int_address, &recieved, sizeof(recieved));
            std::cout << "PID: " << pid<< " get: " << +recieved <<std::endl;
        }
    }


}
