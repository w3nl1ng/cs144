#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  // first thing: get the available capacity of output
  uint64_t available_capacity = output.available_capacity();

  if (is_last_substring) {
    _is_last_index_set = true;
    _last_index = first_index + data.length();
    if (data == "") {
      output.close();
    }
  }

  if (first_index <= _first_unassembled_index && first_index+data.length()>_first_unassembled_index) {
    // do push
    string push_data = data.substr(_first_unassembled_index-first_index);
    auto next = _unassembled_str.lower_bound(first_index+push_data.length());
    if (next != _unassembled_str.end()) {
      if (next->first <= first_index+push_data.length()) {
        // need merge
        _bytes_pending -= next->second.substr(first_index+push_data.length()-next->first).length();
        push_data += next->second.substr(first_index+push_data.length()-next->first);
      }
    }
    output.push(push_data);
    _first_unassembled_index += push_data.substr(0, available_capacity).length();

    // if the last index contain in push_data, mean finished
    if (_is_last_index_set && _last_index <= _first_unassembled_index+push_data.length()) {
      output.close();
    }
  } else {
    // do not push
    if (first_index < _first_unassembled_index+available_capacity) {
      // do cache
      string buffered_str = data.substr(0, available_capacity); //do not cache the str out of capacity
      cache_str(first_index, buffered_str);
    } else {
      // do not cache
    }
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return _bytes_pending;
}

void Reassembler::cache_str(uint64_t first_index, string data) {
  _unassembled_str[first_index] = data;
  _bytes_pending += data.length();
}


Reassembler::Reassembler() :
  _first_unassembled_index(0),
  _is_last_index_set(false),
  _last_index(0),
  _bytes_pending(0),
  _unassembled_str()
  {}
