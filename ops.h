
uint8_t adc(uint8_t step) {
    switch (step) { 
        case    0:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case    4:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t anda(uint8_t step) {
    switch (step) { 
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_AND ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) { 
            case    0:  C1.ACC_e.toggle() ; break ;
            case    1:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case    2:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case    3:  C1.ACC_e.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ADD ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) { 
            case    0:  C1.ACC_e.toggle() ; break ;
            case    1:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case    2:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case    3:  C1.ACC_e.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ADD ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            
            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t step){
    if (! STATUS.C){ 
        switch (step) {  
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;
            
            case    8:  C1.STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bcs(uint8_t step) {
    if (STATUS.C){ 
        switch (step) { 
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;
            
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

            case    8:  C1.STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t beq(uint8_t step){
    if (STATUS.Z){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bit(uint8_t step) {
    switch (step) { 
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_BIT ; 
                    C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t step){
    if (STATUS.N){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bne(uint8_t step){
    if (! STATUS.Z){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bpl(uint8_t step){
    if (! STATUS.N){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t brk(uint8_t step) {
    switch (step){
        case    0:  C1.STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bvc(uint8_t step){
    if (! STATUS.V){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bvs(uint8_t step){
    if (STATUS.V){  
        switch (step) {
            case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case    1:  C4.PCh_s.toggle() ; break ;
            case    2:  C4.PCh_s.toggle() ; break ;
            case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case    5:  C4.PCl_s.toggle() ; break ;
            case    6:  C4.PCl_s.toggle() ; break ;
            case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
            case    8:  C1.STEP_clr = 0 ; break ;
            
            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t clc(uint8_t step) {
    switch (step) { 
        case    0:  break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  break ;

        case    4:  C3.ALU_op = ALU_PASS ; 
                    C5.ST_C_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; break ;
        
        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cld(uint8_t step) {
    switch (step) {
        case    0:  C1.STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cli(uint8_t step) {
    switch (step) {
        case    0:  C1.STEP_clr = 0 ; break ; 
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t clv(uint8_t step) {
    switch (step) { 
        case    0:  break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  break ;

        case    4:  C3.ALU_op = ALU_PASS ; 
                    C5.ST_V_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_V_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t step) {
    switch (step) { 
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t step) {
    switch (step) { 
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ; 

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t step) {
    switch (step) { 
        case    0:  C1.Y_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t step) {
    switch (step) { 
        case    0:  C3.ALU_op = ALU_DEC ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t step) {
    switch (step) { 
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t step) {
    switch (step) { 
        case    0:  C1.Y_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_EOR ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t step) {
    switch (step) {
        case    0:  C3.ALU_op = ALU_INC ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;        

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t step) {
    switch (step) {
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t step) {
    switch (step) {
        case    0:  C1.Y_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t step) {
    switch (step) {
        case    0:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case    1:  C4.PCh_s.toggle() ; break ;
        case    2:  C4.PCh_s.toggle() ; break ;
        case    3:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case    4:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    5:  C4.PCl_s.toggle() ; break ;
        case    6:  C4.PCl_s.toggle() ; break ;
        case    7:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case    8:  C1.STEP_clr = 0 ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t step) {
    switch (step) { 
        case    0:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case    4:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    5:  C3.B_s.toggle() ; break ;
        case    6:  C3.B_s.toggle() ; break ;
        case    7:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case    8:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    9:  C4.PCl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   10:  C4.PCl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   11:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  C3.B_s.toggle() ; break ; 
        case   14:  C3.B_s.toggle() ; break ;
        case   15:  break ;  

        case   16:  C3.ALU_op = ALU_SBC ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ; break ;
        case   17:  C2.RAM_s.toggle() ; break ;
        case   18:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case   19:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case   20:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   21:  C3.B_s.toggle() ; break ;
        case   22:  C3.B_s.toggle() ; break ;
        case   23:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case   24:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ; break ;
        case   25:  C2.RAM_s.toggle() ; break ;
        case   26:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case   27:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case   28:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case   29:  C4.PCh_s.toggle() ; break ;
        case   30:  C4.PCh_s.toggle() ; break ;
        case   31:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case   32:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   33:  C4.PCl_s.toggle() ; break ;
        case   34:  C4.PCl_s.toggle() ; break ;
        case   35:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

        case   36:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t step) {
    switch (step) {
        case    0:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    1:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t step) {
    switch (step) {
        case    0:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    1:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t step) {
    switch (step) {
        case    0:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    1:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t step) {
    if ((INST & 0xF) == 0xA) {
        switch (step) {
            case    0:  C3.ALU_op = ALU_LSR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    1:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    2:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    3:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    4:  C1.STEP_clr = 0 ; break ;            

            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  C3.ALU_op = ALU_LSR ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    1:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    2:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    3:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    4:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nop(uint8_t step) {
    switch (step) {
        case    0:  C1.STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ora(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_ORA ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t step) {
    switch (step) {
        case    0:  C2.SP_e.toggle() ; C5.ST_e.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case    3:  C2.SP_e.toggle() ; C5.ST_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case    4:  C1.STEP_clr = 0 ;        
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t step) {
    switch (step) { 
        case    0:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C2.SP_s.toggle() ; break ;
        case    6:  C2.SP_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case    8:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   12:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case   13:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   14:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   15:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case   16:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t step) {
    switch (step) {
        case    0:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C2.SP_s.toggle() ; break ;
        case    6:  C2.SP_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case    8:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case    9:  C5.ST_s.toggle() ; break ;
        case   10:  C5.ST_s.toggle() ; break ;
        case   11:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;

        case   12:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) {
            case    0:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case    1:  C5.ST_s.toggle() ; break ;
            case    2:  C5.ST_s.toggle() ; break ;
            case    3:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ROL ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;            
            
            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case    1:  C5.ST_s.toggle() ; break ;
            case    2:  C5.ST_s.toggle() ; break ;
            case    3:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ROL ; 
                        C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t step) {
    if ((INST & 0xF) == 0xA){
        switch (step) {
            case    0:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case    1:  C5.ST_s.toggle() ; break ;
            case    2:  C5.ST_s.toggle() ; break ;
            case    3:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (step) {
            case    0:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case    1:  C5.ST_s.toggle() ; break ;
            case    2:  C5.ST_s.toggle() ; break ;
            case    3:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case    4:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case    5:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    6:  C2.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case    7:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            case    8:  C1.STEP_clr = 0 ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t step) {
    switch (step) { // 9 cycles
        case    0:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C2.SP_s.toggle() ; break ;
        case    6:  C2.SP_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case    8:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ;  
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case    9:  C5.ST_s.toggle() ; break ;
        case   10:  C5.ST_s.toggle() ; break ;
        case   11:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;

        case   12:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   13:  C3.B_s.toggle() ; break ;
        case   14:  C3.B_s.toggle() ; break ;
        case   15:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   16:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case   17:  C2.SP_s.toggle() ; break ;
        case   18:  C2.SP_s.toggle() ; break ;
        case   19:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case   20:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   21:  C4.PCl_s.toggle() ; break ;
        case   22:  C4.PCl_s.toggle() ; break ;
        case   23:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   24:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   25:  C3.B_s.toggle() ; break ;
        case   26:  C3.B_s.toggle() ; break ;
        case   27:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   28:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case   29:  C2.SP_s.toggle() ; break ;
        case   30:  C2.SP_s.toggle() ; break ;
        case   31:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case   32:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   33:  C4.PCh_s.toggle() ; break ;
        case   34:  C4.PCh_s.toggle() ; break ;
        case   35:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;

        case   36:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t step) {
    switch (step) {
        case    0:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C2.SP_s.toggle() ; break ;
        case    6:  C2.SP_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case    8:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C4.PCl_s.toggle() ; break ;
        case   10:  C4.PCl_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   12:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   13:  C3.B_s.toggle() ; break ;
        case   14:  C3.B_s.toggle() ; break ;
        case   15:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case   16:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case   17:  C2.SP_s.toggle() ; break ;
        case   18:  C2.SP_s.toggle() ; break ;
        case   19:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case   20:  C2.SP_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   21:  C4.PCh_s.toggle() ; break ;
        case   22:  C4.PCh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   23:  C2.RAM_e.toggle() ; C2.SP_e.toggle() ; C2.PC_up.toggle() ; break ;

        case   24:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case    4:  C3.ALU_op = ALU_SBC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t step) {
    switch (step) {
        // The STATUS word is never 0, at a minimum the constant bits will be on.
        // Decrementing it will always produce a carry.
        case    0:  C5.ST_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C5.ST_e.toggle() ; break ;

        case    4:  C3.ALU_op = ALU_DEC ; 
                    C5.ST_C_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sed(uint8_t step) {
    switch (step) {
        case    0:  C1.STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sei(uint8_t step) {
    switch (step) {
        case    0:  C1.STEP_clr = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sta(uint8_t step) {
    switch (step) {
        case    0:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.ACC_e.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t step) {
    switch (step) {
        case    0:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.X_e.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t step) {
    switch (step) {
        case    0:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C1.Y_e.toggle() ; break ;
        case    1:  C2.RAM_s.toggle() ; break ;
        case    2:  C2.RAM_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case    4:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t step) {
    switch (step) {
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t step) {
    switch (step) {
        case    0:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t step) {
    switch (step) {
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t step) {
    switch (step) {
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;

        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C2.SP_s.toggle() ; break ;
        case    6:  C2.SP_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t step) {
    switch (step) {
        case    0:  C1.Y_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; break ;
        
        case    4:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case    5:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    6:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        case    8:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst(uint8_t step){
    switch (step) {
        // Set SP and STATUS to 0
        case    0:  C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case    1:  C2.SP_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    2:  C2.SP_s.toggle() ; C5.ST_s.toggle() ; break ;
        case    3:  C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;

        // Set ALU_c to 0 
        case    4:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    5:  C5.ST_s.toggle() ; break ;
        case    6:  C5.ST_s.toggle() ; break ;
        case    7:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case    8:  C2.SP_down.toggle() ; break ;
        case    9:  C2.SP_down.toggle() ; break ;
        case   10:  C2.SP_down.toggle() ; break ;
        case   11:  C2.SP_down.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case   12:  C2.SP_down.toggle() ; break ;
        case   13:  C2.SP_down.toggle() ; break ;

        case   14:  C1.STEP_clr = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;    
}