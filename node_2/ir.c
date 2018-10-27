
#include "ir.h"
#include "global_defines.h"

#warning set a pin_number
#define IR_PIN
#define IR_PORT
#define IR_DPORT //direction port

/*
 *How should we check for break in ir-light? Maybe an interupt? Or if we aren't doing anything else we can just have an
 * if setting and check. This has to be decided in the init function
 */

void ir_init(){
    //make it an output
    set_bit(IR_DPORT, IR_PIN);
}

void ir_emit_light(){
    set_bit(IR_PORT, IR_PIN);
}

void ir_stop_emit_light(){
    set_bit(IR_PORT, IR_PIN);
}