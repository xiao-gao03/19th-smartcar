#ifndef __LORA_H__
#define __LORA_H__

extern uint8_t witch_one;
extern uint8_t number[4];


void lora_init(void);
void lora_receive();
void lora_stop();
void LQ_lora();

#endif
