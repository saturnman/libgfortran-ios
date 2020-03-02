/* FPU-related code for x86 and x86_64 processors.
   Copyright (C) 2005-2013 Free Software Foundation, Inc.
   Contributed by Francois-Xavier Coudert <coudert@clipper.ens.fr>

This file is part of the GNU Fortran 95 runtime library (libgfortran).

Libgfortran is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Libgfortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */



#if defined(__sun__) && defined(__svr4__)
#include <signal.h>
#include <ucontext.h>

static volatile sig_atomic_t sigill_caught;

static void
sigill_hdlr (int sig __attribute((unused)),
	     siginfo_t *sip __attribute__((unused)),
	     ucontext_t *ucp)
{
  sigill_caught = 1;
  /* Set PC to the instruction after the faulting one to skip over it,
     otherwise we enter an infinite loop.  3 is the size of the movaps
     instruction.  */
  ucp->uc_mcontext.gregs[EIP] += 3;
  setcontext (ucp);
}
#endif

static int
has_sse (void)
{
  return 0;
}

/* i387 -- see linux <fpu_control.h> header file for details.  */
#define _FPU_MASK_IM  0x01
#define _FPU_MASK_DM  0x02
#define _FPU_MASK_ZM  0x04
#define _FPU_MASK_OM  0x08
#define _FPU_MASK_UM  0x10
#define _FPU_MASK_PM  0x20
#define _FPU_MASK_ALL 0x3f

#define _FPU_EX_ALL   0x3f

void set_fpu (void)
{
  return;
  
}
