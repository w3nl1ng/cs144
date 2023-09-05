#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  // (void)first_index;
  // (void)data;
  // (void)is_last_substring;
  // (void)output;

  // 如果设置了last就将其保存到_last_index
  if (is_last_substring) {
    _last_index = first_index + data.size();
    _is_last_index_set = true;
  }

  const uint64_t first_unacceptable = _first_unassembled_index + output.available_capacity();
  // 如果data不在可接受范围内，则直接返回
  if (first_index+data.size() < _first_unassembled_index || first_index >= first_unacceptable) {
    return;
  }

  // 至此为止，data必定存在可用的部分
    // 裁剪前面的不可用数据
    if (first_index < _first_unassembled_index) {
      data = data.substr(_first_unassembled_index-first_index);
      first_index = _first_unassembled_index;
    }

    // 裁剪后面的数据
    if (first_index+data.size() > first_unacceptable) {
      uint64_t overflow_size = first_index + data.size() - first_unacceptable;
      data = data.substr(0, data.size()-overflow_size);
    }

  // 至此，得到data经过裁剪后的全部可用数据
    // 初始化_buf和_bitmap
    for (uint64_t i = _buf.size(); i < first_index+data.size(); i++) {
      _buf.push_back(0);
      _bitmap.push_back(false);
    }

    // 开始填充data的可用部分
    for (uint64_t i = 0; i < data.size(); i++) {
      if (!_bitmap[i+first_index]) {
        _buf[i+first_index] = data[i];
        _bitmap[i+first_index] = true;
        _bytes_pending++;
      }
    }

  // 将可以push的数据都push到output中
  string push_data;
  while (_first_unassembled_index < _buf.size() && _bitmap[_first_unassembled_index]) {
    push_data += _buf[_first_unassembled_index];
    _bytes_pending--;
    _first_unassembled_index++;
  } 

  if (!push_data.empty()) {
    output.push(push_data);
  }
  if (_first_unassembled_index >= _last_index && _is_last_index_set) {
    output.close();
  }

}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return _bytes_pending;
}

Reassembler::Reassembler() :
  _buf(),
  _bitmap(),
  _first_unassembled_index(0),
  _last_index(0),
  _bytes_pending(0),
  _is_last_index_set(false)
  {}
