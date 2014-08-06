
# Fun JIT tests

Trying out GNU lightning, libffi, and libjit for.. fun purposes.

Built on OSX with homebrew packages, except for libjit, cloned directly
from savannah and installed in local subfolder './prefix'

Homebrew is weird with libffi, apparently it's keg-local and not installed
to /usr/local directly - hence the weird little shell dance to find the
right folder. Feel free to replace FFI_FLAGS with anything fitting on
your platform.


