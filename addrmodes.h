uint8_t fetch(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  CU.INST_s.toggle() ; break ;
        case 0x02:  CU.INST_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imp(uint8_t tick) { //implied
    switch (tick){
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t acc(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t tick) { // 1 cycle
    switch (tick){
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t tick) { // 3 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  CU.EAh_s.toggle() ; break ;
        case 0x02:  CU.EAh_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x11:  CU.EAl_s.toggle() ; break ;
        case 0x12:  CU.EAl_s.toggle() ; break ;
        case 0x13:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; break ;

        case 0x20:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; CU.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t tick) { // 5 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  CU.EAh_s.toggle() ; break ; 
        case 0x02:  CU.EAh_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  C1.X_e.toggle() ; break ; 
        case 0x11:  C3.A_s.toggle() ; break ;
        case 0x12:  C3.A_s.toggle() ; break ;
        case 0x13:  C1.X_e.toggle() ; break ;
    
        case 0x20:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; break ;
    
        case 0x30:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x31:  CU.EAl_s.toggle() ; break ;
        case 0x32:  CU.EAl_s.toggle() ; break ;
        case 0x33:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case 0x40:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ; 
        case 0x41:  C3.B_s.toggle() ; break ;
        case 0x42:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x43:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; CU.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t tick) { // 5 cycles
    switch (tick){
        case 0x00:  break ;
        case 0x01:  CU.EAh_s.toggle() ; break ; 
        case 0x02:  CU.EAh_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  C1.Y_e.toggle() ; break ; 
        case 0x11:  C3.A_s.toggle() ; break ;
        case 0x12:  C3.A_s.toggle() ; break ;
        case 0x13:  C1.Y_e.toggle() ; break ;
    
        case 0x20:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; break ;
    
        case 0x30:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x31:  CU.EAl_s.toggle() ; break ;
        case 0x32:  CU.EAl_s.toggle() ; break ;
        case 0x33:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case 0x40:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ; 
        case 0x41:  C3.B_s.toggle() ; break ;
        case 0x42:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x43:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; CU.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t tick){ // 7 cycles
    switch (tick){
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;

        case 0x10:  C3.ALU_op = ALU_SXT ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  CU.EAh_s.toggle() ; break ;
        case 0x12:  CU.EAh_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case 0x20:  CU.PC_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; break ;
        case 0x23:  CU.Al2D_e.toggle() ; CU.PC_e.toggle() ; break ;
    
        case 0x30:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x31:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x32:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x33:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
    
        case 0x40:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x41:  C3.A_s.toggle() ; break ;
        case 0x42:  C3.A_s.toggle() ; break ;
        case 0x43:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
    
        case 0x50:  CU.PC_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x51:  C3.B_s.toggle() ; break ;
        case 0x52:  C3.B_s.toggle() ; break ;
        case 0x53:  CU.Ah2D_e.toggle() ; CU.PC_e.toggle() ; break ;
    
        case 0x60:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x61:  CU.EAh_s.toggle() ; break ;
        case 0x62:  CU.EAh_s.toggle() ; break ;
        case 0x63:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t tick) { // 3 cycles
    switch(tick) {
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ; 
        case 0x01:  CU.EAl_s.toggle() ; break ; 
        case 0x02:  CU.EAl_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x10:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x11:  CU.EAh_s.toggle() ; break ;
        case 0x12:  CU.EAh_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x13:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;

        case 0x20:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t tick) { // 7 cycles
    switch(tick) {
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;
        
        case 0x10:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x11:  C3.B_s.toggle() ; break ;
        case 0x12:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x13:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x20:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x21:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x22:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        
        case 0x30:  break ;
        case 0x31:  C3.A_s.toggle() ; break ;
        case 0x32:  C3.A_s.toggle() ; break ;
        case 0x33:  break ;

        case 0x40:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ; 
        case 0x41:  C3.B_s.toggle() ; break ;
        case 0x42:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x43:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x50:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x51:  CU.EAh_s.toggle() ; break ;
        case 0x52:  CU.EAh_s.toggle() ; break ;
        case 0x53:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case 0x60:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x61:  C3.B_s.toggle() ; break ;
        case 0x62:  C3.B_s.toggle() ; break ;
        case 0x63:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t tick) { // 7 cycles
    switch(tick) {
        case 0x00:  C1.Y_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; break ;
        
        case 0x10:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x11:  C3.B_s.toggle() ; break ;
        case 0x12:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x13:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x20:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x21:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x22:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        
        case 0x30:  break ;
        case 0x31:  C3.A_s.toggle() ; break ;
        case 0x32:  C3.A_s.toggle() ; break ;
        case 0x33:  break ;

        case 0x40:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ; 
        case 0x41:  C3.B_s.toggle() ; break ;
        case 0x42:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x43:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x50:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x51:  CU.EAh_s.toggle() ; break ;
        case 0x52:  CU.EAh_s.toggle() ; break ;
        case 0x53:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case 0x60:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x61:  C3.B_s.toggle() ; break ;
        case 0x62:  C3.B_s.toggle() ; break ;
        case 0x63:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t tick) { // 8 cycles
    switch(tick) {
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  CU.EAl_s.toggle() ; C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; CU.EAl_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ; 
        
        case 0x10:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x11:  CU.EAh_s.toggle() ; break ;
        case 0x12:  CU.EAh_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x13:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x20:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  C3.A_s.toggle() ; break ;
        case 0x22:  C3.A_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ;break ;
        
        case 0x30:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x31:  CU.EAl_s.toggle() ; break ;
        case 0x32:  CU.EAl_s.toggle() ; break ;
        case 0x33:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case 0x40:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x41:  C3.B_s.toggle() ; break ;
        case 0x42:  C3.B_s.toggle() ; break ;
        case 0x43:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;
        
        case 0x50:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x51:  CU.EAh_s.toggle() ; break ;
        case 0x52:  CU.EAh_s.toggle() ; break ;
        case 0x53:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case 0x60:  break ;
        case 0x61:  C3.B_s.toggle() ; break ;
        case 0x62:  C3.B_s.toggle() ; break ; 
        case 0x63:  break ;

        case 0x70:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x71:  CU.EAl_s.toggle() ; break ;
        case 0x72:  CU.EAl_s.toggle() ; break ;
        case 0x73:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t tick) { // 10 cycles
    switch(tick) {
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x10:  C1.X_e.toggle() ; break ;
        case 0x11:  C3.A_s.toggle() ; break ;
        case 0x12:  C3.A_s.toggle() ; break ;
        case 0x13:  C1.X_e.toggle() ; break ;

        case 0x20:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x21:  CU.EAl_s.toggle() ; break ;
        case 0x22:  CU.EAl_s.toggle() ; break ;
        case 0x23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0x30:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x31:  C3.B_s.toggle() ; break ;
        case 0x32:  C3.B_s.toggle() ; break ;
        case 0x33:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

        case 0x40:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x41:  CU.EAl_s.toggle() ; break ;
        case 0x42:  CU.EAl_s.toggle() ; break ;
        case 0x43:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0x50:  CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x51:  CU.EAh_s.toggle() ; break ;
        case 0x52:  CU.EAh_s.toggle() ; break ;
        case 0x53:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; break ;
        
        case 0x60:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x61:  CU.EAl_s.toggle() ; break ;
        case 0x62:  CU.EAl_s.toggle() ; break ;
        case 0x63:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0x70:  CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x71:  C3.B_s.toggle() ; break ;
        case 0x72:  C3.B_s.toggle() ; break ;
        case 0x73:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; break ;
        
        case 0x80:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x81:  CU.EAl_s.toggle() ; break ;
        case 0x82:  CU.EAl_s.toggle() ; break ;
        case 0x83:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0x90:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x91:  C3.B_s.toggle() ; break ;
        case 0x92:  C3.B_s.toggle() ; break ;
        case 0x93:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t tick) { // 10 cycles
    switch(tick) {
        case 0x00:  CU.PC_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x03:  CU.RAM_e.toggle() ; CU.PC_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        case 0x10:  C1.Y_e.toggle() ; break ;
        case 0x11:  C3.A_s.toggle() ; break ;
        case 0x12:  C3.A_s.toggle() ; break ;
        case 0x13:  C1.Y_e.toggle() ; break ;

        case 0x20:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x21:  CU.EAl_s.toggle() ; break ;
        case 0x22:  CU.EAl_s.toggle() ; break ;
        case 0x23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0x30:  CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x31:  CU.EAh_s.toggle() ; break ;
        case 0x32:  CU.EAh_s.toggle() ; break ;
        case 0x33:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; break ;

        case 0x40:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x41:  CU.EAl_s.toggle() ; break ;
        case 0x42:  CU.EAl_s.toggle() ; break ;
        case 0x43:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ; 
        
        case 0x50:  CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x51:  C3.B_s.toggle() ; break ;
        case 0x52:  C3.B_s.toggle() ; break ;
        case 0x53:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; break ;
        
        case 0x60:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x61:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x62:  CU.EAl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x63:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        
        case 0x70:  break ;
        case 0x71:  C3.A_s.toggle() ; break ;
        case 0x72:  C3.A_s.toggle() ; break ;
        case 0x73:  break ;
        
        case 0x80:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x81:  C3.B_s.toggle() ; break ;
        case 0x82:  C3.B_s.toggle() ; break ;
        case 0x83:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;

        case 0x90:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x91:  CU.EAh_s.toggle() ; break ;
        case 0x92:  CU.EAh_s.toggle() ; break ;
        case 0x93:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case 0xA0:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0xA1:  C3.B_s.toggle() ; break ;
        case 0xA2:  C3.B_s.toggle() ; break ;
        case 0xA3:  CU.RAM_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}