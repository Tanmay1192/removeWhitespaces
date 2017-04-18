# removeWhitespaces
A simple  C API to remove white-spaces from beginning, end and all the white-spaces -
Purpose :
 The purpose of this function is to remove white-spaces from a string, with ability to change in original string
 or you can provide output string, as per requirement you just have to set tampering mode to NOT_TRIM_ORIGNAL or 
 TRIM_ORIGNAL with valid output buffer if NOT_TRIM_ORIGNAL is set. 
 It also provides the ability to remove whites from start, end or all white-spaces
 encountered by using flags viz. : FROM_START, FROM_END and ALL 
    E.g.:
 str <- [ hello world ] 
   i)   ndlb_remove_whitespaces(str, NULL, FROM_START, TRIM_ORIGNAL)            => [hello world ]
   ii)  ndlb_remove_whitespaces(str, NULL, FROM_END, TRIM_ORIGNAL)              => [ hello world]
   iii) ndlb_remove_whitespaces(str, NULL, ALL, TRIM_ORIGNAL)                   => [helloworld]
   iv)  ndlb_remove_whitespaces(str, NULL, FROM_START|FROM_END, TRIM_ORIGNAL)   => [hello world]
   v)   ndlb_remove_whitespaces(str, out_buf, FROM_START, NOT_TRIM_ORIGNAL)     => str:[ hello world ], out_buf:[hello world ]
