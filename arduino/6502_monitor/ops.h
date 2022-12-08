

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
                    ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;

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
        case    0:  STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
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
                    ST_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_C_s.toggle() ; break ;
        
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
        case    0:  STEP_clr = 0 ; break ; 
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
                    ST_V_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_V_s.toggle() ; break ;

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
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ; 

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
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

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
        case    0:  SP_e.toggle() ; ST_e.toggle() ; break ;
        case    1:  RAM_s.toggle() ; break ;
        case    2:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case    3:  SP_e.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
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
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case    9:  ST_s.toggle() ; break ;
        case   10:  ST_s.toggle() ; break ;
        case   11:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;

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
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case    9:  ST_s.toggle() ; break ;
        case   10:  ST_s.toggle() ; break ;
        case   11:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;

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
        case   21:  PCl_s.toggle() ; break ;
        case   22:  PCl_s.toggle() ; break ;
        case   23:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case   24:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case   25:  B_s.toggle() ; break ;
        case   26:  B_s.toggle() ; break ;
        case   27:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case   28:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case   29:  SP_s.toggle() ; break ;
        case   30:  SP_s.toggle() ; break ;
        case   31:  ALU_op = 0 ; 
                    ALU_e.toggle() ; break ;
        
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
                    ST_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ALU_op = 0 ; 
                    ST_C_s.toggle() ; break ;

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
        case    0:  STEP_clr = 0 ; break ;
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
        // Set SP and STATUS to 0
        case    0:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case    1:  ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_s.toggle() ; break ;
        case    2:  ACC_s.toggle() ; X_s.toggle() ; Y_s.toggle() ; A_s.toggle() ; B_s.toggle() ;
                    SP_s.toggle() ; ST_s.toggle() ; break ;
        case    3:  ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;

        // Set ALU_c to 0 
        case    4:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case    5:  ST_s.toggle() ; break ;
        case    6:  ST_s.toggle() ; break ;
        case    7:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case    8:  SP_down.toggle() ; break ;
        case    9:  SP_down.toggle() ; break ;
        case   10:  SP_down.toggle() ; break ;
        case   11:  SP_down.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case   12:  SP_down.toggle() ; break ;
        case   13:  SP_down.toggle() ; break ;

        // TODO (in simulator): Set EA to 0xFFFC/D?
        
        case   14:  STEP_clr = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;    
}
