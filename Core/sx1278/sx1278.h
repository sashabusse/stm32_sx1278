#ifndef __SX1278_H
#define __SX1278_H
#include "sx1278_defs.h"
#include "sx1278_hw_impl.h"

typedef struct __sx1278_handle
{
    sx1278_hw hw;
} sx1278_handle;

void sx1278_init(sx1278_handle *p_sx1278);
void sx1278_change_mode(sx1278_handle *p_sx1278, sx1278_mode mode);
void sx1278_sleep(sx1278_handle *p_sx1278);
void sx1278_stdby(sx1278_handle *p_sx1278);
void sx1278_fs

#endif