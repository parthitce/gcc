#ifndef __TRICORE_PROTOS_H__
#define __TRICORE_PROTOS_H__

extern enum reg_class tricore_regno_to_class(int);
extern int tricore_valid_regno_for_base_p(int);
extern int tricore_valid_regno_for_index_p(int);

extern void tricore_init_cumulative_args(CUMULATIVE_ARGS *ca,
                                       tree fn_type,
                                       rtx libname,
                                       tree fn_decl,
                                       int num_named);

extern HOST_WIDE_INT tricore_initial_elimination_offset(int, int);

#endif /* __TRICORE_PROTOS_H__ */

