#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "gimple.h"
#include "cfghooks.h"
#include "df.h"
#include "memmodel.h"
#include "tm_p.h"
#include "stringpool.h"
#include "attribs.h"
#include "optabs.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "cfgrtl.h"
#include "output.h"
#include "calls.h"
#include "alias.h"
#include "explow.h"
#include "expr.h"
#include "reload.h"
#include "langhooks.h"
#include "gimplify.h"
#include "builtins.h"
#include "dumpfile.h"
#include "hw-doloop.h"
#include "rtl-iter.h"
#include "tm-constrs.h"

/* NOTE, this file has to be included after the generic ones above */
#include "target-def.h"

/* NOTE, we also need to provide a struct for machine functions, the
   compilation breaks without it */
struct GTY(()) machine_function
{
  int reg_val;
};

struct gcc_target targetm = TARGET_INITIALIZER;

/******************************************************************************/
/* Since a register can generally belong to more than just one class, we
   specify the smallest one */

enum reg_class tricore_regno_to_class (int regno)
{
  if (regno >= 0 && regno < FIRST_PSEUDO_REGISTER)
  {
    if (regno == STACK_POINTER_REGNUM)
      return reg_class::SP_REGS;
    else if (regno == FRAME_POINTER_REGNUM)
      return reg_class::SP_REGS; // FIXME hack
    else return reg_class::GENERAL_REGS;
  }

  return reg_class::NO_REGS;
}

/******************************************************************************/
/* Memory can be addressed by having an arbitrary base register, thus, no
   restrictions */

int tricore_valid_regno_for_base_p(int regno)
{
  /* physical registers only, virtual registers make
     actually no sense here */
  if (regno >= 0 && regno < FIRST_PSEUDO_REGISTER)
  {
    return 1;
  }

  return 0;
}

/******************************************************************************/
/* The same as for address base registers applies to index registers, no
   restrictions */

int tricore_valid_regno_for_index_p(int regno)
{
  return tricore_valid_regno_for_base_p(regno);
}

/******************************************************************************/
/* If frame register elimination is supported/desired, compute the initial
   elimination offset */

HOST_WIDE_INT tricore_initial_elimination_offset (int from,
                                                int to ATTRIBUTE_UNUSED)
{
  return 0;
}

/******************************************************************************/
/* Init cumulative arguments for a function call */

void tricore_init_cumulative_args(CUMULATIVE_ARGS *cum,
                                tree fntype ATTRIBUTE_UNUSED,
                                rtx libname ATTRIBUTE_UNUSED,
                                tree fndecl ATTRIBUTE_UNUSED,
                                int num_named ATTRIBUTE_UNUSED)
{
  return;
}

/* NOTE, this file is auto-generated in build/gcc and needs to be (if at all)
   included at the end of this file */
#include "gt-tricore.h"
