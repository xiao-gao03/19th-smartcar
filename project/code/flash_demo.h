#ifndef __FLASH_DEMO_H__
#define __FLASH_DEMO_H__

void flashwrite(uint8_t page, float* wdata, uint8_t lenss);
void flash_read(uint8_t page, float* rdata, uint8_t lenss);

#endif
