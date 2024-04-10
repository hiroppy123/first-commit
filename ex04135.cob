identification      division.
program-id.         ex04133.
data                division.
working-storage     section.
01   DATA01         pic 9(2).
01   DATA02         pic 9(3).
01   DATA03         pic 9(8).
01   DATA04         pic 9(8).
01   DATA05         pic 9(8).
01   DATA06         pic 9(8).
01   COUNTER01      pic 9(8)  value  zero.
01   COUNTER02      pic 9(8)  value  zero.
01   COUNTER03      pic 9(8)  value  zero.
01   COUNTER04      pic 9(8)  value  zero.
01   DATA07         pic 9(8)  value  zero.
01   DATA08         pic 9(8)  value  zero.
procedure           division.
RTN-START.
     perform  until  DATA01  =  9
          display  "性別は　(0:男　1:女)　？"
          accept  DATA01
          if  DATA01  =  0
          	add  1  to  COUNTER01
          	display  "年齢は？"
          	accept  DATA02
          	add  DATA02  to  COUNTER02
          	compute  DATA03  =  COUNTER02  /  COUNTER01
          	display  "男性の平均年齢は"  DATA03
                if  DATA02 > DATA07
                    move DATA02 to DATA07
                end-if
                display  "男性の最高年齢は"  DATA07
          else  if  DATA01  =  1
          	add  1  to  COUNTER03
          	display  "年齢は？"
          	accept  DATA04
          	add  DATA04  to  COUNTER04
          	compute  DATA05  =  COUNTER04  /  COUNTER03
          	display  "女性の平均年齢は"  DATA05
                if  DATA04 > DATA08
                    move DATA04 to DATA08
                end-if
                display "女性の最高年齢は" DATA08
          end-perform.
          stop  run.
