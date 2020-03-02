/* Copyright (C) 2006-2013 Free Software Foundation, Inc.
   Contributed by François-Xavier Coudert

This file is part of the GNU Fortran runtime library (libgfortran).

Libgfortran is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

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

#include "libgfortran.h"

#include <string.h>
#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif

#include <limits.h>

#include "unwind.h"


/* Macros for common sets of capabilities: can we fork and exec, and
   can we use pipes to communicate with the subprocess.  */
#define CAN_FORK (defined(HAVE_FORK) && defined(HAVE_EXECVE) \
		  && defined(HAVE_WAIT))
#define CAN_PIPE (CAN_FORK && defined(HAVE_PIPE) \
		  && defined(HAVE_DUP2) && defined(HAVE_CLOSE))

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


/* GDB style #NUM index for each stack frame.  */

static void 
bt_header (int num)
{
  st_printf ("#%d  ", num);
}


/* fgets()-like function that reads a line from a fd, without
   needing to malloc() a buffer, and does not use locks, hence should
   be async-signal-safe.  */

static char *
fd_gets (char *s, int size, int fd)
{
  for (int i = 0; i < size; i++)
    {
      char c;
      ssize_t nread = read (fd, &c, 1);
      if (nread == 1)
	{
	  s[i] = c;
	  if (c == '\n')
	    {
	      if (i + 1 < size)
		s[i+1] = '\0';
	      else
		s[i] = '\0';
	      break;
	    }
	}
      else
	{
	  s[i] = '\0';
	  if (i == 0)
	    return NULL;
	  break;
	}
    }
  return s;
}


extern char *addr2line_path;

/* Struct containing backtrace state.  */
typedef struct
{
  int frame_number;
  int direct_output;
  int outfd;
  int infd;
  int error;
}
bt_state;

static _Unwind_Reason_Code
trace_function (struct _Unwind_Context *context, void *state_ptr)
{
  
  
  return _URC_NO_REASON;
}


/* Display the backtrace.  */

void
backtrace (void)
{
  
}
iexport(backtrace);
