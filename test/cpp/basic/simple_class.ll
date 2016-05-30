; ModuleID = 'simple_class.cc'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

%class.Point = type { i32, i32 }

; Function Attrs: ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %p = alloca %class.Point, align 4
  store i32 0, i32* %1, align 4
  call void @_ZN5PointC1Eii(%class.Point* %p, i32 0, i32 0)
  ret i32 0
}

; Function Attrs: ssp uwtable
define linkonce_odr void @_ZN5PointC1Eii(%class.Point* %this, i32 %x, i32 %y) unnamed_addr #0 align 2 {
  %1 = alloca %class.Point*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store %class.Point* %this, %class.Point** %1, align 8
  store i32 %x, i32* %2, align 4
  store i32 %y, i32* %3, align 4
  %4 = load %class.Point*, %class.Point** %1, align 8
  %5 = load i32, i32* %2, align 4
  %6 = load i32, i32* %3, align 4
  call void @_ZN5PointC2Eii(%class.Point* %4, i32 %5, i32 %6)
  ret void
}

; Function Attrs: nounwind ssp uwtable
define linkonce_odr void @_ZN5PointC2Eii(%class.Point* %this, i32 %x, i32 %y) unnamed_addr #1 align 2 {
  %1 = alloca %class.Point*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store %class.Point* %this, %class.Point** %1, align 8
  store i32 %x, i32* %2, align 4
  store i32 %y, i32* %3, align 4
  %4 = load %class.Point*, %class.Point** %1, align 8
  %5 = getelementptr inbounds %class.Point, %class.Point* %4, i32 0, i32 0
  %6 = load i32, i32* %2, align 4
  store i32 %6, i32* %5, align 4
  %7 = getelementptr inbounds %class.Point, %class.Point* %4, i32 0, i32 1
  %8 = load i32, i32* %3, align 4
  store i32 %8, i32* %7, align 4
  ret void
}

attributes #0 = { ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 7.3.0 (clang-703.0.29)"}
