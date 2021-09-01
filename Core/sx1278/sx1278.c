#include "sx1278.h"

void sx1278_init(sx1278_handle *p_sx1278)
{
    sx_hw_init(&(p_sx1278->hw));
    
}

void sx1278_change_mode(sx1278_handle *p_sx1278, sx1278_mode mode)
{
    
}