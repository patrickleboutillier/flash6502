
static void adc() { 
    STATUS_alu_c_from_C = 1 ; ACC_e = 1 ; 
    A_s = 1 ; STATUS_alu_c_set = 1 ; 
    A_s = 0 ; STATUS_alu_c_set = 0 ; 
    STATUS_alu_c_from_C = 0 ; ACC_e = 0 ;

    ALU_op = ALU_ADC ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_v_set = 1 ; STATUS_nz_set = 1 ;
    ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_v_set = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void and_() { 
    ACC_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    ACC_e = 0 ; 
    
    ALU_op = ALU_AND ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_nz_set = 1 ; 
    ACC_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void asl() { 
    ACC_e = 1 ; 
    A_s = 1 ; B_s = 1 ; 
    A_s = 0 ; B_s = 0 ; 
    ACC_e = 0 ; 
    
    if ((INST & 0xF) == 0xA){
    ALU_op = ALU_ADD ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ;
    ACC_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
    }
    else {
    ALU_op = ALU_ADD ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; STATUS_c_set = 1 ; STATUS_nz_set = 1 ; 
    RAM_s = 0 ; STATUS_c_set = 0 ; STATUS_nz_set = 0 ;
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; 
    }
}

static void bcc(){ 
    if (! STATUS.C){
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bcs() { 
    if (STATUS.C){
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void beq(){ 
    if (STATUS.Z){
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bit() { 
    ACC_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    ACC_e = 0 ; 
    
    ALU_op = ALU_BIT ; 
    STATUS_v_set = 1 ; STATUS_nz_set = 1 ; 
    STATUS_v_set = 0 ; STATUS_nz_set = 0 ;
    //
}

static void bmi() { 
    if (STATUS.N){
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bne(){ 
    if (! STATUS.Z) {
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bpl() { 
    if (! STATUS.N) {
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void brk() {
}

static void bvc() { 
    if (! STATUS.V) {
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void bvs() { 
    if (STATUS.V) {
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
    }
}

static void clc() { 
    //
    B_s = 1 ; 
    B_s = 0 ; 
    //

    ALU_op = ALU_PASS ; 
    STATUS_c_set = 1 ; 
    STATUS_c_set = 0 ;
    //
}

static void cld() {
}

static void cli() { 
}

static void clv() { 
    //
    B_s = 1 ; 
    B_s = 0 ; 
    //

    ALU_op = ALU_PASS ; 
    STATUS_v_set = 1 ; 
    STATUS_v_set = 0 ;
    //
}

static void cmp() { 
    ACC_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    ACC_e = 0 ; 
    
    ALU_op = ALU_CMP ; 
    STATUS_c_set = 1 ; STATUS_nz_set = 1 ; 
    STATUS_c_set = 0 ; STATUS_nz_set = 0 ; 
    //
}

static void cpx() { 
    X_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    X_e = 0 ; 
    
    ALU_op = ALU_CMP ; 
    STATUS_c_set = 1 ; STATUS_nz_set = 1 ; 
    STATUS_c_set = 0 ; STATUS_nz_set = 0 ;
    // 
}

static void cpy() { 
    Y_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    Y_e = 0 ; 
    
    ALU_op = ALU_CMP ; 
    STATUS_c_set = 1 ; STATUS_nz_set = 1 ; 
    STATUS_c_set = 0 ; STATUS_nz_set = 0 ;
    //
}

static void dec() { 
    ALU_op = ALU_DEC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; STATUS_nz_set = 1 ; 
    RAM_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ; 
}

static void dex() { 
    X_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    X_e = 0 ; 
    
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
    X_s = 1 ; STATUS_nz_set = 1 ; 
    X_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void dey() { 
    Y_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    Y_e = 0 ; 
    
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
    Y_s = 1 ; STATUS_nz_set = 1 ; 
    Y_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void eor() {
    ACC_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    ACC_e = 0 ; 
    
    ALU_op = ALU_EOR ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_nz_set = 1 ; 
    ACC_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void inc() {
    ALU_op = ALU_INC ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; STATUS_nz_set = 1 ; 
    RAM_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void inx() {
    X_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    X_e = 0 ; 
    
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    X_s = 1 ; STATUS_nz_set = 1 ; 
    X_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void iny() {
    Y_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    Y_e = 0 ; 
    
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    Y_s = 1 ; STATUS_nz_set = 1 ; 
    Y_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void jmp() {
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; 
    PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; 
    PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
}

static void jsr() { 
    PCh_e = 1 ; Ah2D_e = 1 ; 
    A_s = 1 ; A_s = 0 ; 
    Ah2D_e = 0 ; PCh_e = 0 ; 
    PCl_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; PCl_e = 0 ; 
    ALU_op = ALU_DEC ; ALU_e = 1 ; 
    PCl_s = 1 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; PCl_s = 0 ; 
    ALU_e = 0 ; 
    B_s = 1 ; B_s = 0 ; 
    ALU_op = ALU_SBC ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
    decSP() ; 
    PCl_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; PCl_e = 0 ; 
    ALU_op = ALU_PASS ; SPh_e = 1 ; SP_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    ALU_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
    decSP() ; 
    EAh_e = 1 ; Ah2D_e = 1 ; 
    PCh_s = 1 ; PCh_s = 0 ; 
    Ah2D_e = 0 ; EAh_e = 0 ;
    EAl_e = 1 ; Al2D_e = 1 ; 
    PCl_s = 1 ; PCl_s = 0 ; 
    Al2D_e = 0 ; EAl_e = 0 ;
}

static void lda() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    ACC_s = 1 ; ACC_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void ldx() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    X_s = 1 ; X_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void ldy() {
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    Y_s = 1 ; Y_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void lsr() {
    if ((INST & 0xF) == 0xA) {
    ALU_op = ALU_LSR ; ALU_e = 1 ; 
    ACC_s = 1 ; ACC_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
    }
    else {
    ALU_op = ALU_LSR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void nop() {
}

static void ora() {
    ACC_e = 1 ; 
    A_s = 1 ; 
    A_s = 0 ; 
    ACC_e = 0 ; 
    
    ALU_op = ALU_ORA ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_nz_set = 1 ; 
    ACC_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ; 
}

static void pha() {
    SPh_e = 1 ; SP_e = 1 ; ACC_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    ACC_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
    decSP() ;
}

static void php() {
    STATUS_b_in = 1 ; STATUS_data_enable = 1 ; SPh_e = 1 ; SP_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    SP_e = 0 ; SPh_e = 0 ; STATUS_data_enable = 0 ; STATUS_b_in = 0 ; 
    decSP() ;
}

static void pla() { 
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;  
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ; 
    ALU_op = ALU_PASS ; ALU_e = 1 ;
    ACC_s = 1 ; ACC_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void plp() {
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ; 
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; STATUS_src_data = 1 ; 
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_c_set = 0 ; 
    STATUS_src_data = 0 ; SPh_e = 0 ; SP_e = 0 ; RAM_e = 0 ; 
}

static void rol() {
    STATUS_alu_c_from_C = 1 ; 
    STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
    STATUS_alu_c_from_C = 0 ; 
    if ((INST & 0xF) == 0xA){
    ALU_op = ALU_ROL ; ALU_e = 1 ; 
    ACC_s = 1 ; ACC_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
    }
    else {
    ALU_op = ALU_ROL ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void ror() {
    STATUS_alu_c_from_C = 1 ; 
    STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
    STATUS_alu_c_from_C = 0 ; 
    if ((INST & 0xF) == 0xA){
    ALU_op = ALU_ROR ; ALU_e = 1 ; 
    ACC_s = 1 ; ACC_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
    }
    else {
    ALU_op = ALU_ROR ; EAh_e = 1 ; EAl_e = 1 ; ALU_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
    }
}

static void rti() {
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;  
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; STATUS_src_data = 1 ; 
    STATUS_nz_set = 1 ; STATUS_v_set = 1 ; STATUS_c_set = 1 ;
    STATUS_nz_set = 0 ; STATUS_v_set = 0 ; STATUS_c_set = 0 ; 
    STATUS_src_data = 0 ; SPh_e = 0 ; SP_e = 0 ; RAM_e = 0 ; 

    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
    PCl_s = 1 ; PCl_s = 0 ; 
    RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;    
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
    PCh_s = 1 ; PCh_s = 0 ; 
    RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
}

static void rts() {
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
    PCl_s = 1 ; PCl_s = 0 ; 
    RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    SP_s = 1 ; SP_s = 0 ;
    ALU_e = 0 ;
    SPh_e = 1 ; SP_e = 1 ; RAM_e = 1 ; 
    PCh_s = 1 ; PCh_s = 0 ; 
    RAM_e = 0 ; SP_e = 0 ; SPh_e = 0 ;
    incPC() ;
}

static void sbc() {
    STATUS_alu_c_from_C = 1 ; ACC_e = 1 ; 
    A_s = 1 ; A_s = 0 ; STATUS_alu_c_set = 1 ; STATUS_alu_c_set = 0 ; 
    STATUS_alu_c_from_C = 0 ; ACC_e = 0 ; 
    ALU_op = ALU_SBC ; ALU_e = 1 ; 
    ACC_s = 1 ; ACC_s = 0 ;  STATUS_c_set = 1 ; STATUS_c_set = 0 ; STATUS_v_set = 1 ; STATUS_v_set = 0 ; ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void sec() {
    B_s = 1 ; B_s = 0 ; 
    ALU_op = ALU_INC ; ALU_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    ALU_e = 0 ; 
    ALU_op = ALU_DEC ; 
     STATUS_c_set = 1 ; STATUS_c_set = 0 ;
}

static void sed() {
}

static void sei() {
}

static void sta() {
    EAh_e = 1 ; EAl_e = 1 ; ACC_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    ACC_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void stx() {
    EAh_e = 1 ; EAl_e = 1 ; X_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; 
    X_e = 0 ; EAl_e = 0 ; EAh_e = 0 ;
}

static void sty() {
    EAh_e = 1 ; EAl_e = 1 ; Y_e = 1 ; 
    RAM_s = 1 ; RAM_s = 0 ; Y_e = 0 ; 
    EAl_e = 0 ; EAh_e = 0 ;
}

static void tax() {
    ACC_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    ACC_e = 0 ; 
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    X_s = 1 ; X_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void tay() {
    ACC_e = 1 ; 
    B_s = 1 ; B_s = 0 ; 
    ACC_e = 0 ; 
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    Y_s = 1 ; Y_s = 0 ; STATUS_nz_set = 1 ; STATUS_nz_set = 0 ; ; 
    ALU_e = 0 ; 
}

static void tsx() {
    SP_e = 1 ; Al2D_e = 1 ; 
    B_s = 1 ;
    B_s = 0 ; 
    Al2D_e = 0 ; SP_e = 0 ;
    
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    X_s = 1 ; STATUS_nz_set = 1 ;
    X_s = 0 ; STATUS_nz_set = 0 ;
    ALU_e = 0 ; 
}

static void txa() {
    X_e = 1 ; 
    B_s = 1 ;
    B_s = 0 ; 
    X_e = 0 ;
    
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_nz_set = 1 ;
    ACC_s = 0 ; STATUS_nz_set = 0 ; 
    ALU_e = 0 ;
}

static void txs() {
    X_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    X_e = 0 ;

    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    SP_s = 1 ;
    SP_s = 0 ; 
    ALU_e = 0 ;
}

static void tya() {
    Y_e = 1 ; 
    B_s = 1 ; 
    B_s = 0 ; 
    Y_e = 0 ;
    
    ALU_op = ALU_PASS ; ALU_e = 1 ; 
    ACC_s = 1 ; STATUS_nz_set = 1 ;   
    ACC_s = 0 ; STATUS_nz_set = 0 ;
    ALU_e = 0 ; 
}
