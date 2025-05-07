#include "reassembler.hh"
#include "debug.hh"
#include<iostream>
using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // debug( "unimplemented insert({}, {}, {}) called", first_index, data, is_last_substring );
  std::cout<<"first_index "<<first_index<<std::endl;
  if ( this->writer().is_closed() || this->writer().available_capacity() == 0 )
    return;
  if ( first_index + data.size() < currentIndex || first_index >= firstUnAcceptable )
    return;
  u_int64_t begin_index = first_index, end_index = first_index + data.size();
  if(is_last_substring){
    end=true;
    endIndex=end_index;
  }
  if ( first_index < currentIndex )
    begin_index = currentIndex;
  if ( end_index > firstUnAcceptable )
    end_index = firstUnAcceptable;
  for ( u_int64_t i = begin_index; i < end_index; i++ ) {
    if ( !judgeBuffer[i - currentIndex] ) {
      buffer[i - currentIndex] = data[i-first_index];
      judgeBuffer[i - currentIndex] = true;
      if(buffer.size()>1) std::cout<<"Byte1 "<<buffer[1]<<std::endl;
      unAssembleBytes++;
    }
  }
  string toWrite = "";
  while ( judgeBuffer.front() == true ) {
    currentIndex++;
    toWrite += buffer.front();
    judgeBuffer.pop_front();
    judgeBuffer.push_back( false );
    std::cout<<"Byte0 "<<buffer.front()<<std::endl;
    if(buffer.size()>1) std::cout<<"Byte1 "<<buffer[1]<<std::endl;
    buffer.pop_front();
    buffer.push_back( '\0' );
    firstUnAcceptable++;
  }
  std::cout<<"string "<<toWrite<<std::endl;
  if ( toWrite.size() > 0 ) {
    output_.writer().push( toWrite );
    unAssembleBytes -= toWrite.size();
  }
  // if ( is_last_substring ) {
  //   end = true;
  //   endIndex = end_index;
  // }
  if ( end and endIndex == this->writer().bytes_pushed() ) {
    output_.writer().close();
  }
}

// How many bytes are stored in the Reassembler itself?
// This function is for testing only; don't add extra state to support it.
uint64_t Reassembler::count_bytes_pending() const
{
  // debug( "unimplemented count_bytes_pending() called" );
  return unAssembleBytes;
}
