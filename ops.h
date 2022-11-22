
uint8_t adc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.ST_ALU_C_from_C.toggle() ; CU.ACC_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ST_ALU_C_from_C.toggle() ; CU.ACC_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;

        case 0x10:  CU.ALU_op = ALU_ADC ; 
                    CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ;
                    CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_AND ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) { 
            case 0x00:  CU.ACC_e.toggle() ; break ;
            case 0x01:  CU.A_s.toggle() ; CU.B_s.toggle() ; break ;
            case 0x02:  CU.A_s.toggle() ; CU.B_s.toggle() ; break ;
            case 0x03:  CU.ACC_e.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ADD ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (tick) { 
            case 0x00:  CU.ACC_e.toggle() ; break ;
            case 0x01:  CU.A_s.toggle() ; CU.B_s.toggle() ; break ;
            case 0x02:  CU.A_s.toggle() ; CU.B_s.toggle() ; break ;
            case 0x03:  CU.ACC_e.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ADD ; 
                        CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x11:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t tick){
    if (! STATUS.C){ 
        switch (tick) {  
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
        
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bcs(uint8_t tick) {
    if (STATUS.C){ 
        switch (tick) { 
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t beq(uint8_t tick){
    if (STATUS.Z){  
        switch (tick) {
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bit(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_BIT ; 
                    CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t tick){
    if (STATUS.N){  
        switch (tick) {
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bne(uint8_t tick){
    if (! STATUS.Z){  
        switch (tick) {
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bpl(uint8_t tick){
    if (! STATUS.N){  
        switch (tick) {
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

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
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bvs(uint8_t tick){
    if (STATUS.V){  
        switch (tick) {
            case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
            case 0x01:  CU.PCh_s.toggle() ; break ;
            case 0x02:  CU.PCh_s.toggle() ; break ;
            case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
            
            case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
            case 0x11:  CU.PCl_s.toggle() ; break ;
            case 0x12:  CU.PCl_s.toggle() ; break ;
            case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t clc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ST_C_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_C_s.toggle() ; break ;

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
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ST_V_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_CMP ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.X_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_CMP ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ; 
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.Y_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.Y_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_CMP ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.ALU_op = ALU_DEC ; 
                    CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ALU_op = 0 ; 
                    CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.X_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_DEC ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.Y_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Y_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_DEC ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_EOR ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ALU_op = ALU_INC ; 
                    CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ALU_op = 0 ; 
                    CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.X_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.Y_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Y_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x01:  CU.PCh_s.toggle() ; break ;
        case 0x02:  CU.PCh_s.toggle() ; break ;
        case 0x03:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
        
        case 0x10:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x11:  CU.PCl_s.toggle() ; break ;
        case 0x12:  CU.PCl_s.toggle() ; break ;
        case 0x13:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.PC_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.Ah2D_e.toggle() ; CU.PC_e.toggle() ; break ;
        
        case 0x10:  CU.PC_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x11:  CU.B_s.toggle() ; break ;
        case 0x12:  CU.B_s.toggle() ; break ;
        case 0x13:  CU.Al2D_e.toggle() ; CU.PC_e.toggle() ; break ;
        
        case 0x20:  CU.ALU_op = ALU_DEC ; 
                    CU.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x21:  CU.PCl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x22:  CU.PCl_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x23:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        
        case 0x30:  break ;
        case 0x31:  CU.B_s.toggle() ; break ; 
        case 0x32:  CU.B_s.toggle() ; break ;
        case 0x33:  break ;  

        case 0x40:  CU.ALU_op = ALU_SBC ; 
                    CU.SP_e.toggle() ; CU.ALU_e.toggle() ; break ;
        case 0x41:  CU.RAM_s.toggle() ; break ;
        case 0x42:  CU.RAM_s.toggle() ; CU.SP_down.toggle() ; break ;
        case 0x43:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.SP_e.toggle() ; CU.SP_down.toggle() ; break ;
        
        case 0x50:  CU.PC_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x51:  CU.B_s.toggle() ; break ;
        case 0x52:  CU.B_s.toggle() ; break ;
        case 0x53:  CU.Al2D_e.toggle() ; CU.PC_e.toggle() ; break ;
        
        case 0x60:  CU.ALU_op = ALU_PASS ; 
                    CU.SP_e.toggle() ; CU.ALU_e.toggle() ; break ;
        case 0x61:  CU.RAM_s.toggle() ; break ;
        case 0x62:  CU.RAM_s.toggle() ; CU.SP_down.toggle() ; break ;
        case 0x63:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.SP_e.toggle() ; CU.SP_down.toggle() ; break ;
        
        case 0x70:  CU.EAh_e.toggle() ; CU.Ah2D_e.toggle() ; break ;
        case 0x71:  CU.PCh_s.toggle() ; break ;
        case 0x72:  CU.PCh_s.toggle() ; break ;
        case 0x73:  CU.Ah2D_e.toggle() ; CU.EAh_e.toggle() ; break ;
        
        case 0x80:  CU.EAl_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x81:  CU.PCl_s.toggle() ; break ;
        case 0x82:  CU.PCl_s.toggle() ; break ;
        case 0x83:  CU.Al2D_e.toggle() ; CU.EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x01:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x01:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x01:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t tick) {
    if ((INST & 0xF) == 0xA) {
        switch (tick) {
            case 0x00:  CU.ALU_op = ALU_LSR ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x01:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x02:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x03:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  CU.ALU_op = ALU_LSR ; 
                        CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x01:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x02:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x03:  CU.ALU_op = 0 ; 
                        CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
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
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_ORA ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ACC_e.toggle() ; CU.SP_e.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; CU.SP_down.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; CU.SP_e.toggle() ; CU.SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.SP_e.toggle() ; CU.ST_e.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; CU.SP_down.toggle() ; break ;
        case 0x03:  CU.SP_e.toggle() ; CU.ST_e.toggle() ; CU.SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t tick) {
    switch (tick) { 
        case 0x00:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.SP_s.toggle() ; break ;
        case 0x12:  CU.SP_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x20:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  CU.B_s.toggle() ; break ;
        case 0x22:  CU.B_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x30:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x31:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x32:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x33:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.SP_s.toggle() ; break ;
        case 0x12:  CU.SP_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x20:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; 
                    CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;
        case 0x21:  CU.ST_s.toggle() ; break ;
        case 0x22:  CU.ST_s.toggle() ; break ;
        case 0x23:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; 
                    CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  CU.ST_ALU_C_from_C.toggle() ; break ;
            case 0x01:  CU.ST_ALU_C_s.toggle() ; CU.ST_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x02:  CU.ST_ALU_C_s.toggle() ; break ;
            case 0x03:  CU.ST_ALU_C_from_C.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ROL ; 
                        CU.ALU_e.toggle() ; break ;
            case 0x11:  CU.ACC_s.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.ACC_s.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  CU.ST_ALU_C_from_C.toggle() ; break ;
            case 0x01:  CU.ST_ALU_C_s.toggle() ; CU.ST_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x02:  CU.ST_ALU_C_s.toggle() ; break ;
            case 0x03:  CU.ST_ALU_C_from_C.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ROL ; 
                        CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ALU_e.toggle() ; break ;
            case 0x11:  CU.RAM_s.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.RAM_s.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  CU.ST_s.toggle() ; break ;
            case 0x02:  CU.ST_s.toggle() ; break ;
            case 0x03:  CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ROR ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  CU.ST_s.toggle() ; break ;
            case 0x02:  CU.ST_s.toggle() ; break ;
            case 0x03:  CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  CU.ALU_op = ALU_ROR ; 
                        CU.ALU_e.toggle() ; CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
            case 0x11:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x12:  CU.RAM_s.toggle() ; CU.ST_s.toggle() ; break ;
            case 0x13:  CU.ALU_op = 0 ; 
                        CU.ALU_e.toggle() ; CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t tick) {
    switch (tick) { // 9 cycles
        case 0x00:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.SP_s.toggle() ; break ;
        case 0x12:  CU.SP_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x20:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ;  
                    CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;
        case 0x21:  CU.ST_s.toggle() ; break ;
        case 0x22:  CU.ST_s.toggle() ; break ;
        case 0x23:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; 
                    CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;

        case 0x30:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x31:  CU.B_s.toggle() ; break ;
        case 0x32:  CU.B_s.toggle() ; break ;
        case 0x33:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x40:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x41:  CU.SP_s.toggle() ; break ;
        case 0x42:  CU.SP_s.toggle() ; break ;
        case 0x43:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x50:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x51:  CU.PCl_s.toggle() ; break ;
        case 0x52:  CU.PCl_s.toggle() ; break ;
        case 0x53:  CU.RAM_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x60:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x61:  CU.B_s.toggle() ; break ;
        case 0x62:  CU.B_s.toggle() ; break ;
        case 0x63:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x70:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x71:  CU.SP_s.toggle() ; break ;
        case 0x72:  CU.SP_s.toggle() ; break ;
        case 0x73:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x80:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x81:  CU.PCh_s.toggle() ; break ;
        case 0x82:  CU.PCh_s.toggle() ; break ;
        case 0x83:  CU.RAM_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.SP_s.toggle() ; break ;
        case 0x12:  CU.SP_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x20:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x21:  CU.PCl_s.toggle() ; break ;
        case 0x22:  CU.PCl_s.toggle() ; break ;
        case 0x23:  CU.RAM_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x30:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x31:  CU.B_s.toggle() ; break ;
        case 0x32:  CU.B_s.toggle() ; break ;
        case 0x33:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x40:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x41:  CU.SP_s.toggle() ; break ;
        case 0x42:  CU.SP_s.toggle() ; break ;
        case 0x43:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x50:  CU.SP_e.toggle() ; CU.RAM_e.toggle() ; break ;
        case 0x51:  CU.PCh_s.toggle() ; break ;
        case 0x52:  CU.PCh_s.toggle() ; CU.PC_up.toggle() ; break ;
        case 0x53:  CU.RAM_e.toggle() ; CU.SP_e.toggle() ; CU.PC_up.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ACC_e.toggle() ; CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;
        case 0x01:  CU.A_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x02:  CU.A_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; CU.ST_ALU_C_from_C.toggle() ; CU.ST_ALU_C_s.toggle() ; break ;

        case 0x10:  CU.ALU_op = ALU_SBC ; 
                    CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_C_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t tick) {
    switch (tick) {
        case 0x00:  break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  CU.ALU_op = ALU_INC ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.B_s.toggle() ; break ;
        case 0x12:  CU.B_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;
        
        case 0x20:  CU.ALU_op = ALU_DEC ; 
                    CU.ST_C_s.toggle() ; break ;
        case 0x21:  CU.ST_s.toggle() ; break ;
        case 0x22:  CU.ST_s.toggle() ; break ;
        case 0x23:  CU.ALU_op = 0 ; 
                    CU.ST_C_s.toggle() ; break ;
        
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
        case 0x00:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.X_e.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.EAh_e.toggle() ; CU.EAl_e.toggle() ; CU.Y_e.toggle() ; break ;
        case 0x01:  CU.RAM_s.toggle() ; break ;
        case 0x02:  CU.RAM_s.toggle() ; break ;
        case 0x03:  CU.Y_e.toggle() ; CU.EAl_e.toggle() ; CU.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.ACC_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.ACC_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.Y_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.SP_e.toggle() ; CU.Al2D_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Al2D_e.toggle() ; CU.SP_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.X_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.X_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.X_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.X_e.toggle() ; break ;

        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; break ;
        case 0x11:  CU.SP_s.toggle() ; break ;
        case 0x12:  CU.SP_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t tick) {
    switch (tick) {
        case 0x00:  CU.Y_e.toggle() ; break ;
        case 0x01:  CU.B_s.toggle() ; break ;
        case 0x02:  CU.B_s.toggle() ; break ;
        case 0x03:  CU.Y_e.toggle() ; break ;
        
        case 0x10:  CU.ALU_op = ALU_PASS ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;
        case 0x11:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x12:  CU.ACC_s.toggle() ; CU.ST_s.toggle() ; break ;
        case 0x13:  CU.ALU_op = 0 ; 
                    CU.ALU_e.toggle() ; CU.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst(uint8_t tick){
    switch (tick) {
        // Set SP and STATUS to 0
        case 0x00:  break ;
        case 0x01:  CU.SP_s.toggle() ; CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;
        case 0x02:  CU.SP_s.toggle() ; CU.ST_src.toggle() ; CU.ST_NZ_s.toggle() ; CU.ST_V_s.toggle() ; CU.ST_C_s.toggle() ; break ;
        case 0x03:  break ;

        // Set ALU_c to 0 
        case 0x10:  CU.ST_ALU_C_from_C.toggle() ; break ;
        case 0x11:  CU.ST_ALU_C_s.toggle() ; break ;
        case 0x12:  CU.ST_ALU_C_s.toggle() ; break ;
        case 0x13:  CU.ST_ALU_C_from_C.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case 0x20:  CU.SP_down.toggle() ; break ;
        case 0x21:  CU.SP_down.toggle() ; break ;
        case 0x22:  CU.SP_down.toggle() ; break ;
        case 0x23:  CU.SP_down.toggle() ; break ;

        // Decrement SP twice to reach 0xFD
        case 0x30:  CU.SP_down.toggle() ; break ;
        case 0x31:  CU.SP_down.toggle() ; break ;
        case 0x32:  break ;
        case 0x33:  break ;

        default:    return 0 ;
    }
    return 1 ;    
}