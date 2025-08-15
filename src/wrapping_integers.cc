#include "wrapping_integers.hh"
#include "debug.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  // Your code here.
  //debug( "unimplemented wrap( {}, {} ) called", n, zero_point.raw_value_ );
  return zero_point+(uint32_t)n;
}
//相对转绝对
uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  // debug( "unimplemented unwrap( {}, {} ) called", zero_point.raw_value_, checkpoint );
  // return {};
  // uint64_t times=(checkpoint+(1ULL<<32)/2)/(1ULL<<32);
  // return times*(1ULL<<32)+this.raw_value_ -zero_point.raw_value_;
  // uint64_t time =checkpoint/(1ULL<<32);
  // int64_t guess=time*(1ULL<<32)+this.raw_value_-zero_point.raw_value_;
  // int64_t leftguess=guess-(1ULL<<32);
  // int64_t rightguess=guess+(1ULL<<32);
  // int64_t temp=0;
  // temp=min(abs(leftguess-checkpoint),min(abs(rightguess-checkpoint),abs(guess-checkpoint)));
  // if(temp==abs(leftguess-checkpoint)) return leftguess;
  // else if(temp==abs(rightguess-checkpoint)) return rightguess;
  // else return guess; 
  uint64_t time = checkpoint / (1ULL << 32);
uint64_t guess = time * (1ULL << 32) + ((uint32_t)(this->raw_value_ - zero_point.raw_value_));
uint64_t leftguess = guess - (1ULL << 32);
uint64_t rightguess = guess + (1ULL << 32);

// A helper lambda or function to calculate unsigned distance
auto dist = [&](uint64_t a, uint64_t b) {
    return a > b ? a - b : b - a;
};

uint64_t min_dist = dist(guess, checkpoint);
uint64_t closest_guess = guess;

if (dist(leftguess, checkpoint) < min_dist) {
    min_dist = dist(leftguess, checkpoint);
    closest_guess = leftguess;
}
if (dist(rightguess, checkpoint) < min_dist) {
    closest_guess = rightguess;
}
return closest_guess;
  // uint32_t curr = raw_value_ - zero_point.raw_value_;
  // uint64_t a = ( checkpoint - curr ) / ( (uint64_t)1 << 32 );
  // uint64_t first = (uint64_t)curr + ( (uint64_t)1 << 32 ) * a;
  // uint64_t second = (uint64_t)curr + ( (uint64_t)1 << 32 ) * ( a + 1 );
  // uint64_t diff1 = ( ( checkpoint > first ) ? checkpoint - first : first - checkpoint );
  // uint64_t diff2 = ( ( checkpoint > second ) ? checkpoint - second : second - checkpoint );
  // return ( ( diff1 < diff2 ) ? first : second );
}
