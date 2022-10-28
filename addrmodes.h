uint8_t fetch(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  INST_s = 1 ; break ;
        case 0x02:  INST_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t acc(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}