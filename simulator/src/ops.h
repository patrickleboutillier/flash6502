
uint8_t adc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ;
                    C1.A_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ;

                    C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.ACC_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_AND ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    
                    C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  C1.ACC_e.toggle() ;
                        C1.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case NEXT:  C1.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case NEXT:  C1.ACC_e.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ADD ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;

                        C1.INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) { 
            case NEXT:  C1.ACC_e.toggle() ;
                        C1.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case NEXT:  C1.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case NEXT:  C1.ACC_e.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ADD ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
            
                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;
            
                        C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C1.INST_done = 1 ; break ;

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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C1.INST_done = 1 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bit_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.ACC_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_BIT ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ;

                    C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t step){
    if (STATUS.N){  
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
        case NEXT:  C2.PC_up.toggle() ; break ;
        case NEXT:  C2.PC_up.toggle() ; 
        // PCh to B
                    C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        // PCl to B
        case NEXT:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_down.toggle() ; break ;
        // Push Status (w/BREAK, via ST_bi)
        case NEXT:  C5.ST_bi.toggle() ; C3.ST_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_e.toggle() ; C5.ST_bi.toggle() ; C3.ST_e.toggle() ; C2.SP_down.toggle() ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh and EAl
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; 
                    C4.EAl_s.toggle() ; C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case NEXT:  C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; break ;
        // EAl to B
        case NEXT:  C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE) to EAl
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ;
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case NEXT:  C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ;
        // Set Interrupt flag
                    C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;            
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;

                    C1.INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t _interrupt(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step){
        // PCh to B
        case NEXT:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        // PCl to B
        case NEXT:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        // Push Status
        case NEXT:  C2.SP_e.toggle() ; C3.ST_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_e.toggle() ; C3.ST_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh, 0xFF/0xFB already in EAl
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ;
                    C4.EAh_s.toggle() ; break ;
        case NEXT:  C4.EAh_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case NEXT:  C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; break ;
        // EAl to B
        case NEXT:  C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE/0xFA) to EAl
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ;
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case NEXT:  C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ;
        // Set Interrupt flag
                    C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;

                    C1.INST_done = 1 ; break ;
        
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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;

                        C1.INST_done = 1 ; break ;

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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                        C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.PCh_s.toggle() ; break ;
            case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                        C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.PCl_s.toggle() ; break ;
            case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ;
        
                        C1.INST_done = 1 ; break ;
            
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
            case NEXT:  C1.INST_done = 1 ; break ;
            
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
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; break ;
        
        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cld(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cli_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_I_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t clv(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_V_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_V_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.ACC_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_CMP ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.X_e.toggle() ; 
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_CMP ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ; 

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.Y_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_CMP ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.X_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C1.Y_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_EOR ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;        

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.X_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.Y_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case NEXT:  C1.INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case NEXT:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ;
                    C4.PCl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
    
        case NEXT:  C3.B_s.toggle() ; break ; 
        case NEXT:  C3.B_s.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_SBC ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case NEXT:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case NEXT:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; 

                    C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t step) {
    if ((INST & 0xF) == 0xA) {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  C3.ALU_op = ALU_LSR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;            

            default:    return 0 ;
        }
    }
    else {
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  C3.ALU_op = ALU_LSR ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nop(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ora(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ;
                    C1.A_s.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_ORA ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C2.SP_e.toggle() ; C5.ST_bi.toggle() ; C3.ST_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_e.toggle() ; C5.ST_bi.toggle() ; C3.ST_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case NEXT:  C1.INST_done = 1 ; break ;       
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pla(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) { 
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        enum { COUNTER_BASE = __COUNTER__ } ;
        #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
        switch (step) {
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                        C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ROL ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;            
            
            default:    return 0 ;
        }
    }
    else {
         enum { COUNTER_BASE = __COUNTER__ } ;
         #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
         switch (step) {
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                        C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ROL ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;

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
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                        C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;

            default:    return 0 ;
        }
    }
    else {
         enum { COUNTER_BASE = __COUNTER__ } ;
         #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
         switch (step) {
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                        C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_clk.toggle() ; break ;
            case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case NEXT:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ;
                        C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C2.RAM_s.toggle() ; C5.ST_clk.toggle() ; break ;
            case NEXT:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case NEXT:  C1.INST_done = 1 ; break ;

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
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[SP] to STATUS
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;  
                    C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ; break ;
        // SP to B
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[SP] to PCl
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        // SP to B
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        // INC B to SP
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        // RAM[SP] to PCh
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case NEXT:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; C2.PC_up.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                    C1.A_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.A_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_SBC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

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
        case NEXT:  C3.ST_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C3.ST_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sed(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
 
    switch (step) {
        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sei_(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sta(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.ACC_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.X_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.Y_e.toggle() ;
                    C2.RAM_s.toggle() ; break ;
        case NEXT:  C2.RAM_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.ACC_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.ACC_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.Y_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.X_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.X_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.X_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.X_e.toggle() ; break ;

        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ;
                    C2.SP_s.toggle() ; break ;
        case NEXT:  C2.SP_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t step) {
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        case NEXT:  C1.Y_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C1.Y_e.toggle() ; break ;
        
        case NEXT:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ;
                    C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst1(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // Set registers, SP and STATUS to 0
        case NEXT:  C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ;
                    C1.ACC_s.toggle() ; C1.X_s.toggle() ; C1.Y_s.toggle() ; C1.A_s.toggle() ; C3.B_s.toggle() ;
                    C2.SP_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C1.ACC_s.toggle() ; C1.X_s.toggle() ; C1.Y_s.toggle() ; C1.A_s.toggle() ; C3.B_s.toggle() ;
                    C2.SP_s.toggle() ; C5.ST_clk.toggle() ; break ;
        case NEXT:  C3.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; C5.ST_I_s.toggle() ; break ;
        // Set ALU_c to 0 
        case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        // Decrement SP once to reach 0xFF
        case NEXT:  C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_down.toggle() ; break ;
        // While SP == 0xFF, copy it to EAh in prep for reset vector
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C4.EAh_s.toggle() ;  break ;
        case NEXT:  C4.EAh_s.toggle() ;  break ;
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        // Decrement SP twice again to reach 0xFD
        case NEXT:  C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_down.toggle() ; break ;
        case NEXT:  C2.SP_down.toggle() ; break ;
        // Copy SP to EAl, EA now 0xFFFD
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ;
                    C4.EAl_s.toggle() ;  break ;
        case NEXT:  C4.EAl_s.toggle() ;  break ;
        case NEXT:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;

        case NEXT:  C1.INST_done = 1 ; break ;

        default:    return 0 ;
    }
    return 1 ;    
}


uint8_t rst2(uint8_t step){
    enum { COUNTER_BASE = __COUNTER__ } ;
    #define NEXT (__COUNTER__ - COUNTER_BASE - 1)
    
    switch (step) {
        // RAM[EA] to PCh
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCh_s.toggle() ; break ;
        case NEXT:  C4.PCh_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; break ;
        // Send EAl to B
        case NEXT:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ;
                    C3.B_s.toggle() ; break ;
        case NEXT:  C3.B_s.toggle() ; break ;
        case NEXT:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;
        // Decrement to EAl (will be 0xFC)
        case NEXT:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ;
                    C4.EAl_s.toggle() ; break ;
        case NEXT:  C4.EAl_s.toggle() ; break ;
        case NEXT:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ; 
        // RAM[EA] to PCl
        case NEXT:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ;
                    C4.PCl_s.toggle() ; break ;
        case NEXT:  C4.PCl_s.toggle() ; break ;
        case NEXT:  C2.RAM_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ;  break ;
        // Disable interrupts by setting the interrupt flag
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ;
                    C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_clk.toggle() ; break ;
        case NEXT:  C5.ST_bi.toggle() ; C5.ST_I_s.toggle() ; break ;
        
        case NEXT:  C1.INST_done = 1 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}
