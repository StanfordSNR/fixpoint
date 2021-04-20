#pragma once

#include <string>
#include <vector>

#include "name.hh"

class Thunk {
  private:
    // Name of the Encode
    Name encode_name_;
    // Path of the Thunk in the output Tree
    std::vector<int> path_;
    
  public: 
    // Constructor
    Thunk( const Name & encode_name, const std::vector<int> path )
      : encode_name_( encode_name ),
        path_( path )
    {}

    const Name & getEncode() const { return encode_name_; }
}; 

