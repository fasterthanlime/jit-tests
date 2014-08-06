
#include <dlfcn.h>
#include <ffi.h>

int main(int argc, char *argv[])
{
  // dlfcn stuff
  void *handle;
  void *puts_addr;

  // ffi stuff
  ffi_cif cif;
  ffi_type *args[1];
  void *values[1];
  char *s;
  int rc;

  // get 'puts' address from global symbol space
  handle = dlopen(0, RTLD_LAZY);
  puts_addr = dlsym(handle, "puts");

  // initialize the argument info vectors
  args[0] = &ffi_type_pointer;
  values[0] = &s;

  // Initialize the cif
  if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1,
        &ffi_type_uint, args) == FFI_OK)
  {
    s = "Hello from dlfcn / ffi";
    ffi_call(&cif, puts_addr, &rc, values);
  }
     
  return 0;
}
