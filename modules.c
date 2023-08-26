#include "modules.h"

#include "ra4m1.h"

void enable_module_sci(long sciIdx)
{
    unsigned long old_mask_level = 0U;
    old_mask_level = __get_PRIMASK(); 
    __set_PRIMASK(1);
    R_MSTP_MSTPCRB &= ~BSP_MSTP_BIT_FSP_IP_SCI(sciIdx);
    __set_PRIMASK(old_mask_level);
}
