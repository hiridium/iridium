// Copyright (c) 2014-2019 Coin Sciences Ltd
// Iridium code distributed under the GPLv3 license, see COPYING file.

#ifndef IRIDIUM_CALLBACKS_H_
#define IRIDIUM_CALLBACKS_H_

#include <map>
#include <v8.h>

namespace mc_v8
{
extern std::map<std::string, v8::FunctionCallback> callbackLookup;
  std::string callbackFixedName(std::string name);
} // namespace mc_v8

#endif /* IRIDIUM_CALLBACKS_H_ */
