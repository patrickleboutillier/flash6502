

uint8_t fetch(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  STEP_clr = 1 ; PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  INST_s.toggle() ; 
                    #ifdef ARDUINO
                        INST = DATA.read() ;
                    #endif
                    break ;
        case    2:  INST_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imp(uint8_t step) { //implied
    switch (step){
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t acc(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  ACC_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t step) { // 3 cycles
    switch (step){
        case    0:  break ;
        case    1:  EAh_s.toggle() ; break ;
        case    2:  EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    5:  EAl_s.toggle() ; break ;
        case    6:  EAl_s.toggle() ; break ;
        case    7:  RAM_e.toggle() ; PC_e.toggle() ; break ;

        case    8:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  break ;
        case    1:  EAh_s.toggle() ; break ; 
        case    2:  EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  X_e.toggle() ; break ; 
        case    5:  A_s.toggle() ; break ;
        case    6:  A_s.toggle() ; break ;
        case    7:  X_e.toggle() ; break ;
    
        case    8:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; PC_e.toggle() ; break ;
    
        case   12:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; break ;
        case   13:  EAl_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case   16:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ; 
        case   17:  B_s.toggle() ; break ;
        case   18:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   19:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  break ;
        case    1:  EAh_s.toggle() ; break ; 
        case    2:  EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  Y_e.toggle() ; break ; 
        case    5:  A_s.toggle() ; break ;
        case    6:  A_s.toggle() ; break ;
        case    7:  Y_e.toggle() ; break ;
    
        case    8:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; PC_e.toggle() ; break ;
    
        case   12:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; break ;
        case   13:  EAl_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case   16:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ; 
        case   17:  B_s.toggle() ; break ;
        case   18:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   19:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t step){ // 7 cycles
    switch (step){
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  A_s.toggle() ; B_s.toggle() ; break ;
        case    2:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;

        case    4:  ALU_op = ALU_SXT ; 
                    ALU_e.toggle() ; break ;
        case    5:  EAh_s.toggle() ; break ;
        case    6:  EAh_s.toggle() ; break ;
        case    7:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case    8:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
    
        case   12:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case   13:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
    
        case   16:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case   17:  A_s.toggle() ; break ;
        case   18:  A_s.toggle() ; break ;
        case   19:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
    
        case   20:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case   21:  B_s.toggle() ; break ;
        case   22:  B_s.toggle() ; break ;
        case   23:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
    
        case   24:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; break ;
        case   25:  EAh_s.toggle() ; break ;
        case   26:  EAh_s.toggle() ; break ;
        case   27:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t step) { // 3 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ; 
        case    1:  EAl_s.toggle() ; break ; 
        case    2:  EAl_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    4:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    5:  EAh_s.toggle() ; break ;
        case    6:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case    7:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;

        case    8:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  X_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;
        
        case    4:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    7:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    8:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    9:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   11:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  A_s.toggle() ; break ;
        case   14:  A_s.toggle() ; break ;
        case   15:  break ;

        case   16:  PC_e.toggle() ; RAM_e.toggle() ; break ; 
        case   17:  B_s.toggle() ; break ;
        case   18:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   19:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case   20:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; break ;
        case   21:  EAh_s.toggle() ; break ;
        case   22:  EAh_s.toggle() ; break ;
        case   23:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   24:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   25:  B_s.toggle() ; break ;
        case   26:  B_s.toggle() ; break ;
        case   27:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  Y_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; break ;
        
        case    4:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    7:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    8:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    9:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   11:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  A_s.toggle() ; break ;
        case   14:  A_s.toggle() ; break ;
        case   15:  break ;

        case   16:  PC_e.toggle() ; RAM_e.toggle() ; break ; 
        case   17:  B_s.toggle() ; break ;
        case   18:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   19:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case   20:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; break ;
        case   21:  EAh_s.toggle() ; break ;
        case   22:  EAh_s.toggle() ; break ;
        case   23:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   24:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   25:  B_s.toggle() ; break ;
        case   26:  B_s.toggle() ; break ;
        case   27:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t step) { // 8 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  EAl_s.toggle() ; B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; EAl_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ; 
        
        case    4:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    5:  EAh_s.toggle() ; break ;
        case    6:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case    7:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    8:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  A_s.toggle() ; break ;
        case   10:  A_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ;break ;
        
        case   12:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   13:  EAl_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   16:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   17:  B_s.toggle() ; break ;
        case   18:  B_s.toggle() ; break ;
        case   19:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;
        
        case   20:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case   21:  EAh_s.toggle() ; break ;
        case   22:  EAh_s.toggle() ; break ;
        case   23:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   24:  break ;
        case   25:  B_s.toggle() ; break ;
        case   26:  B_s.toggle() ; break ; 
        case   27:  break ;

        case   28:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; break ;
        case   29:  EAl_s.toggle() ; break ;
        case   30:  EAl_s.toggle() ; break ;
        case   31:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    4:  X_e.toggle() ; break ;
        case    5:  A_s.toggle() ; break ;
        case    6:  A_s.toggle() ; break ;
        case    7:  X_e.toggle() ; break ;

        case    8:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; break ;
        case    9:  EAl_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; break ;
        case   11:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   12:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case   13:  B_s.toggle() ; break ;
        case   14:  B_s.toggle() ; break ;
        case   15:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

        case   16:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   17:  EAl_s.toggle() ; break ;
        case   18:  EAl_s.toggle() ; break ;
        case   19:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   20:  EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   21:  EAh_s.toggle() ; break ;
        case   22:  EAh_s.toggle() ; break ;
        case   23:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case   24:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case   25:  EAl_s.toggle() ; break ;
        case   26:  EAl_s.toggle() ; break ;
        case   27:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   28:  EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   29:  B_s.toggle() ; break ;
        case   30:  B_s.toggle() ; break ;
        case   31:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case   32:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case   33:  EAl_s.toggle() ; break ;
        case   34:  EAl_s.toggle() ; break ;
        case   35:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   36:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   37:  B_s.toggle() ; break ;
        case   38:  B_s.toggle() ; break ;
        case   39:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
        
        case    4:  Y_e.toggle() ; break ;
        case    5:  A_s.toggle() ; break ;
        case    6:  A_s.toggle() ; break ;
        case    7:  Y_e.toggle() ; break ;

        case    8:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case    9:  EAl_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; break ;
        case   11:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   12:  EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   13:  EAh_s.toggle() ; break ;
        case   14:  EAh_s.toggle() ; break ;
        case   15:  RAM_e.toggle() ; EAl_e.toggle() ; break ;

        case   16:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case   17:  EAl_s.toggle() ; break ;
        case   18:  EAl_s.toggle() ; break ;
        case   19:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ; 
        
        case   20:  EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   21:  B_s.toggle() ; break ;
        case   22:  B_s.toggle() ; break ;
        case   23:  RAM_e.toggle() ; EAl_e.toggle() ; break ;
        
        case   24:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case   25:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   26:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   27:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case   28:  break ;
        case   29:  A_s.toggle() ; break ;
        case   30:  A_s.toggle() ; break ;
        case   31:  break ;
        
        case   32:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case   33:  B_s.toggle() ; break ;
        case   34:  B_s.toggle() ; break ;
        case   35:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;

        case   36:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; break ;
        case   37:  EAh_s.toggle() ; break ;
        case   38:  EAh_s.toggle() ; break ;
        case   39:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   40:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   41:  B_s.toggle() ; break ;
        case   42:  B_s.toggle() ; break ;
        case   43:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}
