target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str1 = private unnamed_addr constant [13 x i8] c"fibo(%d)=%d\0A\00"
@.str2 = private unnamed_addr constant [15 x i8] c"fibo10(%d)=%d\0A\00"

; External declaration of the printf function
declare i32 @printf(i8*, ...) #2

; @N = constant i32 10

; Definition of fibo function
define i32 @fibo(i32 %n) #0 {
  ; %n = load i32 *@N
  ; %n = add i32 0, 10
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
  %9 = getelementptr inbounds [13 x i8], [13 x i8]* @.str1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8 * %9, i32 %n, i32 %3)
  ret i32 0
}

; Definition of fibo10 function
define i32 @fibo10(i32 %n) #0 {
  ; %n = load i32 *@N
  ; %n = add i32 0, 10
  br label %1

; <label>:1
  %2 = phi i32 [ 0, %0 ], [ %13, %1 ]
  %3 = phi i32 [ 0, %0 ], [ %4, %1 ]
  %4 = phi i32 [ 0, %0 ], [ %5, %1 ]
  %5 = phi i32 [ 0, %0 ], [ %6, %1 ]
  %6 = phi i32 [ 0, %0 ], [ %7, %1 ]
  %7 = phi i32 [ 0, %0 ], [ %8, %1 ]
  %8 = phi i32 [ 0, %0 ], [ %9, %1 ]
  %9 = phi i32 [ 0, %0 ], [ %10, %1 ]
  %10 = phi i32 [ 0, %0 ], [ %11, %1 ]
  %11 = phi i32 [ 0, %0 ], [ %12, %1 ]
  %12 = phi i32 [ 1, %0 ], [ %22, %1 ]
  %13 = add i32 1, %2
  %14 = add i32 %3, %4
  %15 = add i32 %14, %5
  %16 = add i32 %15, %6
  %17 = add i32 %16, %7
  %18 = add i32 %17, %8
  %19 = add i32 %18, %9
  %20 = add i32 %19, %10
  %21 = add i32 %20, %11
  %22 = add i32 %21, %12
  %23 = icmp ne i32 %2, %n
  %24 = call i32 @fibo(i32 %2)
  br i1 %23, label %1, label %25
  
; <label>:25
  %26 = getelementptr inbounds [15 x i8], [15 x i8]* @.str2, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8 * %26, i32 %n, i32 %12)
  ret i32 0
}

define i32 @main() #0 {
  %n = add i32 0, 10
  call i32 @fibo10(i32 %n)
  ret i32 0
}
