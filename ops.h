
uint8_t adc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case 0x01:  A_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  ST_ALU_C_from_C.toggle() ; ACC_e.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case 0x10:  ALU_op = ALU_ADC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_AND ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) { 
            case 0x00:  ACC_e.toggle() ; break ;
            case 0x01:  A_s.toggle() ; B_s.toggle() ; break ;
            case 0x02:  A_s.toggle() ; B_s.toggle() ; break ;
            case 0x03:  ACC_e.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ADD ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x13:  ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (tick) { 
            case 0x00:  ACC_e.toggle() ; break ;
            case 0x01:  A_s.toggle() ; B_s.toggle() ; break ;
            case 0x02:  A_s.toggle() ; B_s.toggle() ; break ;
            case 0x03:  ACC_e.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ADD ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x11:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x13:  EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t tick){
    if (! STATUS.C){ 
        switch (tick) {  
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bcs(uint8_t tick) {
    if (STATUS.C){ 
        switch (tick) { 
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t beq(uint8_t tick){
    if (STATUS.Z){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bit(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_BIT ; 
                    ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_NZ_s.toggle() ; ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t tick){
    if (STATUS.N){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bne(uint8_t tick){
    if (! STATUS.Z){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bpl(uint8_t tick){
    if (! STATUS.N){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t brk(uint8_t tick) {
    switch (tick){
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bvc(uint8_t tick){
    if (! STATUS.V){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bvs(uint8_t tick){
    if (STATUS.V){  
        switch (tick) {
            case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
            case 0x01:  PCh_s.toggle() ; break ;
            case 0x02:  PCh_s.toggle() ; break ;
            case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
            
            case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
            case 0x11:  PCl_s.toggle() ; break ;
            case 0x12:  PCl_s.toggle() ; break ;
            case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t clc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  ALU_op = ALU_PASS ; 
                    ST_C_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_C_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cld(uint8_t tick) {
    switch (tick) {
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cli(uint8_t tick) {
    switch (tick) { 
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t clv(uint8_t tick) {
    switch (tick) { 
        case 0x00:  break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  ALU_op = ALU_PASS ; 
                    ST_V_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; 
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t tick) {
    switch (tick) { 
        case 0x00:  X_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; 
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ; 
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t tick) {
    switch (tick) { 
        case 0x00:  Y_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  Y_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; 
                    ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ST_s.toggle() ; break ;
        case 0x12:  ST_s.toggle() ; break ;
        case 0x13:  ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ALU_op = ALU_DEC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t tick) {
    switch (tick) { 
        case 0x00:  X_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t tick) {
    switch (tick) { 
        case 0x00:  Y_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Y_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_EOR ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_INC ; 
                    EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t tick) {
    switch (tick) {
        case 0x00:  Y_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Y_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case 0x01:  PCh_s.toggle() ; break ;
        case 0x02:  PCh_s.toggle() ; break ;
        case 0x03:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case 0x10:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x11:  PCl_s.toggle() ; break ;
        case 0x12:  PCl_s.toggle() ; break ;
        case 0x13:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t tick) {
    switch (tick) { 
        case 0x00:  PC_e.toggle() ; Ah2D_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  Ah2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case 0x10:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x11:  B_s.toggle() ; break ;
        case 0x12:  B_s.toggle() ; break ;
        case 0x13:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case 0x20:  ALU_op = ALU_DEC ; 
                    ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case 0x21:  PCl_s.toggle() ; ST_s.toggle() ; break ;
        case 0x22:  PCl_s.toggle() ; ST_s.toggle() ; break ;
        case 0x23:  ALU_e.toggle() ; ST_ALU_C_s.toggle() ; break ;
        
        case 0x30:  break ;
        case 0x31:  B_s.toggle() ; break ; 
        case 0x32:  B_s.toggle() ; break ;
        case 0x33:  break ;  

        case 0x40:  ALU_op = ALU_SBC ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case 0x41:  RAM_s.toggle() ; break ;
        case 0x42:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case 0x43:  ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case 0x50:  PC_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x51:  B_s.toggle() ; break ;
        case 0x52:  B_s.toggle() ; break ;
        case 0x53:  Al2D_e.toggle() ; PC_e.toggle() ; break ;
        
        case 0x60:  ALU_op = ALU_PASS ; 
                    SP_e.toggle() ; ALU_e.toggle() ; break ;
        case 0x61:  RAM_s.toggle() ; break ;
        case 0x62:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case 0x63:  ALU_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        case 0x70:  EAh_e.toggle() ; Ah2D_e.toggle() ; break ;
        case 0x71:  PCh_s.toggle() ; break ;
        case 0x72:  PCh_s.toggle() ; break ;
        case 0x73:  Ah2D_e.toggle() ; EAh_e.toggle() ; break ;
        
        case 0x80:  EAl_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x81:  PCl_s.toggle() ; break ;
        case 0x82:  PCl_s.toggle() ; break ;
        case 0x83:  Al2D_e.toggle() ; EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x01:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x01:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x01:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t tick) {
    if ((INST & 0xF) == 0xA) {
        switch (tick) {
            case 0x00:  ALU_op = ALU_LSR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x01:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x02:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x03:  ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  ALU_op = ALU_LSR ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x01:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x02:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x03:  EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
        
            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t nop(uint8_t tick) {
    switch (tick) {
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ora(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  A_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_ORA ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; SP_e.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; SP_e.toggle() ; SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e.toggle() ; ST_e.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; SP_down.toggle() ; break ;
        case 0x03:  SP_e.toggle() ; ST_e.toggle() ; SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t tick) {
    switch (tick) { 
        case 0x00:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; ALU_e.toggle() ; break ;
        case 0x11:  SP_s.toggle() ; break ;
        case 0x12:  SP_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;
        
        case 0x20:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case 0x21:  B_s.toggle() ; break ;
        case 0x22:  B_s.toggle() ; break ;
        case 0x23:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x30:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x31:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x32:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x33:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; ALU_e.toggle() ; break ;
        case 0x11:  SP_s.toggle() ; break ;
        case 0x12:  SP_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;
        
        case 0x20:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case 0x21:  ST_s.toggle() ; break ;
        case 0x22:  ST_s.toggle() ; break ;
        case 0x23:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  ST_ALU_C_from_C.toggle() ; break ;
            case 0x01:  ST_ALU_C_s.toggle() ; ST_s.toggle() ; ST_s.toggle() ; break ;
            case 0x02:  ST_ALU_C_s.toggle() ; break ;
            case 0x03:  ST_ALU_C_from_C.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ROL ; ALU_e.toggle() ; break ;
            case 0x11:  ACC_s.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; ST_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  ACC_s.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x13:  ALU_e.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  ST_ALU_C_from_C.toggle() ; break ;
            case 0x01:  ST_ALU_C_s.toggle() ; ST_s.toggle() ; ST_s.toggle() ; break ;
            case 0x02:  ST_ALU_C_s.toggle() ; break ;
            case 0x03:  ST_ALU_C_from_C.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ROL ; 
                        EAh_e.toggle() ; EAl_e.toggle() ; ALU_e.toggle() ; break ;
            case 0x11:  RAM_s.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; ST_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  RAM_s.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x13:  ALU_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case 0x01:  ST_s.toggle() ; break ;
            case 0x02:  ST_s.toggle() ; break ;
            case 0x03:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
            case 0x13:  ALU_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
            case 0x01:  ST_s.toggle() ; break ;
            case 0x02:  ST_s.toggle() ; break ;
            case 0x03:  ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

            case 0x10:  ALU_op = ALU_ROR ; 
                        ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;
            case 0x11:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x12:  RAM_s.toggle() ; ST_s.toggle() ; break ;
            case 0x13:  ALU_e.toggle() ; EAh_e.toggle() ; EAl_e.toggle() ; ST_C_s.toggle() ; ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t tick) {
    switch (tick) { // 9 cycles
        case 0x00:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x11:  SP_s.toggle() ; break ;
        case 0x12:  SP_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;
        
        case 0x20:  SP_e.toggle() ; RAM_e.toggle() ;  
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case 0x21:  ST_s.toggle() ; break ;
        case 0x22:  ST_s.toggle() ; break ;
        case 0x23:  SP_e.toggle() ; RAM_e.toggle() ; 
                    ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;

        case 0x30:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x31:  B_s.toggle() ; break ;
        case 0x32:  B_s.toggle() ; break ;
        case 0x33:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x40:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x41:  SP_s.toggle() ; break ;
        case 0x42:  SP_s.toggle() ; break ;
        case 0x43:  ALU_e.toggle() ; break ;
        
        case 0x50:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case 0x51:  PCl_s.toggle() ; break ;
        case 0x52:  PCl_s.toggle() ; break ;
        case 0x53:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x60:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x61:  B_s.toggle() ; break ;
        case 0x62:  B_s.toggle() ; break ;
        case 0x63:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x70:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x71:  SP_s.toggle() ; break ;
        case 0x72:  SP_s.toggle() ; break ;
        case 0x73:  ALU_e.toggle() ; break ;
        
        case 0x80:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case 0x81:  PCh_s.toggle() ; break ;
        case 0x82:  PCh_s.toggle() ; break ;
        case 0x83:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x11:  SP_s.toggle() ; break ;
        case 0x12:  SP_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;
        
        case 0x20:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case 0x21:  PCl_s.toggle() ; break ;
        case 0x22:  PCl_s.toggle() ; break ;
        case 0x23:  RAM_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x30:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x31:  B_s.toggle() ; break ;
        case 0x32:  B_s.toggle() ; break ;
        case 0x33:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x40:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x41:  SP_s.toggle() ; break ;
        case 0x42:  SP_s.toggle() ; break ;
        case 0x43:  ALU_e.toggle() ; break ;
        
        case 0x50:  SP_e.toggle() ; RAM_e.toggle() ; break ;
        case 0x51:  PCh_s.toggle() ; break ;
        case 0x52:  PCh_s.toggle() ; PC_up.toggle() ; break ;
        case 0x53:  RAM_e.toggle() ; SP_e.toggle() ; PC_up.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;
        case 0x01:  A_s.toggle() ; ST_s.toggle() ; break ;
        case 0x02:  A_s.toggle() ; ST_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; ST_ALU_C_from_C.toggle() ; ST_ALU_C_s.toggle() ; break ;

        case 0x10:  ALU_op = ALU_SBC ; 
                    ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_C_s.toggle() ; ST_V_s.toggle() ; ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t tick) {
    switch (tick) {
        case 0x00:  break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  ALU_op = ALU_INC ; 
                    ALU_e.toggle() ; break ;
        case 0x11:  B_s.toggle() ; break ;
        case 0x12:  B_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;
        
        case 0x20:  ALU_op = ALU_DEC ; 
                    ST_C_s.toggle() ; break ;
        case 0x21:  ST_s.toggle() ; break ;
        case 0x22:  ST_s.toggle() ; break ;
        case 0x23:  ST_C_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sed(uint8_t tick) {
    switch (tick) {
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sei(uint8_t tick) {
    switch (tick) {
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sta(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e.toggle() ; EAl_e.toggle() ; ACC_e.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e.toggle() ; EAl_e.toggle() ; X_e.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e.toggle() ; EAl_e.toggle() ; Y_e.toggle() ; break ;
        case 0x01:  RAM_s.toggle() ; break ;
        case 0x02:  RAM_s.toggle() ; break ;
        case 0x03:  Y_e.toggle() ; EAl_e.toggle() ; EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  ACC_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  Y_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e.toggle() ; Al2D_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Al2D_e.toggle() ; SP_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  X_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  X_e.toggle() ; break ;

        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; break ;
        case 0x11:  SP_s.toggle() ; break ;
        case 0x12:  SP_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t tick) {
    switch (tick) {
        case 0x00:  Y_e.toggle() ; break ;
        case 0x01:  B_s.toggle() ; break ;
        case 0x02:  B_s.toggle() ; break ;
        case 0x03:  Y_e.toggle() ; break ;
        
        case 0x10:  ALU_op = ALU_PASS ; 
                    ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;
        case 0x11:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x12:  ACC_s.toggle() ; ST_s.toggle() ; break ;
        case 0x13:  ALU_e.toggle() ; ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst(uint8_t tick){
    switch (tick) {
        // Set SP and STATUS to 0
        case 0x00:  break ;
        case 0x01:  SP_s.toggle() ; ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case 0x02:  SP_s.toggle() ; ST_src.toggle() ; ST_NZ_s.toggle() ; ST_V_s.toggle() ; ST_C_s.toggle() ; break ;
        case 0x03:  break ;

        // Set ALU_c to 0 
        case 0x10:  ST_ALU_C_from_C.toggle() ; break ;
        case 0x11:  ST_ALU_C_s.toggle() ; break ;
        case 0x12:  ST_ALU_C_s.toggle() ; break ;
        case 0x13:  ST_ALU_C_from_C.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case 0x20:  SP_down.toggle() ; break ;
        case 0x21:  SP_down.toggle() ; break ;
        case 0x22:  SP_down.toggle() ; break ;
        case 0x23:  SP_down.toggle() ; break ;

        // Decrement SP twice to reach 0xFD
        case 0x30:  SP_down.toggle() ; break ;
        case 0x31:  SP_down.toggle() ; break ;
        case 0x32:  break ;
        case 0x33:  break ;

        default:    return 0 ;
    }
    return 1 ;    
}