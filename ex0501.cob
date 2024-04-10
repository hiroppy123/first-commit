identification     division.
program-id.        ex0501.
data               division.
working-storage    section.
01  TABLE1.
    03  T1-DATA    pic  9(3)  occurs  5.
01  ELEMENT-NO     pic  9.
procedure          division.
RTN-START.
    initialize  TABLE1.
    perform varying ELEMENT-NO from 1 by 1 until ELEMENT-NO > 5
       accept  T1-DATA(ELEMENT-NO)
    end-perform.
    perform varying ELEMENT-NO from 5 by -1 until ELEMENT-NO < 1
       display  T1-DATA(ELEMENT-NO)
    end-perform.
    stop  run.
    
