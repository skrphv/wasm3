//
//  m3_global_vars.h
//
//  Created by PhSkr on 11/8/21.
//  Copyright © 2021 PhSkr. All rights reserved.
//

#ifndef m3_global_vars_h
#define m3_global_vars_h

#include "m3_core.h"
#include "m3_config.h"
#include "m3_info.h"
#include "m3_env.h"
#include "m3_compile.h"

#if defined(d_m3HasWASI) || defined(d_m3HasUVWASI) || defined(d_m3HasMetaWASI)
#include "m3_api_wasi.h"
#endif


// Notes: 
// 1) This struct is used to save / restore all global (M3_GLOBAL_VAR,
//    M3_GLOBAL_VAR_STATIC) variables. This is needed when you use different
//    instances of wasm3 interperter in one project
// 2) It is not neccessaty to save
//    M3_GLOBAL_VAR_CONST,
//    M3_GLOBAL_VAR_STATIC_CONST,
//    M3_GLOBAL_VAR_CONST_PTR,
//    M3_GLOBAL_VAR_STATIC_CONST_PTR 
//    M3_LOCAL_VAR_STATIC_CONST,
//    M3_LOCAL_VAR_STATIC_CONST_PTR
//    cause they are const


typedef struct M3GlobalVariables
{
    //From m3_api_uvwasi.c
    #if defined(d_m3HasUVWASI)
        //#if !defined(__APPLE__) && !(_MSC_VER)
        //    char** environ;
        //#endif
        m3_wasi_context_t* wasi_context;
        uvwasi_t uvwasi;
    #endif

    //From m3_api_wasi.c
    #if defined(d_m3HasWASI)
        m3_wasi_context_t* wasi_context;
        Preopen preopen[PREOPEN_CNT];
    #endif

    //From m3_api_meta_wasi.c
    #if defined(d_m3HasMetaWASI)
        m3_wasi_context_t* wasi_context;
    #endif

    //From m3_api_tracer.c
    #if defined(d_m3HasTracer)
        FILE* trace;
    #endif

    //From m3_core.c
    #if d_m3LogTimestamps
        uint64_t initial_ts;
    #endif
    #if d_m3FixedHeap
        u8 fixedHeap[d_m3FixedHeap];
        u8* fixedHeapPtr;
        u8* fixedHeapEnd;
        u8* fixedHeapLast;
    #endif
    #if d_m3LogNativeStack
        size_t stack_start;
        size_t stack_end;
    #endif

    //From m3_info.c
    #if d_m3EnableOpProfiling
        M3ProfilerSlot s_opProfilerCounts [d_m3ProfilerSlotMask + 1];
    #endif
    char SPrintFuncTypeSignature_string [256];
    char SPrintValue_string [100];
    char SPrintFunctionArgList_string [256];

    //From m3_code.c
    u32 new_code_page_sequence;

    //From m3_env.c
    #if defined(d_m3PreferStaticAlloc)
        M3Runtime EvaluateExpression_runtime;
    #endif

    //From m3_parse.c
    #if defined(d_m3PreferStaticAlloc)
        M3Compilation Parse_InitExpr_compilation;
    #endif
}
M3GlobalVariables;


#endif // m3_global_vars_h
