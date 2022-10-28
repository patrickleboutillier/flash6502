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


uint8_t zp(uint8_t tick) { // 3 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  EAh_s = 1 ; break ;
        case 0x02:  EAh_s = 0 ; break ;
        case 0x03:  break ;

        case 0x10:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x11:  EAl_s = 1 ; break ;
        case 0x12:  EAl_s = 0 ; break ;
        case 0x13:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; break ;

        case 0x20:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x21:  B_s = 1 ; break ;
        case 0x22:  B_s = 0 ; break ;
        case 0x23:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t tick) { // 5 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  EAh_s = 1 ; break ; 
        case 0x02:  EAh_s = 0 ; break ;
        case 0x03:  break ;

        case 0x10:  X_e = 1 ; break ; 
        case 0x11:  A_s = 1 ; break ;
        case 0x12:  A_s = 0 ; break ;
        case 0x13:  X_e = 0 ; break ;
    
        case 0x20:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x21:  B_s = 1 ; break ;
        case 0x22:  B_s = 0 ; break ;
        case 0x23:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; break ;
    
        case 0x30:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x31:  EAl_s = 1 ; break ;
        case 0x32:  EAl_s = 0 ; break ;
        case 0x33:  ALU_e = 0 ; break ;
    
        case 0x40:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ; 
        case 0x41:  B_s = 1 ; break ;
        case 0x42:  B_s = 0 ; break ;
        case 0x43:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t tick) { // 5 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  EAh_s = 1 ; break ; 
        case 0x02:  EAh_s = 0 ; break ;
        case 0x03:  break ;

        case 0x10:  Y_e = 1 ; break ; 
        case 0x11:  A_s = 1 ; break ;
        case 0x12:  A_s = 0 ; break ;
        case 0x13:  Y_e = 0 ; break ;
    
        case 0x20:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x21:  B_s = 1 ; break ;
        case 0x22:  B_s = 0 ; break ;
        case 0x23:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; break ;
    
        case 0x30:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x31:  EAl_s = 1 ; break ;
        case 0x32:  EAl_s = 0 ; break ;
        case 0x33:  ALU_e = 0 ; break ;
    
        case 0x40:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ; 
        case 0x41:  B_s = 1 ; break ;
        case 0x42:  B_s = 0 ; break ;
        case 0x43:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; incPC() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t tick){ // 7 cycles
    switch (tick){
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  A_s = 1 ; B_s = 1 ; break ;
        case 0x02:  A_s = 0 ; B_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;

        case 0x10:  ALU_op = ALU_SXT ; ALU_e = 1 ; break ;
        case 0x11:  EAh_s = 1 ; break ;
        case 0x12:  EAh_s = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
    
        case 0x20:  PCl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x21:  B_s = 1 ; break ;
        case 0x22:  B_s = 0 ; break ;
        case 0x23:  Al2D_e = 0 ; PCl_e = 0 ; break ;
    
        case 0x30:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x31:  EAl_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x32:  STATUS_alu_c_set = 0 ; EAl_s = 0 ; break ;
        case 0x33:  ALU_e = 0 ; break ;
    
        case 0x40:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x41:  A_s = 1 ; break ;
        case 0x42:  A_s = 0 ; break ;
        case 0x43:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
    
        case 0x50:  PCh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x51:  B_s = 1 ; break ;
        case 0x52:  B_s = 0 ; break ;
        case 0x53:  Ah2D_e = 0 ; PCh_e = 0 ; break ;
    
        case 0x60:  ALU_op = ALU_ADC ; ALU_e = 1 ; break ;
        case 0x61:  EAh_s = 1 ; break ;
        case 0x62:  EAh_s = 0 ; break ;
        case 0x63:  ALU_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t tick) { // 3 cycles
    switch(tick) {
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ; 
        case 0x01:  EAl_s = 1 ; break ; 
        case 0x02:  EAl_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x10:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x11:  EAh_s = 1 ; break ;
        case 0x12:  EAh_s = 0 ; break ;
        case 0x13:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;

        case 0x20:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x21:  B_s = 1 ; break ;
        case 0x22:  B_s = 0 ; break ;
        case 0x23:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t tick) { // 7 cycles
    switch(tick) {
        case 0x00:  X_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  X_e = 0 ; break ;
        
        case 0x10:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x11:  B_s = 1 ; break ;
        case 0x12:  B_s = 0 ; break ;
        case 0x13:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x20:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x21:  EAl_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x22:  STATUS_alu_c_set = 0 ; EAl_s = 0 ; break ;
        case 0x23:  ALU_e = 0 ; break ;
        
        case 0x30:  break ;
        case 0x31:  A_s = 1 ; break ;
        case 0x32:  A_s = 0 ; break ;
        case 0x33:  break ;

        case 0x40:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ; 
        case 0x41:  B_s = 1 ; break ;
        case 0x42:  B_s = 0 ; break ;
        case 0x43:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x50:  ALU_op = ALU_ADC ; ALU_e = 1 ; break ;
        case 0x51:  EAh_s = 1 ; break ;
        case 0x52:  EAh_s = 0 ; break ;
        case 0x53:  ALU_e = 0 ; break ;
        
        case 0x60:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x61:  B_s = 1 ; break ;
        case 0x62:  B_s = 0 ; break ;
        case 0x63:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t tick) { // 7 cycles
    switch(tick) {
        case 0x00:  Y_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  Y_e = 0 ; break ;
        
        case 0x10:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x11:  B_s = 1 ; break ;
        case 0x12:  B_s = 0 ; break ;
        case 0x13:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x20:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x21:  EAl_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x22:  STATUS_alu_c_set = 0 ; EAl_s = 0 ; break ;
        case 0x23:  ALU_e = 0 ; break ;
        
        case 0x30:  break ;
        case 0x31:  A_s = 1 ; break ;
        case 0x32:  A_s = 0 ; break ;
        case 0x33:  break ;

        case 0x40:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ; 
        case 0x41:  B_s = 1 ; break ;
        case 0x42:  B_s = 0 ; break ;
        case 0x43:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x50:  ALU_op = ALU_ADC ; ALU_e = 1 ; break ;
        case 0x51:  EAh_s = 1 ; break ;
        case 0x52:  EAh_s = 0 ; break ;
        case 0x53:  ALU_e = 0 ; break ;
        
        case 0x60:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x61:  B_s = 1 ; break ;
        case 0x62:  B_s = 0 ; break ;
        case 0x63:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t tick) { // 8 cycles
    switch(tick) {
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  EAl_s = 1 ; B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; EAl_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ; 
        
        case 0x10:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x11:  EAh_s = 1 ; break ;
        case 0x12:  EAh_s = 0 ; break ;
        case 0x13:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x20:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x21:  A_s = 1 ; break ;
        case 0x22:  A_s = 0 ; break ;
        case 0x23:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;break ;
        
        case 0x30:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x31:  EAl_s = 1 ; break ;
        case 0x32:  EAl_s = 0 ; break ;
        case 0x33:  ALU_e = 0 ; break ;
        
        case 0x40:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x41:  B_s = 1 ; break ;
        case 0x42:  B_s = 0 ; break ;
        case 0x43:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        
        case 0x50:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x51:  EAh_s = 1 ; break ;
        case 0x52:  EAh_s = 0 ; break ;
        case 0x53:  ALU_e = 0 ; break ;
        
        case 0x60:  break ;
        case 0x61:  B_s = 1 ; break ;
        case 0x62:  B_s = 0 ; break ; 
        case 0x63:  break ;

        case 0x70:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x71:  EAl_s = 1 ; break ;
        case 0x72:  EAl_s = 0 ; break ;
        case 0x73:  ALU_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t tick) { // 10 cycles
    switch(tick) {
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x10:  X_e = 1 ; break ;
        case 0x11:  A_s = 1 ; break ;
        case 0x12:  A_s = 0 ; break ;
        case 0x13:  X_e = 0 ; break ;

        case 0x20:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x21:  EAl_s = 1 ; break ;
        case 0x22:  EAl_s = 0 ; break ;
        case 0x23:  ALU_e = 0 ; break ;

        case 0x30:  EAl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x31:  B_s = 1 ; break ;
        case 0x32:  B_s = 0 ; break ;
        case 0x33:  Al2D_e = 0 ; EAl_e = 0 ; break ;

        case 0x40:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x41:  EAl_s = 1 ; break ;
        case 0x42:  EAl_s = 0 ; break ;
        case 0x43:  ALU_e = 0 ; break ;

        case 0x50:  EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x51:  EAh_s = 1 ; break ;
        case 0x52:  EAh_s = 0 ; break ;
        case 0x53:  RAM_e = 0 ; EAl_e = 0 ; break ;
        
        case 0x60:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x61:  EAl_s = 1 ; break ;
        case 0x62:  EAl_s = 0 ; break ;
        case 0x63:  ALU_e = 0 ; break ;

        case 0x70:  EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x71:  B_s = 1 ; break ;
        case 0x72:  B_s = 0 ; break ;
        case 0x73:  RAM_e = 0 ; EAl_e = 0 ; break ;
        
        case 0x80:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x81:  EAl_s = 1 ; break ;
        case 0x82:  EAl_s = 0 ; break ;
        case 0x83:  ALU_e = 0 ; break ;

        case 0x90:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x91:  B_s = 1 ; break ;
        case 0x92:  B_s = 0 ; break ;
        case 0x93:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t tick) { // 10 cycles
    switch(tick) {
        case 0x00:  PCh_e = 1 ; PCl_e = 1 ; RAM_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  RAM_e = 0 ; PCl_e = 0 ; PCh_e = 0 ; incPC() ; break ;
        
        case 0x10:  Y_e = 1 ; break ;
        case 0x11:  A_s = 1 ; break ;
        case 0x12:  A_s = 0 ; break ;
        case 0x13:  Y_e = 0 ; break ;

        case 0x20:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x21:  EAl_s = 1 ; break ;
        case 0x22:  EAl_s = 0 ; break ;
        case 0x23:  ALU_e = 0 ; break ;

        case 0x30:  EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x31:  EAh_s = 1 ; break ;
        case 0x32:  EAh_s = 0 ; break ;
        case 0x33:  RAM_e = 0 ; EAl_e = 0 ; break ;

        case 0x40:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x41:  EAl_s = 1 ; break ;
        case 0x42:  EAl_s = 0 ; break ;
        case 0x43:  ALU_e = 0 ; break ; 
        
        case 0x50:  EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0x51:  B_s = 1 ; break ;
        case 0x52:  B_s = 0 ; break ;
        case 0x53:  RAM_e = 0 ; EAl_e = 0 ; break ;
        
        case 0x60:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x61:  EAl_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x62:  STATUS_alu_c_set = 0 ; EAl_s = 0 ; break ;
        case 0x63:  ALU_e = 0 ; break ;
        
        case 0x70:  break ;
        case 0x71:  A_s = 1 ; break ;
        case 0x72:  A_s = 0 ; break ;
        case 0x73:  break ;
        
        case 0x80:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x81:  B_s = 1 ; break ;
        case 0x82:  B_s = 0 ; break ;
        case 0x83:  Ah2D_e = 0 ; EAh_e = 0 ; break ;

        case 0x90:  ALU_op = ALU_ADC ; ALU_e = 1 ; break ;
        case 0x91:  EAh_s = 1 ; break ;
        case 0x92:  EAh_s = 0 ; break ;
        case 0x93:  ALU_e = 0 ; break ;

        case 0xA0:  EAh_e = 1 ; EAl_e = 1 ; RAM_e = 1 ; break ;
        case 0xA1:  B_s = 1 ; break ;
        case 0xA2:  B_s = 0 ; break ;
        case 0xA3:  RAM_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}