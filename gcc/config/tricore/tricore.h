/*
 * Following are the big TODO list. It's because either the item is too
 * high to consider or IDK at that moment.
 *
 * - 18.2 Compiler driver spec
 *
 *
 *
 *
 */

/* Storage Layout */
#define BITS_BIG_ENDIAN 0
#define BYTES_BIG_ENDIAN 0
#define WORDS_BIG_ENDIAN 0
#define MAX_BITS_PER_WORD 32
#define UNITS_PER_WORD 4
#define POINTER_SIZE 32

#define STRICT_ALIGNMENT 0
#define PARM_BOUNDARY 32
#define FUNCTION_BOUNDARY 32
#define STRUCTURE_SIZE_BOUNDARY 8
#define BIGGEST_ALIGNMENT 32

/* treat pointers and function addresses as integers */
#define FUNCTION_MODE SImode
#define Pmode SImode

/* how many int's are required to hold X number of bytes */
#define TRICORE_NUM_INTS(X) (((X) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

/* how many registers are required to hold a value in the given mode */
#define TRICORE_NUM_REGS(MODE) TRICORE_NUM_INTS(GET_MODE_SIZE(MODE))

/* Basic characteristics of Tricore registers:

   Regno           Name
   0 - 7           d0 - d7         Data registers (lower context)
   8 - 14          d8 - d14        Data registers (upper context)
   15              d15             Implicit data register (upper context). TIN
   16, 17, 24, 25  a0, a1, a8, a9  System global registers (not used by compiler)
   18 - 23         a2 - a7         Address registers (lower context)
   26              a10             Stack pointer (upper context)
   27              a11             Return address register (both context)
   28 - 30         a12 - a14       Address registers (upper context)
   31              a15             Implicit base address register (upper context)
   32 - 39         e0 - e14        64 bit data registers
   40 - 47         p0 - p14        64 bit address registers
   48                              First pseudo register

   Upper context registers are automatically saved to Context Save Area (CSA)
   during interrupt, trap and function call. Lower context can be used with the
   help of TODO : Finish this text
*/

#define FIRST_PSEUDO_REGISTER 48
#define FIXED_REGISTERS							\
{									\
  /* Data registers  */							\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  /* Address registers */						\
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,			\
  /* 64bit data registers */						\
  0, 0, 0, 0, 0, 0, 0, 0,						\
  /* 64bit address registers */						\
  1, 0, 0, 0, 1, 1, 0, 0						\
}

/* TODO system global registers */
#define CALL_REALLY_USED_REGISTERS					\
{									\
  /* Data registers.  */						\
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* Address registers */						\
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* 64bit data registers */						\
  0, 0, 0, 0, 1, 1, 1, 1,						\
  /* 64bit address registers */						\
  1, 0, 0, 0, 1, 1, 1, 1						\
}

#define REG_ALLOC_ORDER							\
{									\
  /* caller saved registers */						\
  8, 9, 10, 11, 12, 13, 14, 15, 28, 29, 29, 30, 31, 36, 37, 38, 39,	\
  46, 47,								\
  /* callee saved registers */						\
  0, 1,	32, 42, 43,							\
  /* d4 - d7 & a4 - a7 argument passing */				\
  4, 5, 6, 7, 20, 21, 22, 23, 34, 35,					\
  /* a2, a3, d2, d3 - function return value */				\
  2, 3,	18, 19,	33, 41,							\
  /* a10 - sp & a11 - ra */						\
  26, 27, 45 								\
}

#define REGISTER_NAMES							\
{									\
  "d0", "d1",  "d2",   "d3",  "d4",  "d5",  "d6",  "d7",		\
  "d8", "d9",  "d10",  "d11", "d12", "d13", "d14", "d15",		\
  "a0", "a1",  "a2",   "a3",  "a4",  "a5",  "a6",  "a7",		\
  "a8", "a9",  "a10",  "a11", "a12", "a13", "a14", "a15",		\
  "e0", "e2",  "e4",   "e6",  "e8",  "e10", "e12", "e14",		\
  "p0", "p2",  "p4",   "p6",  "p8",  "p10", "p12", "p14"		\
}

enum reg_class
{
  NO_REGS,		/* no registers in set */
  DATA_REGS,		/* data registers */
  EXTENDED_DATA_REGS,	/* extended data registers */
  ADDR_REGS,		/* address registers */
  EXTENDED_ADDR_REGS,	/* extended address registers */
  GENERAL_REGS,		/* address + data registers */
  EXTENDED_GENERAL_REGS,/* extended address + data registers */
  SP_REGS,		/* stack pointer only */
  ALL_REGS,		/* all registers */
  LIM_REG_CLASSES	/* max value + 1 */
};

#define N_REG_CLASSES (int) LIM_REG_CLASSES

#define REG_CLASS_NAMES							\
{									\
  "NO_REGS",								\
  "DATA_REGS",								\
  "EXTENDED_DATA_REGS",							\
  "ADDR_REGS",								\
  "EXTENDED_ADDR_REGS",							\
  "GENERAL_REGS",							\
  "EXTENDED_GENERAL_REGS",						\
  "SP_REGS",								\
  "ALL_REGS",								\
  "LIM_REG_CLASSES"							\
}

