/* Copyright (C) 2002-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include "pthreadP.h"
#include <shlib-compat.h>

int
__pthread_tryjoin_np (pthread_t threadid, void **thread_return)
{
  /* Return right away if the thread hasn't terminated yet.  */
  struct pthread *pd = (struct pthread *) threadid;
  if (pd->tid != 0)
    return EBUSY;

  /* If pd->tid == 0 then lll_wait_tid will not block on futex
     operation.  */
  return __pthread_clockjoin_ex (threadid, thread_return, 0 /* Ignored */,
				 NULL, false);
}
versioned_symbol (libc, __pthread_tryjoin_np, pthread_tryjoin_np, GLIBC_2_34);

#if OTHER_SHLIB_COMPAT (libpthread, GLIBC_2_3_3, GLIBC_2_34)
compat_symbol (libc, __pthread_tryjoin_np, pthread_tryjoin_np, GLIBC_2_3_3);
#endif
