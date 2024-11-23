# mruby-secure-compare
**Secure String comparisons for mruby**

## Examples
**Always use the secret as the first argument.**

C Example

```c
#include <mruby/secure_compare.h>
#include <mruby/string.h>

mrb_value secret = mrb_str_new_lit(mrb, "hallo");
mrb_value input = mrb_str_new_lit(mrb, "hallo");

if (mrb_secure_memcmp(RSTRING_PTR(secret), RSTRING_LEN(secret), RSTRING_PTR(input), RSTRING_LEN(input))) {
  puts("access granted");
}
```

Ruby Example

```ruby
my_super_secure_secret = "hallo"
user_input = "hallo"
if my_super_secure_secret.securecmp(user_input)
  puts "access granted"
end
```

This gem provides a simple, fast way to do string comparisons that resist timing attacks.

## What is a timing attack?
A timing attack is an attack on a system that determines secret information based on how long an operation takes.

Timing attacks are particularly prevalent (and dangerous) in cryptographic operations, but they can also sneak into other types of operation.

In particular, any time you are comparing user-specified input with a secret, you should consider whether or not you are exposing yourself to a timing attack.

The attack is probably best described by [Nate Lawson](http://rdist.root.org/2010/07/19/exploiting-remote-timing-attacks/):

> "The attack is very simple. You repeatedly send guesses about a secret value to the server, which rejects them as incorrect. However, if your first byte of the guess is correct, it takes a very slightly longer time to return the error. With many measurements and some filtering, you can distinguish this difference."

Therefore, it's important that the amount of time these operations take depends only on the length of the user's input, and not on any characteristic of the secret data.

## How does this gem help? Why should I use it rather than rolling my own?
This gem provides a secure comparison function that is:
- **Very simple**: Adds one method to the String class, also exports the C function for other gems to use.
- **Fast**: It uses a C back-end rather than a pure Ruby implementation.
- **Portable**: The C code is platform-independent.

Furthermore, unlike some other secure comparison functions, the code does not require that the strings are the same length, and should not leak the length of the string if the string lengths do not match.

## Is there anything else I should know?
- The gem is **not foolproof**. In particular, it can't protect you against anything designed to exploit cache misses or any other more elaborate form of timing attack. However, none of the existing pure Ruby secure_compare functions do either.
- **Argument Order**: Putting the arguments around the wrong way may leak the length of your secret.
- **Length of Secret**: Don't use a secret of length 0.
