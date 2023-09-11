#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  // Your code here.
  // (void)n;
  // (void)zero_point;
  // return Wrap32 { 0 };
  return Wrap32((zero_point+(n%(1LL<<32))));
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  // (void)zero_point;
  // (void)checkpoint;
  // return {};
  const uint64_t UINT32_RANGE = 1LL << 32;
  uint64_t offset = raw_value_ - zero_point.raw_value_;
  if (offset >= checkpoint) {
    return offset;
  } else {
    uint64_t round = (checkpoint - offset) / UINT32_RANGE;
    uint64_t reminder = (checkpoint - offset) % UINT32_RANGE;
    if (reminder < UINT32_RANGE/2) {
      return offset + round * UINT32_RANGE;
    } else {
      return offset + (round + 1) * UINT32_RANGE;
    }
  }
}
