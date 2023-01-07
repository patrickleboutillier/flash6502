uint8_t fetch(uint8_t step) { // 1 cycle
    if ((INST == INST_IRQ)||(INST == INST_NMI)){
        // Interrupt (IRQ or NMI). The controller has already setup INST, so there is nothing else to do.
        switch (step){
            case    0:  INST_done = 0 ; break ;  // it's important that nothing else happens here
            case    1:  EAl_s.toggle() ; break ; // INST is also on the data bus at this point,
            case    2:  EAl_s.toggle() ; break ; //   store it in EAl
            default:    return 0 ;
        }
    }
    else {
        switch (step){
            case    0:  INST_done = 0 ; break ;   // it's important that nothing else happens here
            case    1:  PC_e.toggle() ; RAM_e.toggle() ; 
                        INST_s.toggle() ; 
                        #ifdef ARDUINO
                            INST = DATA.read() ;
                        #endif
                        break ;
            case    2:  INST_s.toggle() ; PC_up.toggle() ; break ;
            case    3:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ; break ;
            default:    return 0 ;
        }
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
        case    0:  ACC_e.toggle() ;
                    B_s.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  PC_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case    1:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t step) { // 3 cycles
    switch (step){
        case    0:  EAh_s.toggle() ; break ;
        case    1:  EAh_s.toggle() ; break ;

        case    2:  PC_e.toggle() ; RAM_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case    3:  EAl_s.toggle() ; break ;
        case    4:  PC_e.toggle() ;

                    EAl_e.toggle() ;
                    B_s.toggle() ; break ;
        case    5:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    6:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  EAh_s.toggle() ; break ; 
        case    1:  EAh_s.toggle() ; break ;

        case    2:  X_e.toggle() ; 
                    A_s.toggle() ; break ;
        case    3:  A_s.toggle() ; break ;
        case    4:  X_e.toggle() ;
    
                    PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  RAM_e.toggle() ; PC_e.toggle() ;
    
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    7:  EAl_s.toggle() ; break ;
        case    8:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case    9:  EAl_e.toggle() ; RAM_e.toggle() ;  
                    B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  EAh_s.toggle() ; break ; 
        case    1:  EAh_s.toggle() ; break ;

        case    2:  Y_e.toggle() ;  
                    A_s.toggle() ; break ;
        case    3:  A_s.toggle() ; break ;
        case    4:  Y_e.toggle() ;
    
                    PC_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  RAM_e.toggle() ; PC_e.toggle() ;
    
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    7:  EAl_s.toggle() ; break ;
        case    8:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case    9:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t step){ // 7 cycles
    switch (step){
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; 
                    A_s.toggle() ; B_s.toggle() ; break ;
        case    1:  A_s.toggle() ; B_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;

                    ALU_op = ALU_SXT ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case    3:  EAh_s.toggle() ; break ;
        case    4:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
    
        case    5:  PC_e.toggle() ; Al2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    6:  B_s.toggle() ; break ;
        case    7:  Al2D_e.toggle() ; PC_e.toggle() ;
    
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    8:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    9:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ;
    
                    EAh_e.toggle() ; Ah2D_e.toggle() ; 
                    A_s.toggle() ; break ;
        case   10:  A_s.toggle() ; break ;
        case   11:  Ah2D_e.toggle() ; EAh_e.toggle() ;
    
                    PC_e.toggle() ; Ah2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   12:  B_s.toggle() ; break ;
        case   13:  Ah2D_e.toggle() ; PC_e.toggle() ;
    
                    ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   14:  EAh_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t step) { // 3 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; 
                    EAl_s.toggle() ; break ; 
        case    1:  EAl_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  PC_up.toggle() ;
         
                    EAh_s.toggle() ; break ;
        case    3:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case    4:  PC_e.toggle() ; PC_up.toggle() ;

                    EAh_e.toggle() ; EAl_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  X_e.toggle() ;
                    A_s.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  X_e.toggle() ;
        
                    PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    3:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    4:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    5:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case    7:  A_s.toggle() ; break ;
        case    8:  A_s.toggle() ; break ;

        case    9:  PC_e.toggle() ; RAM_e.toggle() ;  
                    B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   11:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   12:  EAh_s.toggle() ; break ;
        case   13:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   14:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   15:  B_s.toggle() ; break ;
        case   16:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  Y_e.toggle() ; 
                    A_s.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  Y_e.toggle() ;
        
                    PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    3:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    4:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    5:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case    7:  A_s.toggle() ; break ;
        case    8:  A_s.toggle() ; break ;

        case    9:  PC_e.toggle() ; RAM_e.toggle() ;  
                    B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; PC_up.toggle() ; break ;
        case   11:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   12:  EAh_s.toggle() ; break ;
        case   13:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   14:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   15:  B_s.toggle() ; break ;
        case   16:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t step) { // 8 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; 
                    EAl_s.toggle() ; B_s.toggle() ; break ;
        case    1:  B_s.toggle() ; EAl_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  PC_up.toggle() ; 
        
                    EAh_s.toggle() ; break ;
        case    3:  EAh_s.toggle() ; PC_up.toggle() ; break ;
        case    4:  PC_e.toggle() ; PC_up.toggle() ;
        
                    EAh_e.toggle() ; EAl_e.toggle() ; 
                    A_s.toggle() ; break ;
        case    5:  A_s.toggle() ; break ;
        case    6:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ;
        
                    ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    7:  EAl_s.toggle() ; break ;
        case    8:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case    9:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ;
        
                    ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   12:  EAh_s.toggle() ; break ;
        case   13:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;
        
        case   14:  B_s.toggle() ; break ;
        case   15:  B_s.toggle() ; break ; 

        case   16:  ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case   17:  EAl_s.toggle() ; break ;
        case   18:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    1:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    X_e.toggle() ; 
                    A_s.toggle() ; break ;
        case    3:  A_s.toggle() ; break ;
        case    4:  X_e.toggle() ;

                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    5:  EAl_s.toggle() ; break ;
        case    6:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case    7:  EAl_e.toggle() ; Al2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    8:  B_s.toggle() ; break ;
        case    9:  Al2D_e.toggle() ; EAl_e.toggle() ;

                    ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; break ;
        case   11:  ALU_op = 0 ;
                    ALU_e.toggle() ; 

                    EAl_e.toggle() ; RAM_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   12:  EAh_s.toggle() ; break ;
        case   13:  RAM_e.toggle() ; EAl_e.toggle() ;
        
                    ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   16:  EAl_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case   17:  B_s.toggle() ; break ;
        case   18:  RAM_e.toggle() ; EAl_e.toggle() ;
        
                    ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case   19:  EAl_s.toggle() ; break ;
        case   20:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   21:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   22:  B_s.toggle() ; break ;
        case   23:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  PC_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case    1:  B_s.toggle() ; PC_up.toggle() ; break ;
        case    2:  RAM_e.toggle() ; PC_e.toggle() ; PC_up.toggle() ;
        
                    Y_e.toggle() ; 
                    A_s.toggle() ; break ;
        case    3:  A_s.toggle() ; break ;
        case    4:  Y_e.toggle() ;

                    ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    5:  EAl_s.toggle() ; break ;
        case    6:  ALU_op = 0 ;
                    ALU_e.toggle() ;

                    EAl_e.toggle() ; RAM_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case    7:  EAh_s.toggle() ; break ;
        case    8:  RAM_e.toggle() ; EAl_e.toggle() ;

                    ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; break ;
        case    9:  EAl_s.toggle() ; break ;
        case   10:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ; 
        
        case   11:  EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   12:  B_s.toggle() ; break ;
        case   13:  RAM_e.toggle() ; EAl_e.toggle() ;
        
                    ALU_op = ALU_ADD ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; 
                    EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   14:  EAl_s.toggle() ; ST_s.toggle() ; break ;
        case   15:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case   16:  A_s.toggle() ; break ;
        case   17:  A_s.toggle() ; break ;
        
        case   18:  EAh_e.toggle() ; Ah2D_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   19:  B_s.toggle() ; break ;
        case   20:  Ah2D_e.toggle() ; EAh_e.toggle() ;

                    ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; 
                    EAh_s.toggle() ; break ;
        case   21:  EAh_s.toggle() ; break ;
        case   22:  ALU_op = 0 ;
                    ALU_e.toggle() ; break ;

        case   23:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; 
                    B_s.toggle() ; break ;
        case   24:  B_s.toggle() ; break ;
        case   25:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}