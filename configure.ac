#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([gtkmmorse], [0.9.21], [Giuseppe Martino denever@users.sf.net])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
#AC_PROG_RANLIB

# Checks for header files.
AC_HEADER_STDC	    

# Checks for libraries: libao, libgtkmm, libgconfmm, libgthread

PKG_CHECK_MODULES([AO], [ao >= 0.8])
PKG_CHECK_MODULES([GTKMM], [gtkmm-2.4 >= 2.4])
PKG_CHECK_MODULES([GCONFMM], [gconfmm-2.6 >= 2.6])
PKG_CHECK_MODULES([GTHREAD], [gthread-2.0 >= 2.0])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
#AC_PROG_GCC_TRADITIONAL
#AC_CHECK_FUNCS([floor])

AC_SUBST(AO_LIBS)
AC_SUBST(GTKMM_LIBS)
AC_SUBST(GTHREAD_LIBS)

AC_SUBST(AO_CFLAGS)
AC_SUBST(GTKMM_CFLAGS)
AC_SUBST(GTHREAD_CFLAGS)


AC_CONFIG_FILES([Makefile
		 include/Makefile
                 src/Makefile])
AC_OUTPUT
