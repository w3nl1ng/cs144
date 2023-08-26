#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  // first thing: get the available capacity of output
  // uint64_t available_capacity = output.available_capacity();

  if (is_last_substring) {
    _is_last_index_set = true;
    _last_index = first_index + data.length();
  }

  if (first_index <= _first_unassembled_index && data.length() > 0) {
    // do push
    string push_data = data.substr(_first_unassembled_index-first_index);
    output.push(push_data);
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return _bytes_pending;
}

Reassembler::Reassembler() :
  _first_unassembled_index(0),
  _is_last_index_set(false),
  _last_index(0),
  _bytes_pending(0)
  {}
