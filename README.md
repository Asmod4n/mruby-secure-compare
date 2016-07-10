# mruby-secure-compare
Secure String comparisons for mruby

```c
#include <mruby/secure_compare.h>
#include <mruby/string.h>

if (mrb_secure_memcmp(RSTRING_PTR(secret), RSTRING_LEN(secret_len), RSTRING_PTR(input), RSTRING_LEN(input))) {
  puts ("access granted");
}
```

```ruby
if "hallo".securecmp("hallo")
  puts "access granted"
end
```

This gem provides a simple, fast way to do string comparisons that resist timing attacks.

# What is a timing attack? #
A timing attack is an attack on a system that determines secret information based on how long an operation takes.

Timing attacks are particularly prevalent (and dangerous) in cryptographic operations, but they can also sneak into other types of operation.

In particular, any time you are **comparing user specified input with a secret**, you should consider whether or not you are exposing yourself to a timing attack.

The attack is probably best described by [Nate Lawson](http://rdist.root.org/2010/07/19/exploiting-remote-timing-attacks/):

> The attack is very simple. You repeatedly send guesses about a secret value to the server, which rejects them as incorrect. However, if your first byte of the guess is correct, it takes a very slightly longer time to return the error. With many measurements and some filtering, you can distinguish this difference.

Therefore, it's important that the amount of time these operations take depends *only* on the length of the user's input, and *not* on any characteristic of the secret data.

# How does this gem help? Why should I use it rather than rolling my own? #

This gem provides a secure comparison function that is:

 - very simple: adds one method to the String class, also exports the c function for other gems to use.
 - fast: it uses a C back-end rather than a pure Ruby implementation.
 - portable: the C code is platform independent

Furthermore, unlike some other secure comparison fuctions, the code does not require that the strings are the same length, and should not leak the length of the string if the string lengths do not match.


# Is there anything else I should know? #

* The gem is not foolproof. In particular, it can't protect you against anything designed to exploit cache misses or any other more elaborate form of timing attack. However, none of the existing pure Ruby secure_compare functions do either.

* Putting the argmuents around the wrong way may leak the length of your secret.

* Don't use a secret of length 0.

License
=======

Copyright 2016 Hendrik Beskow

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this project except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Acknowledgements
================

This is using a variation from sodium_memcmp from libsodium (https://github.com/jedisct1/libsodium)

/*
 * ISC License
 *
 * Copyright (c) 2013-2016
 * Frank Denis <j at pureftpd dot org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

 It is also influenced by fast_secure_compare from https://github.com/daxtens/fast_secure_compare

 Copyright (c) 2014 Daniel Axtens

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
