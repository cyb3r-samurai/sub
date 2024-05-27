#include "os.h"
#include "Message.h"
#include <cstring>
using namespace SUB2;

Message::Message() 
{
 size_t vector_size = 11;
  
  char *rawptr = (char*)malloc(vector_size);

  const char example[11] = "HelloWorld"; 
  std::strcpy(rawptr, example);
  data = rawptr;
}
