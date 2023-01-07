uint8_t fetch(uint8_t step) { // 1 cycle
    if ((INST == INST_IRQ)||(INST == INST_NMI)){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        // Interrupt (IRQ or NMI). The controller has already setup INST, so there is nothing else to do.
        switch (step){
            case NEXT:  C1.INST_done = 0 ; break ;  // it's important that nothing else happens here
            case NEXT:  C4.EAl_s.toggle() ; break ; // INST is also on the data bus at this point,
            case NEXT:  C4.EAl_s.toggle() ; break ; //   store it in EAl
            default:    return 0 ;
        }
    }
    else {
        switch (step){
            enum { COUNTER_BASE = __COUNTER__ } ;
            #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
            case NEXT:  C1.INST_done = 0 ; break ;   // it's important that nothing else happens here
            case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                        C2.INST_s.toggle() ; 
                        #ifdef ARDUINO
                            INST = DATA.read() ;
                        #endif
                        break ;
            case NEXT:  C2.INST_s.toggle() ; C2.PC_up.toggle() ; break ;
            case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
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
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C1.ACC_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t step) { // 1 cycle
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t step) { // 3 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;

        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C2.PC_e.toggle() ; break ;

        case NEXT:  C4.EAl_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t step) { // 5 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C4.EAh_s.toggle() ; break ; 
        case NEXT:  C4.EAh_s.toggle() ; break ;

        case NEXT:  C1.X_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
    
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ;  
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t step) { // 5 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C4.EAh_s.toggle() ; break ; 
        case NEXT:  C4.EAh_s.toggle() ; break ;

        case NEXT:  C1.Y_e.toggle() ;  
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
    
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t step){ // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C1.A_s.toggle() ; C3.B_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_SXT ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case NEXT:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; 
                    C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
    
        case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
    
        case NEXT:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case NEXT:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t step) { // 3 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ; 
        case NEXT:  C4.EAl_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.PC_up.toggle() ;
         
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;

        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t step) { // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C1.X_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
        
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; 
                    C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;

        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ;  
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t step) { // 7 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C1.Y_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
        
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; 
                    C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;

        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ;  
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t step) { // 8 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C4.EAl_s.toggle() ; C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C4.EAl_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.PC_up.toggle() ; 
        
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ; 

        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t step) { // 10 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C1.X_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t step) { // 10 cycles
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch(step) {
        case NEXT:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case NEXT:  C1.Y_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ; 
        
        case NEXT:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; 
                    C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}