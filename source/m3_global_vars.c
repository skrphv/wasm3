//
//  m3_global_vars.c
//
//  Created by PhSkr on 11/8/21.
//  Copyright © 2021 PhSkr. All rights reserved.
//

#include "m3_global_vars.h"

void m3_save_global_vars(M3GlobalVariables* globals)
{
    if (!globals) {
        return;
    }

    //From m3_api_uvwasi.c
    #if defined(d_m3HasUVWASI)
        //#if !defined(__APPLE__) && !(_MSC_VER)
        //    extern char** environ;
        //    globals->environ = environ;
        //#endif
        extern m3_wasi_context_t* wasi_context;
        globals->wasi_context = wasi_context;

        extern uvwasi_t uvwasi;
        memcpy(&globals->uvwasi, &uvwasi, sizeof(uvwasi_t));
    #endif

    //From m3_api_wasi.c
    #if defined(d_m3HasWASI)
        extern m3_wasi_context_t* wasi_context;
        globals->wasi_context = wasi_context;

        extern Preopen preopen[PREOPEN_CNT];
        memcpy(globals->preopen, preopen, sizeof(Preopen) * PREOPEN_CNT);
    #endif

    //From m3_api_meta_wasi.c
    #if defined(d_m3HasMetaWASI)
        extern m3_wasi_context_t* wasi_context;
        globals->wasi_context = wasi_context;
    #endif

    //From m3_api_tracer.c
    #if defined(d_m3HasTracer)
        extern FILE* trace;
        globals->trace = trace;
    #endif

    //From m3_core.c
    #if d_m3LogTimestamps
        extern uint64_t initial_ts;
        globals->initial_ts = initial_ts;
    #endif
    #if d_m3FixedHeap
        extern u8 fixedHeap[d_m3FixedHeap];
        extern u8* fixedHeapPtr;
        extern u8* fixedHeapEnd;
        extern u8* fixedHeapLast;

        memcpy(globals->fixedHeap, d_m3FixedHeap, d_m3FixedHeap);
        globals->fixedHeapPtr = fixedHeapPtr;
        globals->fixedHeapEnd = fixedHeapEnd;
        globals->fixedHeapLast = fixedHeapLast;
    #endif
    #if d_m3LogNativeStack
        extern size_t stack_start;
        extern size_t stack_end;
        globals->stack_start = stack_start;
        globals->stack_end = stack_end;
    #endif

    //From m3_info.c
    #if d_m3EnableOpProfiling
        extern M3ProfilerSlot s_opProfilerCounts [d_m3ProfilerSlotMask + 1];
        memcpy(globals->s_opProfilerCounts, s_opProfilerCounts, sizeof(M3ProfilerSlot) * (d_m3ProfilerSlotMask + 1));
    #endif

    extern char SPrintFuncTypeSignature_string [256];
    memcpy(globals->SPrintFuncTypeSignature_string, SPrintFuncTypeSignature_string, sizeof(SPrintFuncTypeSignature_string));

    extern char SPrintValue_string [100];
    memcpy(globals->SPrintValue_string, SPrintValue_string, sizeof(SPrintValue_string));

    extern char SPrintFunctionArgList_string [256];
    memcpy(globals->SPrintFunctionArgList_string, SPrintFunctionArgList_string, sizeof(SPrintFunctionArgList_string));

    //From m3_code.c
    extern u32 new_code_page_sequence;
    globals->new_code_page_sequence = new_code_page_sequence;

    //From m3_env.c
    #if defined(d_m3PreferStaticAlloc)
        extern M3Runtime EvaluateExpression_runtime;
        memcpy(&globals->EvaluateExpression_runtime, &EvaluateExpression_runtime, sizeof(M3Runtime));
    #endif

    //From m3_parse.c
    #if defined(d_m3PreferStaticAlloc)
        extern M3Compilation Parse_InitExpr_compilation;
        memcpy(&globals->Parse_InitExpr_compilation, &Parse_InitExpr_compilation, sizeof(M3Compilation));
    #endif
}

