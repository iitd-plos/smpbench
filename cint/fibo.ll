target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"fibo(%d)=%d\0A\00"

; External declaration of the printf function
declare i32 @printf(i8*, ...) #2

; @N = constant i32 10

; Definition of main function
define i32 @main() #0 {
  ; Convert [13 x i8]* to i8  *...
  ; %n = load i32 *@N
  %n = add i32 0, 10
  br label %1

; <label>:1
  %2 = phi i32 [ 0, %0 ], [ %5, %1 ]
  %3 = phi i32 [ 0, %0 ], [ %4, %1 ]
  %4 = phi i32 [ 1, %0 ], [ %6, %1 ]
  %5 = add i32 1, %2
  %6 = add i32 %3, %4
  %7 = icmp ne i32 %2, %n
  br i1 %7, label %1, label %8
  
; <label>:8
  %9 = getelementptr inbounds [13 x i8], [13 x i8]* @.str, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8 *%9, i32 %n, i32 %3)
  ret i32 0
}
