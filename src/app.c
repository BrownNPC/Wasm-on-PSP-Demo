#include "w2c2_base.h"

#include "app.h"

const U8 d0[] = {0x50, 0x73, 0x70, 0x20, 0x74, 0x65, 0x73, 0x74};

void f1(appInstance* i) {
  U32 l0 = 0;
  U32 si0, si1, si2, si3;
  si0 = 1032U;
  si1 = (*i->m0).pages;
  si2 = 16U;
  si1 <<= (si2 & 31);
  i32_store(i->m0, (U64)si0, si1);
  si0 = 1032U;
  si0 = i32_load(i->m0, (U64)si0);
  l0 = si0;
  si1 = l0;
  si2 = 66512U;
  si1 -= si2;
  si2 = 65U;
  si1 = DIV_U(si1, si2);
  l0 = si1;
  si0 -= si1;
  si1 = 0U;
  si2 = l0;
  wasmMemoryFill(i->m0, si0, si1, si2);
  si0 = 1032U;
  si1 = (*i->m0).pages;
  si2 = 16U;
  si1 <<= (si2 & 31);
  i32_store(i->m0, (U64)si0, si1);
  si0 = 480U;
  si1 = 272U;
  si2 = 1024U;
  si3 = 8U;
  rl__InitWindow(i, si0, si1, si2, si3);
  L1:;
  {
    goto L1;
  }
  UNREACHABLE;
  L0:;
}

wasmFuncExport appFuncExports[2] = {
{(wasmFunc)f1,"_start"},
{NULL,NULL}
};

static void appInitMemories(appInstance* i, appInstance* parent) {
  i->m0 = wasmMemoryAllocate(2, 65535, false);
  LOAD_DATA((*i->m0), 1024U, d0, 8);
}

static void appInitImports(appInstance* i, void* resolve(const char* module, const char* name)) {
  if (resolve == NULL) { return; }
}

wasmMemory* app_memory(appInstance* i) {
  return i->m0;
}

void app__start(appInstance* i) {
  f1(i);
}

appInstance* appNewChild(appInstance* self) {
  appInstance* child = (appInstance*)calloc(1, sizeof(appInstance));
  child->common.funcExports = self->common.funcExports;
  child->common.resolveImports = self->common.resolveImports;
  child->common.newChild = self->common.newChild;
  appInitImports(child, self->common.resolveImports);
  appInitMemories(child, self);
  return child;
}

void appInstantiate(appInstance* i, void* resolveImports(const char* module, const char* name)) {
  i->common.funcExports = appFuncExports;
  i->common.resolveImports = resolveImports;
  i->common.newChild = (struct wasmModuleInstance* (*)(struct wasmModuleInstance*))appNewChild;
  appInitImports(i, resolveImports);
  appInitMemories(i, NULL);
}

void appFreeInstance(appInstance* i) {
  wasmMemoryFree(i->m0);
}

