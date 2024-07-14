#include "zf_common_headfile.h"



void flashwrite(uint8_t page, float* wdata, uint8_t lenss)
{

   if(flash_check(0,page))
   {
        flash_erase_page(0,0);//сп╬м╡аЁЩ
   }

    flash_buffer_clear();

    for(int i = 0;i < lenss;i++)
    {
        flash_union_buffer[i].float_type = wdata[i];
    }

    flash_write_page_from_buffer(0,page,lenss);
}

void flash_read(uint8_t page, float* rdata, uint8_t lenss)
{
    flash_buffer_clear();

    flash_read_page_to_buffer(0,page,lenss);

    rdata[0] = flash_union_buffer[0].float_type;
    rdata[1] = flash_union_buffer[1].float_type;
    rdata[2] = flash_union_buffer[2].float_type;
    rdata[3] = flash_union_buffer[3].float_type;
    rdata[4] = flash_union_buffer[4].float_type;
}