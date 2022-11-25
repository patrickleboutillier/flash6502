
uint8_t adc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C5.ST_ALU_C_from_C.toggle() ; C1.ACC_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case 0x10:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}

uint8_t anda(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_AND ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) { 
            case 0x00:  C1.ACC_e.toggle() ; break ;
            case 0x01:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case 0x02:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case 0x03:  C1.ACC_e.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ADD ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    else {
        switch (tick) { 
            case 0x00:  C1.ACC_e.toggle() ; break ;
            case 0x01:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case 0x02:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
            case 0x03:  C1.ACC_e.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ADD ; 
                        C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t bcc(uint8_t tick){
    if (! STATUS.C){ 
        switch (tick) {  
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bcs(uint8_t tick) {
    if (STATUS.C){ 
        switch (tick) { 
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t beq(uint8_t tick){
    if (STATUS.Z){  
        switch (tick) {
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bit(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_BIT ; 
                    C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t tick){
    if (STATUS.N){  
        switch (tick) {
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bne(uint8_t tick){
    if (! STATUS.Z){  
        switch (tick) {
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bpl(uint8_t tick){
    if (! STATUS.N){  
        switch (tick) {
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

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
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bvs(uint8_t tick){
    if (STATUS.V){  
        switch (tick) {
            case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
            case 0x01:  C4.PCh_s.toggle() ; break ;
            case 0x02:  C4.PCh_s.toggle() ; break ;
            case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
            
            case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
            case 0x11:  C2.PCl_s.toggle() ; break ;
            case 0x12:  C2.PCl_s.toggle() ; break ;
            case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t clc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C5.ST_C_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; break ;

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
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  break ;

        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C5.ST_V_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_V_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ; 
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.Y_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_CMP ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C3.ALU_op = ALU_DEC ; 
                    C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C1.Y_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_EOR ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t tick) {
    switch (tick) {
        case 0x00:  C3.ALU_op = ALU_INC ; 
                    C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C3.ALU_op = 0 ; 
                    C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.Y_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t tick) {
    switch (tick) {
        case 0x00:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case 0x01:  C4.PCh_s.toggle() ; break ;
        case 0x02:  C4.PCh_s.toggle() ; break ;
        case 0x03:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case 0x10:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x11:  C2.PCl_s.toggle() ; break ;
        case 0x12:  C2.PCl_s.toggle() ; break ;
        case 0x13:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case 0x10:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x11:  C3.B_s.toggle() ; break ;
        case 0x12:  C3.B_s.toggle() ; break ;
        case 0x13:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case 0x20:  C3.ALU_op = ALU_DEC ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case 0x21:  C2.PCl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x22:  C2.PCl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x23:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case 0x30:  break ;
        case 0x31:  C3.B_s.toggle() ; break ; 
        case 0x32:  C3.B_s.toggle() ; break ;
        case 0x33:  break ;  

        case 0x40:  C3.ALU_op = ALU_SBC ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ; break ;
        case 0x41:  C4.RAM_s.toggle() ; break ;
        case 0x42:  C4.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case 0x43:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case 0x50:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x51:  C3.B_s.toggle() ; break ;
        case 0x52:  C3.B_s.toggle() ; break ;
        case 0x53:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
        
        case 0x60:  C3.ALU_op = ALU_PASS ; 
                    C2.SP_e.toggle() ; C3.ALU_e.toggle() ; break ;
        case 0x61:  C4.RAM_s.toggle() ; break ;
        case 0x62:  C4.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case 0x63:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        case 0x70:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case 0x71:  C4.PCh_s.toggle() ; break ;
        case 0x72:  C4.PCh_s.toggle() ; break ;
        case 0x73:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case 0x80:  C2.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x81:  C2.PCl_s.toggle() ; break ;
        case 0x82:  C2.PCl_s.toggle() ; break ;
        case 0x83:  C4.Al2D_e.toggle() ; C2.EAl_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t tick) {
    switch (tick) {
        case 0x00:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x01:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t tick) {
    switch (tick) {
        case 0x00:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x01:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t tick) {
    switch (tick) {
        case 0x00:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x01:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lsr(uint8_t tick) {
    if ((INST & 0xF) == 0xA) {
        switch (tick) {
            case 0x00:  C3.ALU_op = ALU_LSR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x01:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x02:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x03:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  C3.ALU_op = ALU_LSR ; 
                        C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x01:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x02:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x03:  C3.ALU_op = 0 ; 
                        C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
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
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_ORA ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t pha(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; C2.SP_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t php(uint8_t tick) {
    switch (tick) {
        case 0x00:  C2.SP_e.toggle() ; C5.ST_e.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; C2.SP_down.toggle() ; break ;
        case 0x03:  C2.SP_e.toggle() ; C5.ST_e.toggle() ; C2.SP_down.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t tick) {
    switch (tick) { 
        case 0x00:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C2.SP_s.toggle() ; break ;
        case 0x12:  C2.SP_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x20:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; break ;
        case 0x21:  C3.B_s.toggle() ; break ;
        case 0x22:  C3.B_s.toggle() ; break ;
        case 0x23:  C4.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x30:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x31:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x32:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x33:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t plp(uint8_t tick) {
    switch (tick) {
        case 0x00:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C2.SP_s.toggle() ; break ;
        case 0x12:  C2.SP_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x20:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case 0x21:  C5.ST_s.toggle() ; break ;
        case 0x22:  C5.ST_s.toggle() ; break ;
        case 0x23:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rol(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  C5.ST_s.toggle() ; break ;
            case 0x02:  C5.ST_s.toggle() ; break ;
            case 0x03:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ROL ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  C5.ST_s.toggle() ; break ;
            case 0x02:  C5.ST_s.toggle() ; break ;
            case 0x03:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ROL ; 
                        C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C2.EAl_e.toggle() ; C4.EAh_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t ror(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        switch (tick) {
            case 0x00:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  C5.ST_s.toggle() ; break ;
            case 0x02:  C5.ST_s.toggle() ; break ;
            case 0x03:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            
            default:    return 0 ;
        }
    }
    else {
        switch (tick) {
            case 0x00:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
            case 0x01:  C5.ST_s.toggle() ; break ;
            case 0x02:  C5.ST_s.toggle() ; break ;
            case 0x03:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

            case 0x10:  C3.ALU_op = ALU_ROR ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
            case 0x11:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x12:  C4.RAM_s.toggle() ; C5.ST_s.toggle() ; break ;
            case 0x13:  C3.ALU_op = 0 ; 
                        C3.ALU_e.toggle() ; C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;

            default:    return 0 ;
        }
    }
    return 1 ;
}


uint8_t rti(uint8_t tick) {
    switch (tick) { // 9 cycles
        case 0x00:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C2.SP_s.toggle() ; break ;
        case 0x12:  C2.SP_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x20:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ;  
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case 0x21:  C5.ST_s.toggle() ; break ;
        case 0x22:  C5.ST_s.toggle() ; break ;
        case 0x23:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; 
                    C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;

        case 0x30:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x31:  C3.B_s.toggle() ; break ;
        case 0x32:  C3.B_s.toggle() ; break ;
        case 0x33:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x40:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x41:  C2.SP_s.toggle() ; break ;
        case 0x42:  C2.SP_s.toggle() ; break ;
        case 0x43:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x50:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; break ;
        case 0x51:  C2.PCl_s.toggle() ; break ;
        case 0x52:  C2.PCl_s.toggle() ; break ;
        case 0x53:  C4.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x60:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x61:  C3.B_s.toggle() ; break ;
        case 0x62:  C3.B_s.toggle() ; break ;
        case 0x63:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x70:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x71:  C2.SP_s.toggle() ; break ;
        case 0x72:  C2.SP_s.toggle() ; break ;
        case 0x73:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x80:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; break ;
        case 0x81:  C4.PCh_s.toggle() ; break ;
        case 0x82:  C4.PCh_s.toggle() ; break ;
        case 0x83:  C4.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rts(uint8_t tick) {
    switch (tick) {
        case 0x00:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C2.SP_s.toggle() ; break ;
        case 0x12:  C2.SP_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x20:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; break ;
        case 0x21:  C2.PCl_s.toggle() ; break ;
        case 0x22:  C2.PCl_s.toggle() ; break ;
        case 0x23:  C4.RAM_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x30:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x31:  C3.B_s.toggle() ; break ;
        case 0x32:  C3.B_s.toggle() ; break ;
        case 0x33:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x40:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x41:  C2.SP_s.toggle() ; break ;
        case 0x42:  C2.SP_s.toggle() ; break ;
        case 0x43:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        
        case 0x50:  C2.SP_e.toggle() ; C4.RAM_e.toggle() ; break ;
        case 0x51:  C4.PCh_s.toggle() ; break ;
        case 0x52:  C4.PCh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case 0x53:  C4.RAM_e.toggle() ; C2.SP_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sbc(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case 0x01:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C3.A_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        case 0x10:  C3.ALU_op = ALU_SBC ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_C_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sec(uint8_t tick) {
    switch (tick) {
        // The STATUS word is never 0, at a minimum the constant bits will be on.
        // Decrementing it will always produce a carry.
        case 0x00:  C5.ST_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C5.ST_e.toggle() ; break ;

        // This is a (rentrance) bug !
        /*
        case 0x10:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C3.B_s.toggle() ; break ;
        case 0x12:  C3.B_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;
        */
        case 0x10:  C3.ALU_op = ALU_DEC ; 
                    C5.ST_C_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C5.ST_C_s.toggle() ; break ;
        
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
        case 0x00:  C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C1.ACC_e.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; C2.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t stx(uint8_t tick) {
    switch (tick) {
        case 0x00:  C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C1.X_e.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; C2.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t sty(uint8_t tick) {
    switch (tick) {
        case 0x00:  C4.EAh_e.toggle() ; C2.EAl_e.toggle() ; C1.Y_e.toggle() ; break ;
        case 0x01:  C4.RAM_s.toggle() ; break ;
        case 0x02:  C4.RAM_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; C2.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tax(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tay(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.ACC_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.ACC_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.Y_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tsx(uint8_t tick) {
    switch (tick) {
        case 0x00:  C2.SP_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C4.Al2D_e.toggle() ; C2.SP_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.X_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txa(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t txs(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.X_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.X_e.toggle() ; break ;

        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case 0x11:  C2.SP_s.toggle() ; break ;
        case 0x12:  C2.SP_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t tya(uint8_t tick) {
    switch (tick) {
        case 0x00:  C1.Y_e.toggle() ; break ;
        case 0x01:  C3.B_s.toggle() ; break ;
        case 0x02:  C3.B_s.toggle() ; break ;
        case 0x03:  C1.Y_e.toggle() ; break ;
        
        case 0x10:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;
        case 0x11:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x12:  C1.ACC_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x13:  C3.ALU_op = 0 ; 
                    C3.ALU_e.toggle() ; C5.ST_NZ_s.toggle() ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rst(uint8_t tick){
    switch (tick) {
        // Set SP and STATUS to 0
        case 0x00:  C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;
        case 0x01:  C2.SP_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x02:  C2.SP_s.toggle() ; C5.ST_s.toggle() ; break ;
        case 0x03:  C5.ST_src.toggle() ; C5.ST_NZ_s.toggle() ; C5.ST_V_s.toggle() ; C5.ST_C_s.toggle() ; break ;

        // Set ALU_c to 0 
        case 0x10:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case 0x11:  C5.ST_s.toggle() ; break ;
        case 0x12:  C5.ST_s.toggle() ; break ;
        case 0x13:  C5.ST_ALU_C_from_C.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case 0x20:  C2.SP_down.toggle() ; break ;
        case 0x21:  C2.SP_down.toggle() ; break ;
        case 0x22:  C2.SP_down.toggle() ; break ;
        case 0x23:  C2.SP_down.toggle() ; break ;

        // Decrement SP thrice to reach 0xFD
        case 0x30:  C2.SP_down.toggle() ; break ;
        case 0x31:  C2.SP_down.toggle() ; break ;
        case 0x32:  break ;
        case 0x33:  break ;

        default:    return 0 ;
    }
    return 1 ;    
}