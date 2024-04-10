identification     division.
program-id.        ex0401.
data               division.
working-storage    section.
01  COUNTER        pic 9(3) value zero.
procedure          division.
RTN-START.
    display  "回数="  COUNTER
    add  1  to  COUNTER  on  size  error  go  to  RTN-END.
    go  to  RTN-START.
RTN-END.
    stop run.
