
uint8_t adc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ;
                    A_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  A_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case NEXT:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ;

                    INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_AND ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    
                    INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  ACC_e.toggle() ;
                        A_s.toggle() ; B_s.toggle() ; break ;
            case NEXT:  A_s.toggle() ; B_s.toggle() ; break ;
            case NEXT:  ACC_e.toggle() ; break ;

            case NEXT:  ALU_op = ALU_ADD ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;

                        INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  ALU_op = ALU_ADD ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
            
                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t step){
    if (! STATUS.C){ 
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {  
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;
            
                        INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcs(uint8_t step) {
    if (STATUS.C){ 
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            // TODO: Why do we need 3 breaks here...
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t beq(uint8_t step){
    if (STATUS.Z){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bit_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_BIT ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ;

                    INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t step){
    if (STATUS.N){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bne(uint8_t step){
    if (! STATUS.Z){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;                        
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bpl(uint8_t step){
    if (! STATUS.N){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t brk(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        // Inc PC
        case NEXT:  PC_up.toggle() ; break ;
        case NEXT:  PC_up.toggle() ; 
        // PCh to B
                    PC_e.toggle() ; Ah2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // PCl to B
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_down.toggle() ; break ;
        // Push Status (w/BREAK, via ST_bi)
        case NEXT:  ST_bi.toggle() ; ST_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; SP_down.toggle() ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh and EAl
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; 
                    EAl_s.toggle() ; EAh_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case NEXT:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; break ;
        // EAl to B
        case NEXT:  Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE) to EAl
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case NEXT:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ;
        // Set Interrupt flag
                    ST_bi.toggle() ; ST_I_s.toggle() ;            
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ;

                    INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t _interrupt(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        // PCh to B
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // PCl to B
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // Push Status
        case NEXT:  SP_e.toggle() ; ST_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh, 0xFF/0xFB already in EAl
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ;
                    EAh_s.toggle() ; break ;
        case NEXT:  EAh_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case NEXT:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; break ;
        // EAl to B
        case NEXT:  Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE/0xFA) to EAl
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case NEXT:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ;
        // Set Interrupt flag
                    ST_bi.toggle() ; ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ;

                    INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t irq(uint8_t step) {
    return _interrupt(step) ;
}


uint8_t nmi(uint8_t step) {
    return _interrupt(step) ;
}


uint8_t bvc(uint8_t step){
    if (! STATUS.V){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;

                        INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bvs(uint8_t step){
    if (STATUS.V){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                        PCh_s.toggle() ; break ;
            case NEXT:  PCh_s.toggle() ; break ;
            case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                        PCl_s.toggle() ; break ;
            case NEXT:  PCl_s.toggle() ; break ;
            case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ;
        
                        INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  break ;
            case NEXT:  INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


// OPT


uint8_t clc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;

        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;
        
        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cld(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cli_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_I_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t clv(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;

        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_V_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_V_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  X_e.toggle() ; 
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ; 

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  Y_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  ALU_op = ALU_DEC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    RAM_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  X_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  Y_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_EOR ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ALU_op = ALU_INC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    RAM_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;        

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  X_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  Y_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        
        case NEXT:  INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ;
                    PCl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
    
        case NEXT:  B_s.toggle() ; break ; 
        case NEXT:  B_s.toggle() ; break ;

        case NEXT:  ALU_op = ALU_SBC ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ; 

                    INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t step) {
    if ((INST & 0xF) == 0xA) {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  ALU_op = ALU_LSR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;            

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  ALU_op = ALU_LSR ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nop(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ora(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ;
                    A_s.toggle() ; break ;
        case NEXT:  A_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_ORA ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ; SP_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        case NEXT:  INST_done = 1 ; break ;       
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pla(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                        ST_clk.toggle() ; break ;
            case NEXT:  ST_clk.toggle() ; break ;
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case NEXT:  ALU_op = ALU_ROL ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;            
            
            default:    return 0 ;
        }
    }
    else {
         enum { COUNTER_BASE = __COUNTER__ } ;
         #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
         switch (step) {
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                        ST_clk.toggle() ; break ;
            case NEXT:  ST_clk.toggle() ; break ;
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case NEXT:  ALU_op = ALU_ROL ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t step) {
    if ((INST & 0xF) == 0xA){
         enum { COUNTER_BASE = __COUNTER__ } ;
         #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
         switch (step) {
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                        ST_clk.toggle() ; break ;
            case NEXT:  ST_clk.toggle() ; break ;
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case NEXT:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
         enum { COUNTER_BASE = __COUNTER__ } ;
         #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
         switch (step) {
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                        ST_clk.toggle() ; break ;
            case NEXT:  ST_clk.toggle() ; break ;
            case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case NEXT:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ;
                        RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  RAM_s.toggle() ; ST_clk.toggle() ; break ;
            case NEXT:  ALU_op = 0 ; 
                        ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case NEXT:  INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { // 9 cycles
        // SP to B
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to STATUS
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;  
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        // SP to B
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to PCl
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        // SP to B
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to PCh
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; SP_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case NEXT:  SP_e.toggle() ; RAM_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; PC_up.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; SP_e.toggle() ; PC_up.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                    A_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  A_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case NEXT:  ALU_op = ALU_SBC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // The STATUS word is never 0, at a minimum the constant bits will be on.
        // Decrementing it will always produce a carry.
        case NEXT:  ST_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  ST_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sed(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
 
    switch (step) {
        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sei_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sta(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; ACC_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; X_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; Y_e.toggle() ;
                    RAM_s.toggle() ; break ;
        case NEXT:  RAM_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  ACC_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  Y_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  X_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  X_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  X_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;

        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ;
                    SP_s.toggle() ; break ;
        case NEXT:  SP_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  Y_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        
        case NEXT:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ;
                    ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst1(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // Set registers, SP and STATUS to 0
        case NEXT:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ;
                    ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_clk.toggle() ; break ;
        case NEXT:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        // Set ALU_c to 0 
        case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        // Decrement SP once to reach 0xFF
        case NEXT:  SP_down.toggle() ; break ;
        case NEXT:  SP_down.toggle() ; break ;
        // While SP == 0xFF, copy it to EAh in prep for reset vector
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    EAh_s.toggle() ;  break ;
        case NEXT:  EAh_s.toggle() ;  break ;
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        // Decrement SP twice again to reach 0xFD
        case NEXT:  SP_down.toggle() ; break ;
        case NEXT:  SP_down.toggle() ; break ;
        case NEXT:  SP_down.toggle() ; break ;
        case NEXT:  SP_down.toggle() ; break ;
        // Copy SP to EAl, EA now 0xFFFD
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ;
                    EAl_s.toggle() ;  break ;
        case NEXT:  EAl_s.toggle() ;  break ;
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;    
}


uint8_t rst2(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // RAM[EA] to PCh
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ;
                    PCh_s.toggle() ; break ;
        case NEXT:  PCh_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; break ;
        // Send EAl to B
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ;
                    B_s.toggle() ; break ;
        case NEXT:  B_s.toggle() ; break ;
        case NEXT:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        // Decrement to EAl (will be 0xFC)
        case NEXT:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ;
                    EAl_s.toggle() ; break ;
        case NEXT:  EAl_s.toggle() ; break ;
        case NEXT:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ; 
        // RAM[EA] to PCl
        case NEXT:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ;
                    PCl_s.toggle() ; break ;
        case NEXT:  PCl_s.toggle() ; break ;
        case NEXT:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ;  break ;
        // Disable interrupts by setting the interrupt flag
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ;
                    ST_clk.toggle() ; break ;
        case NEXT:  ST_clk.toggle() ; break ;
        case NEXT:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        
        case NEXT:  INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t mon(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // PCh
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case NEXT:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        // PCl
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case NEXT:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        // EAh
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case NEXT:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        // EAl
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case NEXT:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        // SP
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case NEXT:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        // ACC
        case NEXT:  ACC_e.toggle() ; break ;
        case NEXT:  ACC_e.toggle() ; break ;
        // X
        case NEXT:  X_e.toggle() ; break ;
        case NEXT:  X_e.toggle() ; break ;
        // Y
        case NEXT:  Y_e.toggle() ; break ;
        case NEXT:  Y_e.toggle() ; break ;
        // STATUS
        case NEXT:  ST_e.toggle() ; break ;
        case NEXT:  ST_e.toggle() ; break ;

        case NEXT:  INST_done = 1 ; break ;
                
        default:    return 0 ;
    }
    return 1 ;
}
