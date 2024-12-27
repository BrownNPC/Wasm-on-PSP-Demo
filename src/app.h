#ifndef app_H
#define app_H

#ifdef __cplusplus
extern "C" {
#endif

#include "w2c2_base.h"

typedef struct appInstance {
  wasmModuleInstance common;
  wasmMemory* m0;
} appInstance;

  void rl__InitWindow(void*, U32, U32, U32, U32);

void f1(appInstance*);

wasmMemory* app_memory(appInstance* i);

void app__start(appInstance* i);

void appInstantiate(appInstance* instance, void* resolve(const char* module, const char* name));

void appFreeInstance(appInstance* instance);

#ifdef __cplusplus
}
#endif

#endif /* app_H */