#define REG_CLASS_CONTENTS						\
{									\
  { 0x00000000, 0x00000000 },						\
  { 0x0000ffff, 0x00000000 },						\
  { 0x00000000, 0x000000ff },						\
  { 0xffff0000, 0x00000000 },						\
  { 0x00000000, 0x0000ff00 },						\
  { 0xffffffff, 0x00000000 },						\
  { 0x00000000, 0x0000ffff },						\
  { 0x00000400, 0x00000000 },						\
  { 0xffffffff, 0x0000ffff },						\
}

#define REGNO_REG_CLASS(REGNO) tricore_regno_to_class(REGNO)
#define REGNO_OK_FOR_BASE_P(REGNO) tricore_valid_regno_for_base_p(REGNO)
#define REGNO_OK_FOR_INDEX_P(REGNO) tricore_valid_regno_for_index_p(REGNO)

#define BASE_REG_CLASS reg_class::GENERAL_REGS
#define INDEX_REG_CLASS reg_class::GENERAL_REGS

#define FIRST_ARG_REGNUM 4
#define LAST_ARG_REGNUM 7
#define FIRST_ASM_REGNUM 4
#define LAST_ASM_REGNUM 7
#define FIRST_CALLEE_SAVED_REGNUM 0
#define LAST_CALLEE_SAVED_REGNUM 7
#define STACK_POINTER_REGNUM 26
#define FRAME_POINTER_REGNUM 28
#define FIRST_RETVAL_REGNUM 2
#define RET_VALUE_REGNUM 2
#define RET_ADDRESS_REGNUM 18
#define MAX_REGS_PER_ADDRESS 1
#define ARG_POINTER_REGNUM FRAME_POINTER_REGNUM
#define NUM_ARG_REGISTERS LAST_ARG_REGNUM

#define ELIMINABLE_REGS {{ FRAME_POINTER_REGNUM }}
#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET) \
  (OFFSET) = tricore_initial_elimination_offset((FROM), (TO))

/******************************************************************************/
/* Memory, stack, function args                                               */
/******************************************************************************/

#define MOVE_MAX 4
#define SLOW_BYTE_ACCESS 0
#define PUSH_ARGS 0
#define ACCUMULATE_OUTGOING_ARGS 1
#define STACK_BOUNDARY 32
#define STACK_GROWS_DOWNWARD 1
#define FRAME_GROWS_DOWNWARD 1
#define STACK_POINTER_OFFSET -8
#define EXIT_IGNORE_STACK 1
#define MAX_ARGS_IN_REGISTERS 6

/* cumulative argument info */
typedef struct
{
  int num_reg_args;
  int num_args;
} tricore_cumulative_arg_info;

#define CUMULATIVE_ARGS tricore_cumulative_arg_info

/* init cumulative args */
#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS)     \
  tricore_init_cumulative_args(&CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS);

/* misc. function stuff */
#define FUNCTION_ARG_REGNO_P(N)                                                \
  ((N >= FIRST_ARG_REGNUM) && (N <= LAST_ARG_REGNUM))

#define FIRST_PARM_OFFSET(FNDECL) 0

/******************************************************************************/
/* Misc.                                                                      */
/******************************************************************************/

#define DEFAULT_SIGNED_CHAR 1

/* for nested functions only */
#define TRAMPOLINE_SIZE 64
#define TRAMPOLINE_ALIGNMENT 32

/* treat 'case' labels as integers */
#define CASE_VECTOR_MODE SImode

/* no profiler support yet */
#define FUNCTION_PROFILER(FILE, LABELNO)                                       \
  do {                                                                         \
  } while(0)

/* Run-time Target Specification */
#define TARGET_CPU_CPP_BUILTINS()                                              \
  do {                                                                         \
    builtin_assert ("cpu=tricore");                                              \
    builtin_assert ("machine=tricore");                                          \
    builtin_define ("__tricore__");                                              \
    builtin_define ("__TRICORE__");                                              \
    builtin_define ("__TRICORE_SOFT_FLOAT__");                                   \
  } while (0)

/******************************************************************************/
/* Assembler                                                                  */ 
/******************************************************************************/

/* how to output alignment directives */
#define ASM_OUTPUT_ALIGN(STREAM, LOG)                                          \
  do {                                                                         \
    if (LOG != 0)                                                              \
      fprintf (STREAM, "\t.align\t%d\n", 1 << (LOG));                          \
  } while (0)

/* not entirely sure about the following directives since missing in my
   docs. Thus, guessing here */
#define ASM_APP_ON "#APP\n"
#define ASM_APP_OFF "#NO_APP\n"

#define TEXT_SECTION_ASM_OP "\t.code"
#define DATA_SECTION_ASM_OP "\t.data"

#define BSS_SECTION_ASM_OP "\t.bss"

#undef GLOBAL_ASM_OP
#define GLOBAL_ASM_OP "\t.global\t"
