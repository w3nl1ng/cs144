#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  // (void)first_index;
  // (void)data;
  // (void)is_last_substring;
  // (void)output;

  if (!has_inited) {
    has_inited = true;
    _capacity = output.available_capacity();
    _last_expected = _first_expected + _capacity;
    for (uint64_t i = _first_expected; i < _last_expected; i++) {
      _buf.push_back(0);
    }
  }


  uint64_t data_len = data.length();
  uint64_t last_index = first_index + data_len;
  uint64_t old_first_index = first_index;

  if (data_len == 0) {
    if (is_last_substring) {
      output.close();
    }
    return;
  }

  if (is_last_substring) {
    last_byte = last_index;
  }

  if (last_index <= _first_expected) {
    return;
  } else if (last_index > _last_expected) {
    last_index = _last_expected;
  }

  if (first_index >= _last_expected) {
    return;
  } else if (first_index < _first_expected) {
    first_index = _first_expected;
  }

  for (uint64_t i = first_index; i < last_index; i++) {
    if (_buf[i] != 0 && _bytes_pending > 0) {
      _bytes_pending--;
    }
    _buf[i] = data[i-old_first_index];
  }

  if (first_index == _first_expected) {
    string temp;
    uint64_t ac = output.available_capacity();
    if (_capacity < ac) {
      ac = _capacity;
    }
    uint64_t end = get_string(temp, ac);
    
    output.push(temp);

    if (_bytes_pending <= end ) {
      _bytes_pending = 0;
    } else {
      _bytes_pending -= end;
    }

    _first_expected = end;

    if ((int64_t)end >= last_byte && last_byte >= 0) {
      output.close();
    }

    for (uint64_t i = _last_expected; i < _first_expected+_capacity; i++) {
      _buf.push_back(0);
    }
    _last_expected = _first_expected+_capacity;
  } else {
    _bytes_pending += last_index - first_index;
  }

}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return _bytes_pending;
}

Reassembler::Reassembler() : _buf(vector<char>{}), _capacity(0), _first_expected(0), 
_last_expected(0), _bytes_pending(0), has_inited(false), last_byte(-1)
{
  
}

uint64_t Reassembler::get_string(std::string& str, uint64_t ac) {
  uint64_t i = _first_expected;
  for (; i < ac+_first_expected; i++) {
    if (_buf[i] != 0) {
      str += _buf[i];
    } else {
      break;
    }
  }
  return i;
}
