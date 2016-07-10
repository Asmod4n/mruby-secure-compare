#ifndef MRUBY_SECURE_COMPARE
#define MRUBY_SECURE_COMPARE

#ifdef __cplusplus
#extern "C" {
#endif

#include <mruby.h>

MRB_API mrb_bool
mrb_secure_memcmp(const void * const secret_, mrb_int secret_len, const void * const input_, mrb_int input_len);

#ifdef __cplusplus
}
#endif

#endif
