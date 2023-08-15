#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>
#include <sstream>

using namespace std;
using std::stringstream;

void get_URL( const string& host, const string& path )
{
  // cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  // cerr << "Warning: get_URL() has not been implemented yet.\n";

  stringstream fmt;  
  
  fmt << "GET " << path << " HTTP/1.1\r\n"
      << "Host: " << host << "\r\n"
      << "Connection: close\r\n"
      << "\r\n"
      << "\r\n";

  // 需要发送的http请求
  std::string http_request = fmt.str();

  const Address address(host, "http");
  TCPSocket tcpsocket;

  // 连接服务器并发送http请求
  tcpsocket.connect(address);
  tcpsocket.write(http_request);

  string http_resp;
  string buf;

  // 只要还未读到eof并且tcp连接未关闭，就一直读取
  while (!tcpsocket.eof() && !tcpsocket.closed()) {
    tcpsocket.read(buf);
    http_resp += buf;
  }

  if (tcpsocket.closed()) {
    tcpsocket.close();
  }

  cout << http_resp;
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
