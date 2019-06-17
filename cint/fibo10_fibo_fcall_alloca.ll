target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str1 = private unnamed_addr constant [13 x i8] c"fibo(%d)=%d\0A\00"
@.str2 = private unnamed_addr constant [15 x i8] c"fibo10(%d)=%d\0A\00"

; External declaration of the printf function
declare i32 @printf(i8*, ...) #2

; @N = constant i32 10

; Definition of fibo function
define i32 @fibo(i32 %n) #0 {
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 0, i32* %x, align 4
  store i32 1, i32* %y, align 4
  br label %1

; <label>:1
  %2 = load i32, i32* %i, align 4
  %3 = add i32 1, %2
  store i32 %3, i32* %i, align 4
  %4 = load i32, i32* %x, align 4
  %5 = load i32, i32* %y, align 4
  %6 = add i32 %4, %5
  store i32 %5, i32* %x, align 4
  store i32 %6, i32* %y, align 4
  %7 = icmp ne i32 %2, %n
  br i1 %7, label %1, label %8
  
; <label>:8
  %9 = getelementptr inbounds [13 x i8], [13 x i8]* @.str1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8 * %9, i32 %n, i32 %4)
  ret i32 0
}

; Definition of fibo10 function
define i32 @fibo10(i32* %nptr) #0 {
  %n = load i32, i32* %nptr, align 4
  %i = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 0, i32* %i, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  store i32 0, i32* %6, align 4
  store i32 0, i32* %7, align 4
  store i32 0, i32* %8, align 4
  store i32 0, i32* %9, align 4
  store i32 1, i32* %10, align 4
  br label %11

; <label>:11
  %outgoing_val = load i32, i32* %1, align 4
  %12 = load i32, i32* %2, align 4
  store i32 %12, i32* %1
  %13 = load i32, i32* %3, align 4
  store i32 %13, i32* %2
  %14 = load i32, i32* %4, align 4
  store i32 %14, i32* %3
  %15 = load i32, i32* %5, align 4
  store i32 %15, i32* %4
  %16 = load i32, i32* %6, align 4
  store i32 %16, i32* %5
  %17 = load i32, i32* %7, align 4
  store i32 %17, i32* %6
  %18 = load i32, i32* %8, align 4
  store i32 %18, i32* %7
  %19 = load i32, i32* %9, align 4
  store i32 %19, i32* %8
  %20 = load i32, i32* %10, align 4
  store i32 %20, i32* %9
  %21 = add i32 %outgoing_val, %12
  %22 = add i32 %21, %13
  %23 = add i32 %22, %14
  %24 = add i32 %23, %15
  %25 = add i32 %24, %16
  %26 = add i32 %25, %17
  %27 = add i32 %26, %18
  %28 = add i32 %27, %19
  %29 = add i32 %28, %20
  store i32 %29, i32* %10
  %30 = load i32, i32* %i, align 32
  %31 = add i32 1, %30
  store i32 %31, i32* %i, align 32
  %32 = icmp ne i32 %30, %n
  %33 = call i32 @fibo(i32 %30)
  br i1 %32, label %11, label %34
  
; <label>:34
  %35 = getelementptr inbounds [15 x i8], [15 x i8]* @.str2, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8 * %35, i32 %n, i32 %20)
  ret i32 0
}

define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 10, i32* %1, align 4
  call i32 @fibo10(i32* %1)
  ret i32 0
}
