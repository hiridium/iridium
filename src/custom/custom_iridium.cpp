// Copyright (c) 2014-2019 Coin Sciences Ltd
// Iridium code distributed under the GPLv3 license, see COPYING file.

#include "iridium/iridium.h"

void* custom_get_blockchain_default(const char *param,int* size,void *param_in)
{
    *size=0;
    
    return NULL;
}

