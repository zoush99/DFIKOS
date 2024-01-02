; ModuleID = '/tmp/testArray-78749f.ll'
source_filename = "/tmp/testArray-78749f.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.BSS1 = type <{ [64 x i8] }>
%struct.STATICS1 = type <{ [8 x i8] }>

@.BSS1 = internal global %struct.BSS1 zeroinitializer, align 32
@.STATICS1 = internal global %struct.STATICS1 <{ [8 x i8] c"\03\00\00\00\03\00\00\00" }>, align 16
@.C359_main_ = internal constant i32 38
@.C335_main_ = internal constant i32 2
@.C358_main_ = internal constant [13 x i8] c"Sliced Array:"
@.C357_main_ = internal constant i32 36
@.C355_main_ = internal constant i32 29
@.C330_main_ = internal constant i32 3
@.C353_main_ = internal constant i32 14
@.C350_main_ = internal constant [15 x i8] c"Original Array:"
@.C309_main_ = internal constant i32 0
@.C347_main_ = internal constant i32 6
@.C344_main_ = internal constant [13 x i8] c"testArray.f90"
@.C339_main_ = internal constant i32 9
@.C311_main_ = internal constant i32 1
@.C336_main_ = internal constant i64 2
@.C346_main_ = internal constant i32 27
@.C331_main_ = internal constant i64 3
@.C312_main_ = internal constant i64 1
@.C333_main_ = internal constant i64 4
@.C378_main_ = internal constant i64 27
@.C310_main_ = internal constant i64 0

