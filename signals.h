class CONTROL_UNIT {
    public:
        // 1
        output<1> X_s, X_e, Y_s, Y_e, ACC_s, ACC_e ;
        // 2
        output<1> SP_down, SP_s, SP_e, EAl_s, EAl_e, PC_up, PCl_s, PC_e ;
        // 3
        output<4> ALU_op ; 
        output<1> A_s, ALU_e, B_s ;
        // 4
        output<1> Ah2D_e, INST_s, RAM_s, RAM_e, Al2D_e, EAh_s, EAh_e, PCh_s ;
        // 5
        output<1> ST_e, ST_src, ST_NZ_s, ST_V_s, ST_C_s, ST_ALU_C_s, ST_ALU_C_from_C, ST_s ;

    CONTROL_UNIT() :    X_e(1), Y_e(1), ACC_e(1), 
                        SP_down(1), SP_e(1), EAl_e(1), PC_up(1), PC_e(1), 
                        ALU_e(1),
                        Ah2D_e(1), RAM_e(1), Al2D_e(1), EAh_e(1){

    }
} ;