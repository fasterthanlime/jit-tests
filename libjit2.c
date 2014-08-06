#include <jit/jit.h>
#include <jit/jit-dynamic.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  puts("Alright, let's get started!");
  jit_context_t context;
  context = jit_context_create();
  jit_context_build_start(context);
  
  void* puts_addr;
  jit_dynlib_handle_t dynlib;
  dynlib = jit_dynlib_open(NULL);
  if (!dynlib) {
    puts("Could not open self as dynlib.");
    exit(1);
  }

  puts_addr = jit_dynlib_get_symbol(dynlib, "puts");
  if (!puts_addr) {
    puts("Could not get 'puts' address dynamically via libjit.");
    exit(1);
  }
  jit_dynlib_close(dynlib);

  jit_function_t function;
  jit_type_t signature;
  signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, NULL, 0, 1);

  function = jit_function_create(context, signature);

  jit_type_t puts_params[1];
  puts_params[0] = jit_type_void_ptr;
  jit_type_t puts_signature;
  puts_signature = jit_type_create_signature(jit_abi_cdecl, jit_type_int, puts_params, 1, 1);

  jit_value_t puts_args[1];
  const char *message = "Hello from libjit as a ffi";
  puts_args[0] = jit_value_create_nint_constant(function, jit_type_void_ptr, (jit_nint) message);

  jit_insn_call_native(
      function,
      "puts", // for debug only, could be NULL
      puts_addr,
      puts_signature,
      puts_args,
      1, // num_args
      0  // flags
  );
  jit_insn_return(function, NULL);
  jit_function_compile(function);
  jit_context_build_end(context);

  int result;
  jit_function_apply(function, NULL, &result);

  int (*closure)() = jit_function_to_closure(function);
  closure();
}

