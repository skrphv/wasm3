//
//  m3_info.h
//
//  Created by Steven Massey on 12/6/19.
//  Copyright © 2019 Steven Massey. All rights reserved.
//

#ifndef m3_info_h
#define m3_info_h

#include "m3_compile.h"

d_m3BeginExternC

void            ProfileHit              (cstr_t i_operationName);

#ifdef DEBUG

void            dump_type_stack         (IM3Compilation o);
void            log_opcode              (IM3Compilation o, m3opcode_t i_opcode);
const char *    get_indention_string    (IM3Compilation o);
void            log_emit                (IM3Compilation o, IM3Operation i_operation);

cstr_t          SPrintFuncTypeSignature (IM3FuncType i_funcType);

#else // DEBUG

#define         dump_type_stack(...)      {}
#define         log_opcode(...)           {}
#define         get_indention_string(...) ""
#define         emit_stack_dump(...)      {}
#define         log_emit(...)             {}

#endif // DEBUG


# if d_m3EnableOpProfiling

typedef struct M3ProfilerSlot
{
    cstr_t      opName;
    u64         hitCount;
}
M3ProfilerSlot;

#endif

d_m3EndExternC

#endif // m3_info_h
