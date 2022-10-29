
uint8_t adc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  STATUS_alu_c_from_C = 1 ; ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x02:  A_s = 0 ; STATUS_alu_c_set = 0 ; break ;
        case 0x03:  STATUS_alu_c_from_C = 0 ; ACC_e = 0 ; break ;

        case 0x10:  ALU_op = ALU_ADC ; ALU_e = 1 ; break ;
        case 0x11:  ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_v_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_v_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t and_(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_AND ; ALU_e = 1 ; break ;
        case 0x11:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl_acc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; B_s = 1 ; break ;
        case 0x02:  A_s = 0 ; B_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;

        case 0x10:  ALU_op = ALU_ADD ; ALU_e = 1 ; break ;
        case 0x11:  ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl_ram(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; B_s = 1 ; break ;
        case 0x02:  A_s = 0 ; B_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;

        case 0x10:  ALU_op = ALU_ADD ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x11:  RAM_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  RAM_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t asl(uint8_t tick) {
    if ((INST & 0xF) == 0xA){
        return asl_acc(tick) ;
    }
    else {
        return asl_ram(tick) ;
    }
}


uint8_t bcc(uint8_t tick){
    if (! STATUS.C){ 
        switch (tick) {  
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
        
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bcs(uint8_t tick) {
    if (STATUS.C){ 
        switch (tick) { 
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t beq(uint8_t tick){
    if (STATUS.Z){  
        switch (tick) {
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bit(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_BIT ; break ;
        case 0x11:  STATUS_v_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  STATUS_v_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t bmi(uint8_t tick){
    if (STATUS.N){  
        switch (tick) {
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bne(uint8_t tick){
    if (! STATUS.Z){  
        switch (tick) {
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bpl(uint8_t tick){
    if (! STATUS.N){  
        switch (tick) {
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

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
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t bvs(uint8_t tick){
    if (STATUS.V){  
        switch (tick) {
            case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
            case 0x01:  PCh_s = 1 ; break ;
            case 0x02:  PCh_s = 0 ; break ;
            case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
            
            case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
            case 0x11:  PCl_s = 1 ; break ;
            case 0x12:  PCl_s = 0 ; break ;
            case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;

            default:    return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


uint8_t clc(uint8_t tick) {
    switch (tick) { 
        case 0x00:  break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  break ;

        case 0x10:  ALU_op = ALU_PASS ; break ;
        case 0x11:  STATUS_c_set = 1 ; break ;
        case 0x12:  STATUS_c_set = 0 ; break ;
        case 0x13:  break ;

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
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  break ;

        case 0x10:  ALU_op = ALU_PASS ; break ;
        case 0x11:  STATUS_v_set = 1 ; break ;
        case 0x12:  STATUS_v_set = 0 ; break ;
        case 0x13:  break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cmp(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; break ;
        case 0x11:  STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpx(uint8_t tick) {
    switch (tick) { 
        case 0x00:  X_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  X_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; break ;
        case 0x11:  STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  break ; 
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t cpy(uint8_t tick) {
    switch (tick) { 
        case 0x00:  Y_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  Y_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_CMP ; break ;
        case 0x11:  STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dec(uint8_t tick) {
    switch (tick) { 
        case 0x00:  ALU_op = ALU_DEC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x01:  RAM_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x02:  RAM_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x03:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dex(uint8_t tick) {
    switch (tick) { 
        case 0x00:  X_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  X_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_DEC ; ALU_e = 1 ; break ;
        case 0x11:  X_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  X_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t dey(uint8_t tick) {
    switch (tick) { 
        case 0x00:  Y_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  Y_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_DEC ; ALU_e = 1 ; break ;
        case 0x11:  Y_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  Y_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t eor(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  ACC_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_EOR ; ALU_e = 1 ; break ;
        case 0x11:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inc(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_INC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x01:  RAM_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x02:  RAM_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x03:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t inx(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  X_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x11:  X_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  X_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t iny(uint8_t tick) {
    switch (tick) {
        case 0x00:  Y_e = 1 ; break ;
        case 0x01:  B_s = 1 ; break ;
        case 0x02:  B_s = 0 ; break ;
        case 0x03:  Y_e = 0 ; break ;
        
        case 0x10:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x11:  Y_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x12:  Y_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x13:  ALU_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jmp(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x01:  PCh_s = 1 ; break ;
        case 0x02:  PCh_s = 0 ; break ;
        case 0x03:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
        
        case 0x10:  EAl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x11:  PCl_s = 1 ; break ;
        case 0x12:  PCl_s = 0 ; break ;
        case 0x13:  Al2D_e = 0 ; EAl_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t jsr(uint8_t tick) {
    switch (tick) { 
        case 0x00:  PCh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x01:  A_s = 1 ; break ;
        case 0x02:  A_s = 0 ; break ;
        case 0x03:  Ah2D_e = 0 ; PCh_e = 0 ; break ;
        
        case 0x10:  PCl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x11:  B_s = 1 ; break ;
        case 0x12:  B_s = 0 ; break ;
        case 0x13:  Al2D_e = 0 ; PCl_e = 0 ; break ;
        
        case 0x20:  ALU_op = ALU_DEC ; ALU_e = 1 ; break ;
        case 0x21:  PCl_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x22:  STATUS_alu_c_set = 0 ; PCl_s = 0 ; break ;
        case 0x23:  ALU_e = 0 ; break ;
        
        case 0x30:  break ;
        case 0x31:  B_s = 1 ; break ; 
        case 0x32:  B_s = 0 ; break ;
        case 0x33:  break ;  

        case 0x40:  ALU_op = ALU_SBC ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; break ;
        case 0x41:  RAM_s = 1 ; break ;
        case 0x42:  RAM_s = 0 ; break ;
        case 0x43:  ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; decSP() ; break ;
        
        case 0x50:  PCl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x51:  B_s = 1 ; break ;
        case 0x52:  B_s = 0 ; break ;
        case 0x53:  Al2D_e = 0 ; PCl_e = 0 ; break ;
        
        case 0x60:  ALU_op = ALU_PASS ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; break ;
        case 0x61:  RAM_s = 1 ; break ;
        case 0x62:  RAM_s = 0 ; break ;
        case 0x63:  ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; decSP() ; break ;
        
        case 0x70:  EAh_e = 1 ; Ah2D_e = 1 ; break ;
        case 0x71:  PCh_s = 1 ; break ;
        case 0x72:  PCh_s = 0 ; break ;
        case 0x73:  Ah2D_e = 0 ; EAh_e = 0 ; break ;
        
        case 0x80:  EAl_e = 1 ; Al2D_e = 1 ; break ;
        case 0x81:  PCl_s = 1 ; break ;
        case 0x82:  PCl_s = 0 ; break ;
        case 0x83:  Al2D_e = 0 ; EAl_e = 0 ; break ;
        
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t lda(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x01:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x02:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x03:  ALU_e = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldx(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x01:  X_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x02:  X_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x03:  ALU_e = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


uint8_t ldy(uint8_t tick) {
    switch (tick) {
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x01:  Y_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x02:  Y_s = 0 ; STATUS_nz_set = 0 ; ; break ;
        case 0x03:  ALU_e = 0 ; break ;

        default:    return 0 ;
    }
    return 1 ;
}


#if 0
uint8_t lsr(uint8_t tick) {
    switch (tick) {
        case 0x00:  if ((INST & 0xF) == 0xA) {
        case 0x00:  ALU_op = ALU_LSR ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; ACC_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        case 0x00:  }
        case 0x00:  else {
        case 0x00:  ALU_op = ALU_LSR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; RAM_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; break ;
        case 0x00:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        case 0x00:  }
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t nop(uint8_t tick) {
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t ora(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e = 1 ; break ;
        case 0x00:  A_s = 1 ; break ;
        case 0x00:  A_s = 0 ; break ;
        case 0x00:  ACC_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_ORA ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pha(uint8_t tick) {
    switch (tick) {
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; ACC_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; break ;
        case 0x00:  RAM_s = 0 ; break ;
        case 0x00:  ACC_e = 0 ; SP_e = 0 ; SPh_e = 0 ; decSP() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t php(uint8_t tick) {
    switch (tick) {
        case 0x00:  STATUS_b_in = 1 ; STATUS_data_enable = 1 ; SPh_e = 1 ; SP_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; break ;
        case 0x00:  RAM_s = 0 ; break ;
        case 0x00:  SP_e = 0 ; SPh_e = 0 ; STATUS_data_enable = 0 ; STATUS_b_in = 0 ; decSP() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t pla(uint8_t tick) {
    switch (tick) { 
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t plp(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; STATUS_src_data = 1 ; break ;
        case 0x00:  STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_c_set = 1 ; break ;
        case 0x00:  STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_c_set = 0 ; break ;
        case 0x00:  STATUS_src_data = 0 ; SPh_e = 0 ; SP_e = 0 ; RAM_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t rol(uint8_t tick) {
    switch (tick) {
        case 0x00:  STATUS_alu_c_from_C = 1 ; break ;
        case 0x00:  STATUS_alu_c_set = 1 ; break ;
        case 0x00:  STATUS_alu_c_set = 0 ; break ;
        case 0x00:  STATUS_alu_c_from_C = 0 ; break ;

        case 0x00:  if ((INST & 0xF) == 0xA){
        case 0x00:  ALU_op = ALU_ROL ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        case 0x00:  }
        case 0x00:  else {
        case 0x00:  ALU_op = ALU_ROL ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  RAM_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        case 0x00:  }
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t ror(uint8_t tick) {
    switch (tick) {
        case 0x00:  STATUS_alu_c_from_C = 1 ; break ;
        case 0x00:  STATUS_alu_c_set = 1 ; break ;
        case 0x00:  STATUS_alu_c_set = 0 ; break ;
        case 0x00:  STATUS_alu_c_from_C = 0 ; break ;
        
        case 0x00:  if ((INST & 0xF) == 0xA){
        case 0x00:  ALU_op = ALU_ROR ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        case 0x00:  }
        case 0x00:  else {
        case 0x00:  ALU_op = ALU_ROR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  RAM_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        case 0x00:  }
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t rti(uint8_t tick) {
    switch (tick) { // 9 cycles
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; STATUS_src_data = 1 ; break ;
        case 0x00:  STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_c_set = 1 ; break ;
        case 0x00:  STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_c_set = 0 ; break ;
        case 0x00:  STATUS_src_data = 0 ; SPh_e = 0 ; SP_e = 0 ; RAM_e = 0 ; break ;

        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; break ;
        case 0x00:  PCl_s = 1 ; break ;
        case 0x00:  PCl_s = 0 ; break ;
        case 0x00:  RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; break ;
        
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; break ;
        case 0x00:  PCh_s = 1 ; break ;
        case 0x00:  PCh_s = 0 ; break ;
        case 0x00:  RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t rts(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; break ;
        case 0x00:  PCl_s = 1 ; break ;
        case 0x00:  PCl_s = 0 ; break ;
        case 0x00:  RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; break ;
        
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; break ;
        case 0x00:  PCh_s = 1 ; break ;
        case 0x00:  PCh_s = 0 ; break ;
        case 0x00:  RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; incPC() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sbc(uint8_t tick) {
    switch (tick) {
        case 0x00:  STATUS_alu_c_from_C = 1 ; ACC_e = 1 ; break ;
        case 0x00:  A_s = 1 ; STATUS_alu_c_set = 1 ; break ;
        case 0x00:  A_s = 0 ; STATUS_alu_c_set = 0 ; break ;
        case 0x00:  STATUS_alu_c_from_C = 0 ; ACC_e = 0 ; break ;

        case 0x00:  ALU_op = ALU_SBC ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_v_set = 1 ; STATUS_nz_set = 1
        case 0x00:  ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_v_set = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sec(uint8_t tick) {
    switch (tick) {
        case 0x00:  //
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  //

        case 0x00:  ALU_op = ALU_INC ; ALU_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_DEC ; break ;
        case 0x00:  STATUS_c_set = 1 ; break ;
        case 0x00:  STATUS_c_set = 0 ; break ;
        case 0x00:  //
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
        case 0x00:  EAh_e = 1 ; EAl_e = 1 ; ACC_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; break ;
        case 0x00:  RAM_s = 0 ; break ;
        case 0x00:  ACC_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t stx(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e = 1 ; EAl_e = 1 ; X_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; break ;
        case 0x00:  RAM_s = 0 ; break ;
        case 0x00:  X_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t sty(uint8_t tick) {
    switch (tick) {
        case 0x00:  EAh_e = 1 ; EAl_e = 1 ; Y_e = 1 ; break ;
        case 0x00:  RAM_s = 1 ; break ;
        case 0x00:  RAM_s = 0 ; break ;
        case 0x00:  Y_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t tax(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  ACC_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  X_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  X_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t tay(uint8_t tick) {
    switch (tick) {
        case 0x00:  ACC_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  ACC_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  Y_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  Y_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t tsx(uint8_t tick) {
    switch (tick) {
        case 0x00:  SP_e = 1 ; Al2D_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Al2D_e = 0 ; SP_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  X_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  X_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t txa(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  X_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t txs(uint8_t tick) {
    switch (tick) {
        case 0x00:  X_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  X_e = 0 ; break ;

        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  SP_s = 1 ; break ;
        case 0x00:  SP_s = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

uint8_t tya(uint8_t tick) {
    switch (tick) {
        case 0x00:  Y_e = 1 ; break ;
        case 0x00:  B_s = 1 ; break ;
        case 0x00:  B_s = 0 ; break ;
        case 0x00:  Y_e = 0 ; break ;
        
        case 0x00:  ALU_op = ALU_PASS ; ALU_e = 1 ; break ;
        case 0x00:  ACC_s = 1 ; STATUS_nz_set = 1 ; break ;
        case 0x00:  ACC_s = 0 ; STATUS_nz_set = 0 ; break ;
        case 0x00:  ALU_e = 0 ; break ;
        default:    return 0 ;
    }
    return 1 ;
}

#endif