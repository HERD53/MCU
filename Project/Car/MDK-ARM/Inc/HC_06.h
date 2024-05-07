#ifndef __HC_06_H
#define __HC_06_H

#define Receive_Num 64

extern uint8_t Receive_Data[1];								//串口接收数组
extern uint8_t Receive_Cache[Receive_Num];		//接收缓存区
extern uint8_t Uart_Receive[Receive_Num];			//将数据传输到外面

#endif