define float @main_() !dbg !5 {
L.entry:
  %"tmp$r$sd4_377" = alloca [16 x i64], align 8
  %"tmp$r1$sd3_376" = alloca [16 x i64], align 8
  %z_i_0_342 = alloca i64, align 8
  %.dY0001_387 = alloca i32, align 4
  %z_i_1_343 = alloca i32, align 4
  %z_a_0_341 = alloca [9 x i32], align 16
  %"reshap$r$p_362" = alloca i32*, align 8
  %z_b_1_363 = alloca i64, align 8
  %z_b_2_364 = alloca i64, align 8
  %z_b_3_365 = alloca i64, align 8
  %z_b_4_366 = alloca i64, align 8
  %.dY0002_390 = alloca i64, align 8
  %"i$a_367" = alloca i64, align 8
  %.dY0003_393 = alloca i64, align 8
  %"i$b_368" = alloca i64, align 8
  %z__io_349 = alloca i32, align 4
  %.dY0004_396 = alloca i32, align 4
  %i_338 = alloca i32, align 4
  %"original_array$ss_369" = alloca i64, align 8
  %.dY0005_399 = alloca i64, align 8
  %"i$a$i_371" = alloca i64, align 8
  %"tmp$r_370" = alloca [3 x float], align 4
  %.dY0006_402 = alloca i64, align 8
  %.dY0007_405 = alloca i64, align 8
  %.dY0008_408 = alloca i32, align 4
  %"sliced_array$ss_372" = alloca i64, align 8
  %.dY0009_411 = alloca i64, align 8
  %"i$a$i2_374" = alloca i64, align 8
  %"tmp$r1_373" = alloca [2 x float], align 4
  %main_329 = alloca float, align 4
  %0 = bitcast [16 x i64]* %"tmp$r$sd4_377" to i8*
  %1 = bitcast i64* @.C310_main_ to i8*
  %2 = bitcast i64* @.C378_main_ to i8*
  %3 = bitcast i64* @.C333_main_ to i8*
  %4 = bitcast i64* @.C312_main_ to i8*
  %5 = bitcast i64* @.C331_main_ to i8*
  %6 = bitcast void (...)* @f90_template1_i8 to void (i8*, i8*, i8*, i8*, i8*, i8*, ...)*
  call void (i8*, i8*, i8*, i8*, i8*, i8*, ...) %6(i8* %0, i8* %1, i8* %2, i8* %3, i8* %4, i8* %5)
  %7 = bitcast [16 x i64]* %"tmp$r$sd4_377" to i8*
  %8 = bitcast void (...)* @f90_set_intrin_type_i8 to void (i8*, i32, ...)*
  call void (i8*, i32, ...) %8(i8* %7, i32 27)
  %9 = bitcast [16 x i64]* %"tmp$r1$sd3_376" to i8*
  %10 = bitcast i64* @.C310_main_ to i8*
  %11 = bitcast i64* @.C378_main_ to i8*
  %12 = bitcast i64* @.C333_main_ to i8*
  %13 = bitcast i64* @.C312_main_ to i8*
  %14 = bitcast i64* @.C336_main_ to i8*
  %15 = bitcast void (...)* @f90_template1_i8 to void (i8*, i8*, i8*, i8*, i8*, i8*, ...)*
  call void (i8*, i8*, i8*, i8*, i8*, i8*, ...) %15(i8* %9, i8* %10, i8* %11, i8* %12, i8* %13, i8* %14)
  %16 = bitcast [16 x i64]* %"tmp$r1$sd3_376" to i8*
  %17 = bitcast void (...)* @f90_set_intrin_type_i8 to void (i8*, i32, ...)*
  call void (i8*, i32, ...) %17(i8* %16, i32 27)
  br label %L.LB1_420

L.LB1_420:                                        ; preds = %L.entry
  store i64 1, i64* %z_i_0_342, align 8, !dbg !9
  store i32 9, i32* %.dY0001_387, align 4, !dbg !9
  store i32 1, i32* %z_i_1_343, align 4, !dbg !9
  br label %L.LB1_385

L.LB1_385:                                        ; preds = %L.LB1_385, %L.LB1_420
  %18 = load i32, i32* %z_i_1_343, align 4, !dbg !9
  %19 = load i64, i64* %z_i_0_342, align 8, !dbg !9
  %20 = bitcast [9 x i32]* %z_a_0_341 to i8*, !dbg !9
  %21 = getelementptr i8, i8* %20, i64 -4, !dbg !9
  %22 = bitcast i8* %21 to i32*, !dbg !9
  %23 = getelementptr i32, i32* %22, i64 %19, !dbg !9
  store i32 %18, i32* %23, align 4, !dbg !9
  %24 = load i64, i64* %z_i_0_342, align 8, !dbg !9
  %25 = add nsw i64 %24, 1, !dbg !9
  store i64 %25, i64* %z_i_0_342, align 8, !dbg !9
  %26 = load i32, i32* %z_i_1_343, align 4, !dbg !9
  %27 = add nsw i32 %26, 1, !dbg !9
  store i32 %27, i32* %z_i_1_343, align 4, !dbg !9
  %28 = load i32, i32* %.dY0001_387, align 4, !dbg !9
  %29 = sub nsw i32 %28, 1, !dbg !9
  store i32 %29, i32* %.dY0001_387, align 4, !dbg !9
  %30 = load i32, i32* %.dY0001_387, align 4, !dbg !9
  %31 = icmp sgt i32 %30, 0, !dbg !9
  br i1 %31, label %L.LB1_385, label %L.LB1_485, !dbg !9, !llvm.loop !10

L.LB1_485:                                        ; preds = %L.LB1_385
  %32 = bitcast [9 x i32]* %z_a_0_341 to i8*, !dbg !9
  %33 = bitcast i32** %"reshap$r$p_362" to i8**, !dbg !9
  store i8* %32, i8** %33, align 8, !dbg !9
  %34 = bitcast %struct.STATICS1* @.STATICS1 to i32*, !dbg !9
  %35 = load i32, i32* %34, align 4, !dbg !9
  %36 = sext i32 %35 to i64, !dbg !9
  store i64 %36, i64* %z_b_1_363, align 8, !dbg !9
  %37 = bitcast %struct.STATICS1* @.STATICS1 to i8*, !dbg !9
  %38 = getelementptr i8, i8* %37, i64 4, !dbg !9
  %39 = bitcast i8* %38 to i32*, !dbg !9
  %40 = load i32, i32* %39, align 4, !dbg !9
  %41 = sext i32 %40 to i64, !dbg !9
  store i64 %41, i64* %z_b_2_364, align 8, !dbg !9
  %42 = load i64, i64* %z_b_1_363, align 8, !dbg !9
  store i64 %42, i64* %z_b_3_365, align 8, !dbg !9
  %43 = load i64, i64* %z_b_3_365, align 8, !dbg !9
  %44 = add nsw i64 %43, 1, !dbg !9
  store i64 %44, i64* %z_b_4_366, align 8, !dbg !9
  store i64 3, i64* %.dY0002_390, align 8, !dbg !9
  store i64 1, i64* %"i$a_367", align 8, !dbg !9
  br label %L.LB1_388

L.LB1_388:                                        ; preds = %L.LB1_486, %L.LB1_485
  store i64 3, i64* %.dY0003_393, align 8, !dbg !9
  store i64 1, i64* %"i$b_368", align 8, !dbg !9
  br label %L.LB1_391

L.LB1_391:                                        ; preds = %L.LB1_391, %L.LB1_388
  %45 = load i64, i64* %"i$b_368", align 8, !dbg !9
  %46 = load i64, i64* %z_b_3_365, align 8, !dbg !9
  %47 = load i64, i64* %"i$a_367", align 8, !dbg !9
  %48 = mul nsw i64 %46, %47, !dbg !9
  %49 = add nsw i64 %45, %48, !dbg !9
  %50 = load i64, i64* %z_b_4_366, align 8, !dbg !9
  %51 = sub nsw i64 %49, %50, !dbg !9
  %52 = load i32*, i32** %"reshap$r$p_362", align 8, !dbg !9
  %53 = getelementptr i32, i32* %52, i64 %51, !dbg !9
  %54 = load i32, i32* %53, align 4, !dbg !9
  %55 = sitofp i32 %54 to float, !dbg !9
  %56 = load i64, i64* %"i$b_368", align 8, !dbg !9
  %57 = load i64, i64* %"i$a_367", align 8, !dbg !9
  %58 = mul nsw i64 %57, 3, !dbg !9
  %59 = add nsw i64 %56, %58, !dbg !9
  %60 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !9
  %61 = getelementptr i8, i8* %60, i64 -16, !dbg !9
  %62 = bitcast i8* %61 to float*, !dbg !9
  %63 = getelementptr float, float* %62, i64 %59, !dbg !9
  store float %55, float* %63, align 4, !dbg !9
  %64 = load i64, i64* %"i$b_368", align 8, !dbg !9
  %65 = add nsw i64 %64, 1, !dbg !9
  store i64 %65, i64* %"i$b_368", align 8, !dbg !9
  %66 = load i64, i64* %.dY0003_393, align 8, !dbg !9
  %67 = sub nsw i64 %66, 1, !dbg !9
  store i64 %67, i64* %.dY0003_393, align 8, !dbg !9
  %68 = load i64, i64* %.dY0003_393, align 8, !dbg !9
  %69 = icmp sgt i64 %68, 0, !dbg !9
  br i1 %69, label %L.LB1_391, label %L.LB1_486, !dbg !9, !llvm.loop !11

L.LB1_486:                                        ; preds = %L.LB1_391
  %70 = load i64, i64* %"i$a_367", align 8, !dbg !9
  %71 = add nsw i64 %70, 1, !dbg !9
  store i64 %71, i64* %"i$a_367", align 8, !dbg !9
  %72 = load i64, i64* %.dY0002_390, align 8, !dbg !9
  %73 = sub nsw i64 %72, 1, !dbg !9
  store i64 %73, i64* %.dY0002_390, align 8, !dbg !9
  %74 = load i64, i64* %.dY0002_390, align 8, !dbg !9
  %75 = icmp sgt i64 %74, 0, !dbg !9
  br i1 %75, label %L.LB1_388, label %L.LB1_487, !dbg !9, !llvm.loop !12

L.LB1_487:                                        ; preds = %L.LB1_486
  %76 = bitcast i32* @.C346_main_ to i8*, !dbg !13
  %77 = bitcast [13 x i8]* @.C344_main_ to i8*, !dbg !13
  %78 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !13
  call void (i8*, i8*, i64, ...) %78(i8* %76, i8* %77, i64 13), !dbg !13
  %79 = bitcast i32* @.C347_main_ to i8*, !dbg !13
  %80 = bitcast i32* @.C309_main_ to i8*, !dbg !13
  %81 = bitcast i32* @.C309_main_ to i8*, !dbg !13
  %82 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !13
  %83 = call i32 (i8*, i8*, i8*, i8*, ...) %82(i8* %79, i8* null, i8* %80, i8* %81), !dbg !13
  store i32 %83, i32* %z__io_349, align 4, !dbg !13
  %84 = bitcast [15 x i8]* @.C350_main_ to i8*, !dbg !13
  %85 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !13
  %86 = call i32 (i8*, i32, i64, ...) %85(i8* %84, i32 14, i64 15), !dbg !13
  store i32 %86, i32* %z__io_349, align 4, !dbg !13
  %87 = call i32 (...) @f90io_ldw_end(), !dbg !13
  store i32 %87, i32* %z__io_349, align 4, !dbg !13
  store i32 3, i32* %.dY0004_396, align 4, !dbg !14
  store i32 1, i32* %i_338, align 4, !dbg !14
  br label %L.LB1_394

L.LB1_394:                                        ; preds = %L.LB1_488, %L.LB1_487
  %88 = bitcast i32* @.C355_main_ to i8*, !dbg !15
  %89 = bitcast [13 x i8]* @.C344_main_ to i8*, !dbg !15
  %90 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !15
  call void (i8*, i8*, i64, ...) %90(i8* %88, i8* %89, i64 13), !dbg !15
  %91 = bitcast i32* @.C347_main_ to i8*, !dbg !15
  %92 = bitcast i32* @.C309_main_ to i8*, !dbg !15
  %93 = bitcast i32* @.C309_main_ to i8*, !dbg !15
  %94 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !15
  %95 = call i32 (i8*, i8*, i8*, i8*, ...) %94(i8* %91, i8* null, i8* %92, i8* %93), !dbg !15
  store i32 %95, i32* %z__io_349, align 4, !dbg !15
  %96 = load i32, i32* %i_338, align 4, !dbg !15
  %97 = sext i32 %96 to i64, !dbg !15
  store i64 %97, i64* %"original_array$ss_369", align 8, !dbg !15
  store i64 3, i64* %.dY0005_399, align 8, !dbg !15
  store i64 1, i64* %"i$a$i_371", align 8, !dbg !15
  br label %L.LB1_397

L.LB1_397:                                        ; preds = %L.LB1_397, %L.LB1_394
  %98 = load i64, i64* %"original_array$ss_369", align 8, !dbg !15
  %99 = load i64, i64* %"i$a$i_371", align 8, !dbg !15
  %100 = mul nsw i64 %99, 3, !dbg !15
  %101 = add nsw i64 %98, %100, !dbg !15
  %102 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !15
  %103 = getelementptr i8, i8* %102, i64 -16, !dbg !15
  %104 = bitcast i8* %103 to float*, !dbg !15
  %105 = getelementptr float, float* %104, i64 %101, !dbg !15
  %106 = load float, float* %105, align 4, !dbg !15
  %107 = load i64, i64* %"i$a$i_371", align 8, !dbg !15
  %108 = bitcast [3 x float]* %"tmp$r_370" to i8*, !dbg !15
  %109 = getelementptr i8, i8* %108, i64 -4, !dbg !15
  %110 = bitcast i8* %109 to float*, !dbg !15
  %111 = getelementptr float, float* %110, i64 %107, !dbg !15
  store float %106, float* %111, align 4, !dbg !15
  %112 = load i64, i64* %"i$a$i_371", align 8, !dbg !15
  %113 = add nsw i64 %112, 1, !dbg !15
  store i64 %113, i64* %"i$a$i_371", align 8, !dbg !15
  %114 = load i64, i64* %.dY0005_399, align 8, !dbg !15
  %115 = sub nsw i64 %114, 1, !dbg !15
  store i64 %115, i64* %.dY0005_399, align 8, !dbg !15
  %116 = load i64, i64* %.dY0005_399, align 8, !dbg !15
  %117 = icmp sgt i64 %116, 0, !dbg !15
  br i1 %117, label %L.LB1_397, label %L.LB1_488, !dbg !15, !llvm.loop !16

L.LB1_488:                                        ; preds = %L.LB1_397
  %118 = bitcast [3 x float]* %"tmp$r_370" to i8*, !dbg !15
  %119 = bitcast [16 x i64]* %"tmp$r$sd4_377" to i8*, !dbg !15
  %120 = bitcast i32 (...)* @ftnio_ldw64 to i32 (i8*, i8*, ...)*, !dbg !15
  %121 = call i32 (i8*, i8*, ...) %120(i8* %118, i8* %119), !dbg !15
  store i32 %121, i32* %z__io_349, align 4, !dbg !15
  %122 = call i32 (...) @f90io_ldw_end(), !dbg !15
  store i32 %122, i32* %z__io_349, align 4, !dbg !15
  %123 = load i32, i32* %i_338, align 4, !dbg !17
  %124 = add nsw i32 %123, 1, !dbg !17
  store i32 %124, i32* %i_338, align 4, !dbg !17
  %125 = load i32, i32* %.dY0004_396, align 4, !dbg !17
  %126 = sub nsw i32 %125, 1, !dbg !17
  store i32 %126, i32* %.dY0004_396, align 4, !dbg !17
  %127 = load i32, i32* %.dY0004_396, align 4, !dbg !17
  %128 = icmp sgt i32 %127, 0, !dbg !17
  br i1 %128, label %L.LB1_394, label %L.LB1_489, !dbg !17, !llvm.loop !18

L.LB1_489:                                        ; preds = %L.LB1_488
  store i64 2, i64* %.dY0006_402, align 8, !dbg !19
  store i64 1, i64* %"i$a_367", align 8, !dbg !19
  br label %L.LB1_400

L.LB1_400:                                        ; preds = %L.LB1_490, %L.LB1_489
  store i64 2, i64* %.dY0007_405, align 8, !dbg !19
  store i64 1, i64* %"i$b_368", align 8, !dbg !19
  br label %L.LB1_403

L.LB1_403:                                        ; preds = %L.LB1_403, %L.LB1_400
  %129 = load i64, i64* %"i$b_368", align 8, !dbg !19
  %130 = load i64, i64* %"i$a_367", align 8, !dbg !19
  %131 = mul nsw i64 %130, 3, !dbg !19
  %132 = add nsw i64 %129, %131, !dbg !19
  %133 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !19
  %134 = getelementptr i8, i8* %133, i64 -4, !dbg !19
  %135 = bitcast i8* %134 to float*, !dbg !19
  %136 = getelementptr float, float* %135, i64 %132, !dbg !19
  %137 = load float, float* %136, align 4, !dbg !19
  %138 = load i64, i64* %"i$b_368", align 8, !dbg !19
  %139 = load i64, i64* %"i$a_367", align 8, !dbg !19
  %140 = load i64, i64* %"i$a_367", align 8, !dbg !19
  %141 = add nsw i64 %139, %140, !dbg !19
  %142 = add nsw i64 %138, %141, !dbg !19
  %143 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !19
  %144 = getelementptr i8, i8* %143, i64 36, !dbg !19
  %145 = bitcast i8* %144 to float*, !dbg !19
  %146 = getelementptr float, float* %145, i64 %142, !dbg !19
  store float %137, float* %146, align 4, !dbg !19
  %147 = load i64, i64* %"i$b_368", align 8, !dbg !19
  %148 = add nsw i64 %147, 1, !dbg !19
  store i64 %148, i64* %"i$b_368", align 8, !dbg !19
  %149 = load i64, i64* %.dY0007_405, align 8, !dbg !19
  %150 = sub nsw i64 %149, 1, !dbg !19
  store i64 %150, i64* %.dY0007_405, align 8, !dbg !19
  %151 = load i64, i64* %.dY0007_405, align 8, !dbg !19
  %152 = icmp sgt i64 %151, 0, !dbg !19
  br i1 %152, label %L.LB1_403, label %L.LB1_490, !dbg !19, !llvm.loop !20

L.LB1_490:                                        ; preds = %L.LB1_403
  %153 = load i64, i64* %"i$a_367", align 8, !dbg !19
  %154 = add nsw i64 %153, 1, !dbg !19
  store i64 %154, i64* %"i$a_367", align 8, !dbg !19
  %155 = load i64, i64* %.dY0006_402, align 8, !dbg !19
  %156 = sub nsw i64 %155, 1, !dbg !19
  store i64 %156, i64* %.dY0006_402, align 8, !dbg !19
  %157 = load i64, i64* %.dY0006_402, align 8, !dbg !19
  %158 = icmp sgt i64 %157, 0, !dbg !19
  br i1 %158, label %L.LB1_400, label %L.LB1_491, !dbg !19, !llvm.loop !21

L.LB1_491:                                        ; preds = %L.LB1_490
  %159 = bitcast i32* @.C357_main_ to i8*, !dbg !22
  %160 = bitcast [13 x i8]* @.C344_main_ to i8*, !dbg !22
  %161 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !22
  call void (i8*, i8*, i64, ...) %161(i8* %159, i8* %160, i64 13), !dbg !22
  %162 = bitcast i32* @.C347_main_ to i8*, !dbg !22
  %163 = bitcast i32* @.C309_main_ to i8*, !dbg !22
  %164 = bitcast i32* @.C309_main_ to i8*, !dbg !22
  %165 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !22
  %166 = call i32 (i8*, i8*, i8*, i8*, ...) %165(i8* %162, i8* null, i8* %163, i8* %164), !dbg !22
  store i32 %166, i32* %z__io_349, align 4, !dbg !22
  %167 = bitcast [13 x i8]* @.C358_main_ to i8*, !dbg !22
  %168 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !22
  %169 = call i32 (i8*, i32, i64, ...) %168(i8* %167, i32 14, i64 13), !dbg !22
  store i32 %169, i32* %z__io_349, align 4, !dbg !22
  %170 = call i32 (...) @f90io_ldw_end(), !dbg !22
  store i32 %170, i32* %z__io_349, align 4, !dbg !22
  store i32 2, i32* %.dY0008_408, align 4, !dbg !23
  store i32 1, i32* %i_338, align 4, !dbg !23
  br label %L.LB1_406

L.LB1_406:                                        ; preds = %L.LB1_492, %L.LB1_491
  %171 = bitcast i32* @.C359_main_ to i8*, !dbg !24
  %172 = bitcast [13 x i8]* @.C344_main_ to i8*, !dbg !24
  %173 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !24
  call void (i8*, i8*, i64, ...) %173(i8* %171, i8* %172, i64 13), !dbg !24
  %174 = bitcast i32* @.C347_main_ to i8*, !dbg !24
  %175 = bitcast i32* @.C309_main_ to i8*, !dbg !24
  %176 = bitcast i32* @.C309_main_ to i8*, !dbg !24
  %177 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !24
  %178 = call i32 (i8*, i8*, i8*, i8*, ...) %177(i8* %174, i8* null, i8* %175, i8* %176), !dbg !24
  store i32 %178, i32* %z__io_349, align 4, !dbg !24
  %179 = load i32, i32* %i_338, align 4, !dbg !24
  %180 = sext i32 %179 to i64, !dbg !24
  store i64 %180, i64* %"sliced_array$ss_372", align 8, !dbg !24
  store i64 2, i64* %.dY0009_411, align 8, !dbg !24
  store i64 1, i64* %"i$a$i2_374", align 8, !dbg !24
  br label %L.LB1_409

L.LB1_409:                                        ; preds = %L.LB1_409, %L.LB1_406
  %181 = load i64, i64* %"sliced_array$ss_372", align 8, !dbg !24
  %182 = load i64, i64* %"i$a$i2_374", align 8, !dbg !24
  %183 = load i64, i64* %"i$a$i2_374", align 8, !dbg !24
  %184 = add nsw i64 %182, %183, !dbg !24
  %185 = add nsw i64 %181, %184, !dbg !24
  %186 = bitcast %struct.BSS1* @.BSS1 to i8*, !dbg !24
  %187 = getelementptr i8, i8* %186, i64 36, !dbg !24
  %188 = bitcast i8* %187 to float*, !dbg !24
  %189 = getelementptr float, float* %188, i64 %185, !dbg !24
  %190 = load float, float* %189, align 4, !dbg !24
  %191 = load i64, i64* %"i$a$i2_374", align 8, !dbg !24
  %192 = bitcast [2 x float]* %"tmp$r1_373" to i8*, !dbg !24
  %193 = getelementptr i8, i8* %192, i64 -4, !dbg !24
  %194 = bitcast i8* %193 to float*, !dbg !24
  %195 = getelementptr float, float* %194, i64 %191, !dbg !24
  store float %190, float* %195, align 4, !dbg !24
  %196 = load i64, i64* %"i$a$i2_374", align 8, !dbg !24
  %197 = add nsw i64 %196, 1, !dbg !24
  store i64 %197, i64* %"i$a$i2_374", align 8, !dbg !24
  %198 = load i64, i64* %.dY0009_411, align 8, !dbg !24
  %199 = sub nsw i64 %198, 1, !dbg !24
  store i64 %199, i64* %.dY0009_411, align 8, !dbg !24
  %200 = load i64, i64* %.dY0009_411, align 8, !dbg !24
  %201 = icmp sgt i64 %200, 0, !dbg !24
  br i1 %201, label %L.LB1_409, label %L.LB1_492, !dbg !24, !llvm.loop !25

L.LB1_492:                                        ; preds = %L.LB1_409
  %202 = bitcast [2 x float]* %"tmp$r1_373" to i8*, !dbg !24
  %203 = bitcast [16 x i64]* %"tmp$r1$sd3_376" to i8*, !dbg !24
  %204 = bitcast i32 (...)* @ftnio_ldw64 to i32 (i8*, i8*, ...)*, !dbg !24
  %205 = call i32 (i8*, i8*, ...) %204(i8* %202, i8* %203), !dbg !24
  store i32 %205, i32* %z__io_349, align 4, !dbg !24
  %206 = call i32 (...) @f90io_ldw_end(), !dbg !24
  store i32 %206, i32* %z__io_349, align 4, !dbg !24
  %207 = load i32, i32* %i_338, align 4, !dbg !26
  %208 = add nsw i32 %207, 1, !dbg !26
  store i32 %208, i32* %i_338, align 4, !dbg !26
  %209 = load i32, i32* %.dY0008_408, align 4, !dbg !26
  %210 = sub nsw i32 %209, 1, !dbg !26
  store i32 %210, i32* %.dY0008_408, align 4, !dbg !26
  %211 = load i32, i32* %.dY0008_408, align 4, !dbg !26
  %212 = icmp sgt i32 %211, 0, !dbg !26
  br i1 %212, label %L.LB1_406, label %L.LB1_493, !dbg !26, !llvm.loop !27

L.LB1_493:                                        ; preds = %L.LB1_492
  %213 = load float, float* %main_329, align 4, !dbg !28
  ret float %213, !dbg !28
}

