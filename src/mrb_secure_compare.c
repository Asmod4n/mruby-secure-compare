#include <mruby/secure_compare.h>
#include <mruby/string.h>

#if (__GNUC__ >= 3) || (__INTEL_COMPILER >= 800) || defined(__clang__)
# define likely(x) __builtin_expect(!!(x), 1)
# define unlikely(x) __builtin_expect(!!(x), 0)
#else
# define likely(x) (x)
# define unlikely(x) (x)
#endif

MRB_API mrb_bool
mrb_secure_memcmp(const void * const secret_, mrb_int secret_len, const void * const input_, mrb_int input_len)
{
  const volatile unsigned char *volatile secret =
    (const volatile unsigned char * volatile) secret_;
  const volatile unsigned char *volatile input =
    (const volatile unsigned char * volatile) input_;

  mrb_int input_pos;
  mrb_int result = secret_len - input_len;

  if (unlikely(secret_len == 0 && input_len != 0)) {
    return FALSE;
  }

  for (input_pos = 0; input_pos < input_len; input_pos++) {
    result |= input[input_pos] ^ secret[input_pos % secret_len];
  }

  return result == 0;
}

static mrb_value
mrb_string_securecmp(mrb_state *mrb, mrb_value self)
{
  mrb_value input;

  mrb_get_args(mrb, "S", &input);

  return mrb_bool_value(mrb_secure_memcmp(RSTRING_PTR(self), RSTRING_LEN(self), RSTRING_PTR(input), RSTRING_LEN(input)));
}

void
mrb_mruby_secure_compare_gem_init(mrb_state *mrb)
{
  mrb_define_method(mrb, mrb->string_class, "securecmp", mrb_string_securecmp, MRB_ARGS_REQ(1));
}

void mrb_mruby_secure_compare_gem_final(mrb_state *mrb) {}
