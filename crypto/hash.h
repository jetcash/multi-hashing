#pragma once

#include "hash-ops.h"

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;

#ifdef __cplusplus

#include <string>

typedef std::string blobdata;

namespace crypto {
  struct hash {
    char data[HASH_SIZE];
  };
}

#endif
