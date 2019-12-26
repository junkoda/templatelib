#
# $ make
#

from setuptools import setup, Extension
import numpy as np
import os

# Remember this directory as _dir
path, _ = os.path.split(os.path.abspath(__file__))
libroot = os.path.abspath(os.path.join(path, '..', '..'))

with open('templatelib/config.py', 'w') as f:
    f.write("_dir = '%s'\n" % libroot)


# Remove the "-Wstrict-prototypes" compiler option, which isn't valid for C++.
# https://stackoverflow.com/questions/8106258
import distutils.sysconfig
cfg_vars = distutils.sysconfig.get_config_vars()
for key, value in cfg_vars.items():
    if type(value) == str:
        cfg_vars[key] = value.replace('-Wstrict-prototypes', '').replace('-g', '').replace('-DNDEBUG', '')

setup(name='templatelib',
      version='0.0.1',
      author='Jun Koda',
      py_modules=['templatelib.config',
                  'templatelib.hello',
      ],
      ext_modules=[
          Extension('templatelib._templatelib',
                    ['py_package.cpp',                     
                     'np_array.cpp',
                     'py_examples.cpp',
                    ],
                    depends = ['np_array.h',
                               'buffer.h',
                               'error.h',
                               'py_examples.h',
                    ],
                    extra_compile_args = ['-std=c++11'],
                    include_dirs = [np.get_include(), ],
                    #libraries = ['gsl', 'gslcblas'],
          )
      ],
      packages=['templatelib'],
      url='https://github.com/junkoda/templatelib',
      license = "MIT",
)
