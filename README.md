
# Fun JIT tests

Trying out GNU lightning, libffi, and libjit for.. fun purposes.

Built on OSX with homebrew packages, except for libjit, cloned directly
from savannah and installed in local subfolder './prefix'

Homebrew is weird with libffi, apparently it's keg-local and not installed
to /usr/local directly - hence the weird little shell dance to find the
right folder. Feel free to replace FFI_FLAGS with anything fitting on
your platform.

## libjit notes

libjit's dynlib stuff uses discouraged OSX-specific stuff instead of
the 'Dynamic Loader Compatibility Functions' described at:
<https://developer.apple.com/library/mac/documentation/DeveloperTools/Reference/MachOReference/Reference/reference.html> (which is the standard dlopen/dlsym/dlclose unixy
stuff).

As a result, `jit_dynlib_open(NULL)` on OSX with vanilla libjit will
crash into oblivion - disabling the OSX codepath with an `&& 0` in the
codepath leads to the expected behavior (e.g. opens the global dynamic
context - current executable + compile-time linked libraries).

