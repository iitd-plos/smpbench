target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"hello world\0A\00"

; External declaration of the puts function
declare i32 @puts(i8* nocapture) nounwind

; Definition of main function
define i32 @main() {   ; i32()*
  ; Convert [13 x i8]* to i8  *...
  %cast210 = getelementptr [13 x i8]* @.str
  ; Call puts function to write out the string to stdout.
  %c2 = bitcast [13 x i8]* %cast210 to i8*
  call i32 @puts(i8 *%c2)
  ret i32 0
}

; Named metadata
;!1 = metadata !{i32 42}
;!foo = !{!1, !1}
