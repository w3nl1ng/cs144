#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), 
buf(std::queue<mytype::byte>()), num_of_byte_pushed(0), is_close(false), is_error(false),
num_of_byte_poped(0)  
{}

void Writer::push( string data )
{
  // Your code here.

  if (data == "") {
    return;
  }

  unsigned int i = 0;
  while (buf.size() < capacity_ && i < data.length()) {
    buf.push(data[i++]);
    num_of_byte_pushed++;
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
  static std::string ret;

  if (ret != "") {
    ret = "";
  }

  std::queue<mytype::byte> temp(buf);
  while (!temp.empty()) {
    // ret.append(1, static_cast<char>(temp.front()));
    ret += static_cast<char>(temp.front());
    temp.pop();
  }
  return std::string_view(ret);
}

bool Reader::is_finished() const
{
  // Your code here.
  return is_close && num_of_byte_poped == num_of_byte_pushed;
}

bool Reader::has_error() const
{
  // Your code here.
  return is_error;
}

void Reader::pop( uint64_t len )
{
  // Your code here.

  if (len >= buf.size()) {
    buf = std::queue<mytype::byte>();
    num_of_byte_poped += len;
    return;
  }

  while (len > 0 && buf.size() > 0) {
    buf.pop();
    len--;
    num_of_byte_poped++;
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
