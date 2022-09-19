/*
 * AppCore.h
 *
 *  Created on: 28 de ago de 2022
 *      Author: eric_
 */

#ifndef INC_APPCORE_H_
#define INC_APPCORE_H_

//// ENUM

typedef enum {
    SYS_EVENT_NONE = 0,
    SYS_EVENT_TIMER_100_MSEC,
    SYS_EVENT_TIMER_250_MSEC
} SYS_EVENT;

//// EXTERNAL FUNCTION DECLARATION

void app_init();
void app_loop();

int* get_matrix_buf();

void push_event(SYS_EVENT ev);

#endif /* INC_APPCORE_H_ */
