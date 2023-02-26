#ifndef MONITOR_H
#define MONITOR_H

#define INST_PC      0x0F
#define INST_MON     0x1F

void insert_inst(uint8_t opcode, bool process) ;
bool button_pressed(uint8_t button_pin) ;


class MONITOR {
  private:
    DATA *_data ;
    uint16_t _pc, _ea, _prev_pc ;
    uint8_t _inst, _sp, _acc, _x, _y, _status, _prev_inst ;

  public:
    MONITOR(DATA *data){
      _data = data ;
    }

    inline uint16_t get_pc(){
      return _pc ;
    }

    inline bool pc_changed(){
      return _pc != _prev_pc ;
    }
    
    inline uint8_t get_inst(){
      return _inst ;
    }

    inline void set_inst(uint8_t inst){
      _inst = inst ;
    }
    
    void trace(const char *label=nullptr, bool force_full=false, bool nl=true){
      static char buf[128] ;
    
      if (label != nullptr){
        sprintf(buf, "%8s", label) ;
      }
      else {
        sprintf(buf, "%8ld", INST_CNT) ;
      }
      Serial.print(buf) ;
    
      if ((STEP_CNT == 0)||(force_full)){
        sprintf(buf, " %2d PC:0x%04X  INST:0x%02X  EA:0x%04X ACC:%-3d X:%-3d Y:%-3d SP:0x%02X STATUS:0x%02X", 
          STEP_CNT, _pc, _inst, _ea, _acc, _x, _y, _sp, _status) ;
      }
      else {
        sprintf(buf, " %2d PC:0x%04X~ INST:0x%02X  ", STEP_CNT, _pc, _inst) ;
      }
      if (nl){
        strcat(buf, "\n") ;
      }
      Serial.print(buf) ;
    }

    inline void pause(){
      Serial.println(F("\nPAUSE:")) ;
      while (! button_pressed(STEP)){} ; 
    }
    
    inline void step(){
      if ((_inst != INST_MON)&&(_inst != INST_PC)){
        trace(nullptr, false, false) ;
        Serial.print(F("  ")) ;
        Serial.print(STEP_CNT) ;
        Serial.print(" done...") ;
        while (! button_pressed(STEP)){} ;
        Serial.println() ;
      }
    }
    
    inline void process(bool grab_inst){
      // See fetch()
      if ((grab_inst)&&(STEP_CNT == 3)){
        _prev_inst = _inst ;
        _inst = _data->read() ;
      }
  
      // See pc()
      if (_inst == INST_PC){
        switch (STEP_CNT){
          case 2: _prev_pc = _pc ;
                  _pc = _data->read() << 8 ; 
                  break ;
          case 4: _pc |= _data->read() ; 
                  break ;
        }
      }
      // See mon()
      else if (_inst == INST_MON){
        switch (STEP_CNT){
          case  2: _prev_pc = _pc ;
                   _pc = _data->read() << 8 ; 
                   break ;
          case  4: _pc |= _data->read() ; 
                   break ;
          case  6: _ea = _data->read() << 8 ; 
                   break ;
          case  8: _ea |= _data->read() ; 
                   break ;
          case 10: _sp = _data->read() ; 
                   break ;
          case 12: _acc = _data->read() ; 
                   break ;
          case 14: _x = _data->read() ; 
                   break ;
          case 16: _y = _data->read() ; 
                   break ;
          case 18: _status = _data->read() ; 
                   break ;
        }
      }
    }

    inline void sample(bool pc_only=false){
      insert_inst(pc_only ? INST_PC : INST_MON, true) ;
      // Replace original instruction
      insert_inst(_prev_inst, false) ;
    }
} ;


#endif 
