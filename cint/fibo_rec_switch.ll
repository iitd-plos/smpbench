target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str2 = private unnamed_addr constant [15 x i8] c"fibo_r(%d)=%d\0A\00"

; External declaration of the printf function
declare i32 @printf(i8*, ...) #2

; @N = constant i32 10

; Definition of fibo_r function
define i32 @fibo_r(i32 %n) #0 {
  %1 = add i32 0, 0
  switch i32 %n, label %4 [
    i32 0, label %2
    i32 1, label %3
  ]

; <label>:2
  ret i32 0

; <label>:3
  ret i32 1

; <label>:4
  %5 = add i32 0, 0
  %6 = add i32 0, 0
  %7 = sub i32 %n, 1
  %8 = sub i32 %n, 2
  %9 = call i32 @fibo_r(i32 %7)
  %10 = call i32 @fibo_r(i32 %8)
  %11 = add i32 %9, %10
  ret i32 %11
}

define i32 @main() #0 {
  %n = add i32 0, 10
  %1 = call i32 @fibo_r(i32 %n)
  %2 = getelementptr inbounds [15 x i8]* @.str2, i32 0, i32 0
  %3 = load i8* getelementptr inbounds ([15 x i8]* @.str2, i32 0, i32 1), align 4
  call i32 (i8*, ...)* @printf(i8 * %2, i32 %n, i32 %1)
  ret i32 0
}
