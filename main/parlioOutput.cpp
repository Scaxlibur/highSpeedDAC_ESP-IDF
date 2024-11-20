#include "parlioOutput.hpp"

PARLIO::PARLIO(){
    parlio_init();
}

void PARLIO::parlio_init(){
    parlio_new_tx_unit(&parlio_conf, &parlioHandle);
}