#define __GLIBC_USE

#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include <pspkernel.h>
PSP_MODULE_INFO("WasiExample", 0, 1, 0);

#include "pspdebug.h"
#define printf pspDebugScreenPrintf

// the compiled wasm -> C code
#include "app.h"
// wasi runtime
#include "w2c2_base.h"
#include "wasi.h"

extern wasmMemory* e_memory;  // the WASM memory.
void trap(Trap trap)
{
  fprintf(stderr, "TRAP: %s\n", trapDescription(trap));
  abort();
}

wasmMemory* wasiMemory(void* instance)
{
  return app_memory((appInstance*)instance);
}
extern char** environ;

// Helper function to retrieve a C string from WASI memory
char* getCStringFromMemory(void* memoryptr, U32 offset, U32 length)
{
  wasmMemory* memory = wasiMemory(memoryptr);
  char* str = (char*)(memory->data + offset);
  char* result = (char*)malloc(
    length + 1);  // Allocate space for the string + null terminator
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Copy the string from WASI memory to local memory
  for (U32 i = 0; i < length; ++i) {
    result[i] = str[i];
  }
  result[length] = '\0';  // Null-terminate the string

  return result;
}

void rl__InitWindow(
  void* memoryptr, U32 width, U32 height, U32 offset, U32 length)
{
  char* title = getCStringFromMemory(memoryptr, offset, length);
  InitWindow(width, height, title);
  bool ready = IsWindowReady();
  if (ready) {
    printf("Window was created");
  }
}

int main(int argc, char* argv[])
{
  pspDebugScreenInit();
  appInstance i;
  appInstantiate(&i, NULL);
  if (!wasiInit(argc, argv, environ)) {
    fprintf(stderr, "failed to initialize WASI\n");
    return 1;
  }

  app__start(&i);
  appFreeInstance(&i);
  return 0;
}
