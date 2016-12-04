#ifndef MRUBY_SECURE_COMPARE
#define MRUBY_SECURE_COMPARE

#include <mruby.h>

MRB_BEGIN_DECL

MRB_API mrb_bool
mrb_secure_memcmp(const void * const secret_, mrb_int secret_len, const void * const input_, mrb_int input_len);

MRB_END_DECL

#endif