declare signext i32 @ftnio_ldw64(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

declare void @f90_set_intrin_type_i8(...)

declare void @f90_template1_i8(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm testArray.f90 -S -o test.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "testArray.f90", directory: "/home/zou/Documents/DFIKOS/Fort-test")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 24, column: 1, scope: !5)
!10 = distinct !{!10, !9, !9}
!11 = distinct !{!11, !9, !9}
!12 = distinct !{!12, !9, !9}
!13 = !DILocation(line: 27, column: 1, scope: !5)
!14 = !DILocation(line: 28, column: 1, scope: !5)
!15 = !DILocation(line: 29, column: 1, scope: !5)
!16 = distinct !{!16, !15, !15}
!17 = !DILocation(line: 30, column: 1, scope: !5)
!18 = distinct !{!18, !14, !17}
!19 = !DILocation(line: 33, column: 1, scope: !5)
!20 = distinct !{!20, !19, !19}
!21 = distinct !{!21, !19, !19}
!22 = !DILocation(line: 36, column: 1, scope: !5)
!23 = !DILocation(line: 37, column: 1, scope: !5)
!24 = !DILocation(line: 38, column: 1, scope: !5)
!25 = distinct !{!25, !24, !24}
!26 = !DILocation(line: 39, column: 1, scope: !5)
!27 = distinct !{!27, !23, !26}
!28 = !DILocation(line: 42, column: 1, scope: !5)