void m3_restore_global_vars(M3GlobalVariables* globals)
{
    if (!globals) {
        return;
    }

    //From m3_api_uvwasi.c
    #if defined(d_m3HasUVWASI)
        //#if !defined(__APPLE__) && !(_MSC_VER)
        //    extern char** environ;
        //    environ = globals->environ;
        //#endif
        extern m3_wasi_context_t* wasi_context;
        wasi_context = globals->wasi_context;

        extern uvwasi_t uvwasi;
        memcpy(&uvwasi, &globals->uvwasi, sizeof(uvwasi_t));
    #endif

    //From m3_api_wasi.c
    #if defined(d_m3HasWASI)
        extern m3_wasi_context_t* wasi_context;
        wasi_context = globals->wasi_context;

        extern Preopen preopen[PREOPEN_CNT];
        memcpy(preopen, globals->preopen, sizeof(Preopen) * PREOPEN_CNT);
    #endif

    //From m3_api_meta_wasi.c
    #if defined(d_m3HasMetaWASI)
        extern m3_wasi_context_t* wasi_context;
        wasi_context = globals->wasi_context;
    #endif

    //From m3_api_tracer.c
    #if defined(d_m3HasTracer)
        extern FILE* trace;
        trace = globals->trace;
    #endif

    //From m3_core.c
    #if d_m3LogTimestamps
        extern uint64_t initial_ts;
        initial_ts = globals->initial_ts;
    #endif
    #if d_m3FixedHeap
        extern u8 fixedHeap[d_m3FixedHeap];
        memcpy(fixedHeap, globals->fixedHeap, d_m3FixedHeap);

        extern u8* fixedHeapPtr;
        fixedHeapPtr = globals->fixedHeapPtr;

        extern u8* fixedHeapEnd;
        fixedHeapEnd = globals->fixedHeapEnd;

        extern u8* fixedHeapLast;
        fixedHeapLast = globals->fixedHeapLast;
    #endif
    #if d_m3LogNativeStack
        extern size_t stack_start;
        stack_start = globals->stack_start;

        extern size_t stack_end;
        stack_end = globals->stack_end;
    #endif

    //From m3_info.c
    #if d_m3EnableOpProfiling
        extern M3ProfilerSlot s_opProfilerCounts [d_m3ProfilerSlotMask + 1];
        memcpy(s_opProfilerCounts, globals->s_opProfilerCounts, sizeof(M3ProfilerSlot) * (d_m3ProfilerSlotMask + 1));
    #endif
    extern char SPrintFuncTypeSignature_string [256];
    memcpy(SPrintFuncTypeSignature_string, globals->SPrintFuncTypeSignature_string, sizeof(SPrintFuncTypeSignature_string));

    extern char SPrintValue_string [100];
    memcpy(SPrintValue_string, globals->SPrintValue_string, sizeof(SPrintValue_string));

    extern char SPrintFunctionArgList_string [256];
    memcpy(SPrintFunctionArgList_string, globals->SPrintFunctionArgList_string, sizeof(SPrintFunctionArgList_string));

    //From m3_code.c
    extern u32 new_code_page_sequence;
    new_code_page_sequence = globals->new_code_page_sequence;

    //From m3_env.c
    #if defined(d_m3PreferStaticAlloc)
        extern M3Runtime EvaluateExpression_runtime;
        memcpy(&EvaluateExpression_runtime, &globals->EvaluateExpression_runtime, sizeof(M3Runtime));
    #endif

    //From m3_parse.c
    #if defined(d_m3PreferStaticAlloc)
        extern M3Compilation Parse_InitExpr_compilation;
        memcpy(&Parse_InitExpr_compilation, &globals->Parse_InitExpr_compilation, sizeof(M3Compilation));
    #endif
}
