#!/usr/bin/env python
# To use:
#       python setup.py install
#

__version__ = "$FreeBSD: head/databases/py-gdbm/files/setup3.py 340872 2014-01-24 00:14:07Z mat $"

try:
    import distutils
    from distutils import sysconfig
    from distutils.command.install import install
    from distutils.core import setup, Extension
except:
    raise SystemExit("Distutils problem")

install.sub_commands = [x for x in install.sub_commands if 'egg' not in x[0]]

prefix = sysconfig.PREFIX
inc_dirs = [prefix + "/include"]
lib_dirs = [prefix + "/lib"]
libs = ["gdbm"]

setup(name = "gdbm",
      description = "GDBM Extension to Python",

      ext_modules = [Extension('gdbm', ['_gdbmmodule.c'],
                               include_dirs = inc_dirs,
                               libraries = libs,
                               library_dirs = lib_dirs)]
      )
