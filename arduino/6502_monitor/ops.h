
uint8_t adc(uint8_t step) {
    switch (step) { 
        case    0:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    1:  A_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  A_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case    4:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ;
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t step) {
    switch (step) { 
        case    0:  ACC_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_AND ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) { 
            case    0:  ACC_e.toggle() ; break ;
            case    1:  A_s.toggle() ; B_s.toggle() ; break ;
            case    2:  A_s.toggle() ; B_s.toggle() ; break ;
            case    3:  ACC_e.toggle() ; break ;

            case    4:  ALU_op = ALU_ADD ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  ACC_e.toggle() ; break ;
            case    1:  A_s.toggle() ; B_s.toggle() ; break ;
            case    2:  A_s.toggle() ; B_s.toggle() ; break ;
            case    3:  ACC_e.toggle() ; break ;

            case    4:  ALU_op = ALU_ADD ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            
            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t step){
    if (! STATUS.C){ 
        switch (step) {  
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
            
            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcs(uint8_t step) {
    if (STATUS.C){ 
        switch (step) { 
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t beq(uint8_t step){
    if (STATUS.Z){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bit_(uint8_t step) {
    switch (step) { 
        case    0:  ACC_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_BIT ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t step){
    if (STATUS.N){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bne(uint8_t step){
    if (! STATUS.Z){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bpl(uint8_t step){
    if (! STATUS.N){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t brk(uint8_t step) {
    switch (step){
        // Inc PC
        case    0:  PC_up.toggle() ; break ;
        case    1:  PC_up.toggle() ; break ; 
        // PCh to B
        case    2:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case    3:  B_s.toggle() ; break ;
        case    4:  B_s.toggle() ; break ;
        case    5:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case    6:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case    7:  RAM_s.toggle() ; break ;
        case    8:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case    9:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // PCl to B
        case   10:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case   11:  B_s.toggle() ; break ;
        case   12:  B_s.toggle() ; break ;
        case   13:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case   14:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case   15:  RAM_s.toggle() ; break ;
        case   16:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   17:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // Push Status (w/BREAK, via ST_bi)
        case   18:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; break ;
        case   19:  RAM_s.toggle() ; break ;
        case   20:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   21:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
        case   22:  B_s.toggle() ; break ;
        case   23:  B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh and EAl
        case   24:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; break ;
        case   25:  EAl_s.toggle() ; EAh_s.toggle() ; break ;
        case   26:  EAl_s.toggle() ; EAh_s.toggle() ; break ;
        case   27:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case   28:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ; break ;
        case   29:  PCh_s.toggle() ; break ;
        case   30:  PCh_s.toggle() ; break ;
        case   31:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;
        // EAl to B
        case   32:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case   33:  B_s.toggle() ; break ;
        case   34:  B_s.toggle() ; break ;
        case   35:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE) to EAl
        case   36:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; break ;
        case   37:  EAl_s.toggle() ; break ;
        case   38:  EAl_s.toggle() ; break ;
        case   39:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case   40:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ; break ;
        case   41:  PCl_s.toggle() ; break ;
        case   42:  PCl_s.toggle() ; break ;
        case   43:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; break ;
        // Set Interrupt flag
        case   44:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case   45:  ST_s.toggle() ; break ;
        case   46:  ST_s.toggle() ; break ;
        case   47:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case   48:  STEP_clr = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t _interrupt(uint8_t step){
    switch (step){
        // PCh to B
        case    0:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case    4:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case    5:  RAM_s.toggle() ; break ;
        case    6:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // PCl to B
        case    8:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        // B to RAM[SP--]
        case   12:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case   13:  RAM_s.toggle() ; break ;
        case   14:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   15:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        // Push Status
        case   16:  SP_e.toggle() ; ST_e.toggle() ; break ;
        case   17:  RAM_s.toggle() ; break ;
        case   18:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   19:  SP_e.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        // pc = (uint16_t)read6502(0xFFFE) | ((uint16_t)read6502(0xFFFF) << 8);
        // Clear B
        case   20:  B_s.toggle() ; break ;
        case   21:  B_s.toggle() ; break ;
        // DEC B (giving 0xFF) to EAh, 0xFF/0xFB already in EAl
        case   22:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; break ;
        case   23:  EAh_s.toggle() ; break ;
        case   24:  EAh_s.toggle() ; break ;
        case   25:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCh
        case   26:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ; break ;
        case   27:  PCh_s.toggle() ; break ;
        case   28:  PCh_s.toggle() ; break ;
        case   29:  RAM_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;
        // EAl to B
        case   30:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case   31:  B_s.toggle() ; break ;
        case   32:  B_s.toggle() ; break ;
        case   33:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        // DEC B (giving 0xFE/0xFA) to EAl
        case   34:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; break ;
        case   35:  EAl_s.toggle() ; break ;
        case   36:  EAl_s.toggle() ; break ;
        case   37:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[EA] to PCl
        case   38:  EAl_e.toggle() ; EAh_e.toggle() ; RAM_e.toggle() ; break ;
        case   39:  PCl_s.toggle() ; break ;
        case   40:  PCl_s.toggle() ; break ;
        case   41:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; break ;
        // Set Interrupt flag
        case   42:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case   43:  ST_s.toggle() ; break ;
        case   44:  ST_s.toggle() ; break ;
        case   45:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case   46:  STEP_clr = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t irq(uint8_t step) {
    // TODO: Ideally we do not get here if STATUS.I is set. We need to handle this in the controller logic.
    // We may not have enough input signals left though...
    if (! STATUS.I){
        return _interrupt(step) ;
    }
    else {
        switch (step) { 
            case    0:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nmi(uint8_t step) {
    return _interrupt(step) ;
}


uint8_t bvc(uint8_t step){
    if (! STATUS.V){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bvs(uint8_t step){
    if (STATUS.V){  
        switch (step) {
            case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case    1:  PCh_s.toggle() ; break ;
            case    2:  PCh_s.toggle() ; break ;
            case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case    5:  PCl_s.toggle() ; break ;
            case    6:  PCl_s.toggle() ; break ;
            case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        
            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  break ;
            case    1:  break ;
            case    2:  break ;
            case    3:  break ;
            
            case    4:  break ;
            case    5:  break ;
            case    6:  break ;
            case    7:  break ;

            case    8:  STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t clc(uint8_t step) {
    switch (step) { 
        case    0:  break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  break ;

        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;
        
        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cld(uint8_t step) {
    switch (step) {
        case    0:  STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cli_(uint8_t step) {
    switch (step) {
        case    0:  ST_I_s.toggle() ; break ;
        case    1:  ST_s.toggle() ; break ;
        case    2:  ST_s.toggle() ; break ;
        case    3:  ST_I_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t clv(uint8_t step) {
    switch (step) { 
        case    0:  break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  break ;

        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_V_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_V_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t step) {
    switch (step) { 
        case    0:  ACC_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t step) {
    switch (step) { 
        case    0:  X_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ; 

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t step) {
    switch (step) { 
        case    0:  Y_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_CMP ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t step) {
    switch (step) { 
        case    0:  ALU_op = ALU_DEC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    1:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ALU_op = 0 ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t step) {
    switch (step) { 
        case    0:  X_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t step) {
    switch (step) { 
        case    0:  Y_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_EOR ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t step) {
    switch (step) {
        case    0:  ALU_op = ALU_INC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    1:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ALU_op = 0 ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;        

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t step) {
    switch (step) {
        case    0:  X_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t step) {
    switch (step) {
        case    0:  Y_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t step) {
    switch (step) {
        case    0:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case    1:  PCh_s.toggle() ; break ;
        case    2:  PCh_s.toggle() ; break ;
        case    3:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case    5:  PCl_s.toggle() ; break ;
        case    6:  PCl_s.toggle() ; break ;
        case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        
        case    8:  STEP_clr = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t step) {
    switch (step) { 
        case    0:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case    4:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  B_s.toggle() ; break ;
        case    7:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case    8:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    9:  PCl_s.toggle() ; ST_s.toggle() ; break ;
        case   10:  PCl_s.toggle() ; ST_s.toggle() ; break ;
        case   11:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  B_s.toggle() ; break ; 
        case   14:  B_s.toggle() ; break ;
        case   15:  break ;  

        case   16:  ALU_op = ALU_SBC ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case   17:  RAM_s.toggle() ; break ;
        case   18:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   19:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case   20:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case   21:  B_s.toggle() ; break ;
        case   22:  B_s.toggle() ; break ;
        case   23:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case   24:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case   25:  RAM_s.toggle() ; break ;
        case   26:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case   27:  ALU_op = 0 ; 
                    ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case   28:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case   29:  PCh_s.toggle() ; break ;
        case   30:  PCh_s.toggle() ; break ;
        case   31:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case   32:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case   33:  PCl_s.toggle() ; break ;
        case   34:  PCl_s.toggle() ; break ;
        case   35:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

        case   36:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t step) {
    switch (step) {
        case    0:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    1:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t step) {
    switch (step) {
        case    0:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    1:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t step) {
    switch (step) {
        case    0:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    1:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t step) {
    if ((INST & 0xF) == 0xA) {
        switch (step) {
            case    0:  ALU_op = ALU_LSR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    1:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    2:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    3:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    4:  STEP_clr = 0 ; break ;            

            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  ALU_op = ALU_LSR ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    1:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    2:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    3:  ALU_op = 0 ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    4:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nop(uint8_t step) {
    switch (step) {
        case    0:  STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ora(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; break ;
        case    1:  A_s.toggle() ; break ;
        case    2:  A_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_ORA ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; SP_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case    3:  ACC_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t step) {
    switch (step) {
        case    0:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case    3:  SP_e.toggle() ; ST_bi.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        case    4:  STEP_clr = 0 ; break ;       
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t step) {
    switch (step) { 
        case    0:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case    5:  SP_s.toggle() ; break ;
        case    6:  SP_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case    8:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  B_s.toggle() ; break ;
        case   10:  B_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case   12:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case   13:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case   14:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case   15:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case   16:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t step) {
    switch (step) {
        case    0:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case    5:  SP_s.toggle() ; break ;
        case    6:  SP_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case    8:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        case    9:  ST_s.toggle() ; break ;
        case   10:  ST_s.toggle() ; break ;
        case   11:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;

        case   12:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) {
            case    0:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case    1:  ST_s.toggle() ; break ;
            case    2:  ST_s.toggle() ; break ;
            case    3:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case    4:  ALU_op = ALU_ROL ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;            
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case    1:  ST_s.toggle() ; break ;
            case    2:  ST_s.toggle() ; break ;
            case    3:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case    4:  ALU_op = ALU_ROL ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        ALU_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) {
            case    0:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case    1:  ST_s.toggle() ; break ;
            case    2:  ST_s.toggle() ; break ;
            case    3:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case    4:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case    1:  ST_s.toggle() ; break ;
            case    2:  ST_s.toggle() ; break ;
            case    3:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case    4:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case    5:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    6:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case    7:  ALU_op = 0 ; 
                        ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            case    8:  STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t step) {
    switch (step) { // 9 cycles
        // SP to B
        case    0:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case    5:  SP_s.toggle() ; break ;
        case    6:  SP_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to STATUS
        case    8:  SP_e.toggle() ; RAM_e.toggle() ;  
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        case    9:  ST_s.toggle() ; break ;
        case   10:  ST_s.toggle() ; break ;
        case   11:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        // SP to B
        case   12:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   13:  B_s.toggle() ; break ;
        case   14:  B_s.toggle() ; break ;
        case   15:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case   16:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   17:  SP_s.toggle() ; break ;
        case   18:  SP_s.toggle() ; break ;
        case   19:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to PCl
        case   20:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case   21:  PCl_s.toggle() ; break ;
        case   22:  PCl_s.toggle() ; break ;
        case   23:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        // SP to B
        case   24:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   25:  B_s.toggle() ; break ;
        case   26:  B_s.toggle() ; break ;
        case   27:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        // INC B to SP
        case   28:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   29:  SP_s.toggle() ; break ;
        case   30:  SP_s.toggle() ; break ;
        case   31:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        // RAM[SP] to PCh
        case   32:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case   33:  PCh_s.toggle() ; break ;
        case   34:  PCh_s.toggle() ; break ;
        case   35:  RAM_e.toggle() ; SP_e.toggle() ; break ;

        case   36:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t step) {
    switch (step) {
        case    0:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case    5:  SP_s.toggle() ; break ;
        case    6:  SP_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case    8:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case    9:  PCl_s.toggle() ; break ;
        case   10:  PCl_s.toggle() ; break ;
        case   11:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case   12:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   13:  B_s.toggle() ; break ;
        case   14:  B_s.toggle() ; break ;
        case   15:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case   16:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   17:  SP_s.toggle() ; break ;
        case   18:  SP_s.toggle() ; break ;
        case   19:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
        case   20:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case   21:  PCh_s.toggle() ; break ;
        case   22:  PCh_s.toggle() ; PC_up.toggle() ; break ;
        case   23:  RAM_e.toggle() ; SP_e.toggle() ; PC_up.toggle() ; break ;

        case   24:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    1:  A_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  A_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case    4:  ALU_op = ALU_SBC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t step) {
    switch (step) {
        // The STATUS word is never 0, at a minimum the constant bits will be on.
        // Decrementing it will always produce a carry.
        case    0:  ST_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  ST_e.toggle() ; break ;

        case    4:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sed(uint8_t step) {
    switch (step) {
        case    0:  STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sei_(uint8_t step) {
    switch (step) {
        case    0:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case    1:  ST_s.toggle() ; break ;
        case    2:  ST_s.toggle() ; break ;
        case    3:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ; 

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sta(uint8_t step) {
    switch (step) {
        case    0:  EAh_e.toggle() ; EAl_e.toggle() ; ACC_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t step) {
    switch (step) {
        case    0:  EAh_e.toggle() ; EAl_e.toggle() ; X_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; break ;
        case    3:  X_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t step) {
    switch (step) {
        case    0:  EAh_e.toggle() ; EAl_e.toggle() ; Y_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        case    4:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t step) {
    switch (step) {
        case    0:  ACC_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  ACC_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t step) {
    switch (step) {
        case    0:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  X_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t step) {
    switch (step) {
        case    0:  X_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t step) {
    switch (step) {
        case    0:  X_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  X_e.toggle() ; break ;

        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case    5:  SP_s.toggle() ; break ;
        case    6:  SP_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t step) {
    switch (step) {
        case    0:  Y_e.toggle() ; break ;
        case    1:  B_s.toggle() ; break ;
        case    2:  B_s.toggle() ; break ;
        case    3:  Y_e.toggle() ; break ;
        
        case    4:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    6:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        case    8:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst1(uint8_t step){
    switch (step) {
        // Set registers, SP and STATUS to 0
        case    0:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        case    1:  ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; ST_I_s.toggle() ; break ;
        // Set ALU_c to 0 
        case    4:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        // Decrement SP once to reach 0xFF
        case    8:  SP_down.toggle() ; break ;
        case    9:  SP_down.toggle() ; break ;
        // While SP == 0xFF, copy it to EAh in prep for reset vector
        case   10:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   11:  EAh_s.toggle() ;  break ;
        case   12:  EAh_s.toggle() ;  break ;
        case   13:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        // Decrement SP twice again to reach 0xFD
        case   14:  SP_down.toggle() ; break ;
        case   15:  SP_down.toggle() ; break ;
        case   16:  SP_down.toggle() ; break ;
        case   17:  SP_down.toggle() ; break ;
        // Copy SP to EAl, EA now 0xFFFD
        case   18:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   19:  EAl_s.toggle() ;  break ;
        case   20:  EAl_s.toggle() ;  break ;
        case   21:  SP_e.toggle() ; Al2D_e.toggle() ; break ;

        case   22:  STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;    
}


uint8_t rst2(uint8_t step){
    switch (step) {
        // RAM[EA] to PCh
        case    0:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case    1:  PCh_s.toggle() ; break ;
        case    2:  PCh_s.toggle() ; break ;
        case    3:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; break ;
        // Send EAl to B
        case    4:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case    5:  B_s.toggle() ; break ;
        case    6:  B_s.toggle() ; break ;
        case    7:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        // Decrement to EAl (will be 0xFC)
        case    8:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; break ;
        case    9:  EAl_s.toggle() ; break ;
        case   10:  EAl_s.toggle() ; break ;
        case   11:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ; 
        // RAM[EA] to PCl
        case   12:  EAh_e.toggle() ; EAl_e.toggle() ; RAM_e.toggle() ; break ;
        case   13:  PCl_s.toggle() ; break ;
        case   14:  PCl_s.toggle() ; break ;
        case   15:  RAM_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ;  break ;
        // Disable interrupts by setting the interrupt flag
        case   16:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        case   17:  ST_s.toggle() ; break ;
        case   18:  ST_s.toggle() ; break ;
        case   19:  ST_bi.toggle() ; ST_I_s.toggle() ; break ;
        
        case   20:  STEP_clr = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}
