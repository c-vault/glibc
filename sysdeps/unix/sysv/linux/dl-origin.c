/* Find path of executable.
   Copyright (C) 1998-2025 Free Software Foundation, Inc.
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

#include <assert.h>
#include <dl-dst.h>
#include <fcntl.h>
#include <ldsodefs.h>
#include <sysdep.h>
#include <fd_to_filename.h>

/* On Linux >= 2.1 systems which have the dcache implementation we can get
   the path of the application from the /proc/self/exe symlink.  Try this
   first and fall back on the generic method if necessary.  */

const char *
_dl_get_origin (void)
{
  char linkval[PATH_MAX];
  char *result;
  int len;

  len = INTERNAL_SYSCALL_CALL (readlinkat, AT_FDCWD, "/proc/self/exe",
			       linkval, sizeof (linkval));
  if (len > 0 && linkval[0] != '[')
    {
      /* We can use this value.  */
      assert (linkval[0] == '/');
      while (len > 1 && linkval[len - 1] != '/')
	--len;
      result = (char *) malloc (len + 1);
      if (result == NULL)
	result = (char *) -1;
      else if (len == 1)
	memcpy (result, "/", 2);
      else
	*((char *) __mempcpy (result, linkval, len - 1)) = '\0';
    }
  else
    {
      result = (char *) -1;
      /* We use the environment variable LD_ORIGIN_PATH.  If it is set make
	 a copy and strip out trailing slashes.  */
      if (GLRO(dl_origin_path) != NULL)
	{
	  size_t len = strlen (GLRO(dl_origin_path));
	  result = (char *) malloc (len + 1);
	  if (result == NULL)
	    result = (char *) -1;
	  else
	    {
	      char *cp = __mempcpy (result, GLRO(dl_origin_path), len);
	      while (cp > result + 1 && cp[-1] == '/')
		--cp;
	      *cp = '\0';
	    }
	}
    }

  return result;
}

/* On Linux, readlink on the magic symlinks in /proc/self/fd also has
   the same behavior of returning the canonical path from the dcache.
   If it does not work, we do not bother to canonicalize. */

char *
_dl_canonicalize (int fd)
{
  struct fd_to_filename fdfilename;
  char canonical[PATH_MAX];
  char *path = __fd_to_filename (fd, &fdfilename);
  int size = INTERNAL_SYSCALL_CALL (readlinkat, AT_FDCWD, path,
                                    canonical, PATH_MAX - 1);

  /* Check if the path was truncated.  */
  if (size >= 0 && size < PATH_MAX - 1)
    {
      canonical[size] = '\0';
      return __strdup (canonical);
    }
  return NULL;
}
