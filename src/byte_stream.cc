#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), 
buf(std::string()), num_of_byte_pushed(0), is_close(false), is_error(false),
num_of_byte_poped(0)  
{}

void Writer::push( string data )
{
  // Your code here.

  if (buf.size() + data.size() <= capacity_) {
    buf.append(data);
    num_of_byte_pushed += data.size();
  } else {
    int left = available_capacity();
    buf.append(data.substr(0, left));
    num_of_byte_pushed += left;
  }
}



void Writer::close()
{
  // Your code here.
  is_close = true;
}

void Writer::set_error()
{
  // Your code here.
  is_error = true;
}

bool Writer::is_closed() const
{
  // Your code here.
  return is_close;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  // 使用容量减去现在buf的size
  return capacity_ - buf.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return num_of_byte_pushed;
}

string_view Reader::peek() const
{
  return std::string_view(buf);
}

bool Reader::is_finished() const
{
  // Your code here.
  return is_close && num_of_byte_poped == num_of_byte_pushed;
  // return is_close;
}

bool Reader::has_error() const
{
  // Your code here.
  return is_error;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  int old = buf.size();
  if (len >= buf.size()) {
    buf.clear();
    num_of_byte_poped += old;
  } else {
    buf = buf.substr(len, old-len);
    num_of_byte_poped += len;
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buf.size();
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return num_of_byte_poped;
}
