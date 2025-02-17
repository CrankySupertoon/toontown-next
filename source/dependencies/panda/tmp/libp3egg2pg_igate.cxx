/*
 * This file was generated by:
 * built\bin\interrogate -v -srcdir panda/src/egg2pg -Ipanda/src/egg2pg -DCPPPARSER -D__STDC__=1 -D__cplusplus=201103L -DWIN32_VC -DWIN32 -D_WIN32 -D_M_IX86 -D_MSC_VER=1600 -D__declspec(param)= -D__cdecl -D_near -D_far -D__near -D__far -D__stdcall -oc built/tmp/libp3egg2pg_igate.cxx -od built/pandac/input/libp3egg2pg.in -fnames -string -refcount -assert -python-native -Sbuilt/include/parser-inc -Ipanda/src/egg2pg -Sbuilt/tmp -Sbuilt/include -Sthirdparty/win-python/include -Sthirdparty/win-libs-vc10/extras/include -module panda3d.egg -library libp3egg2pg load_egg_file.h 
 *
 */

#include "dtoolbase.h"
#include "interrogate_request.h"
#include "dconfig.h"
#include "pnotify.h"
#include <sstream>
#define PANDA_LIBRARY_NAME_libp3egg2pg
#include "py_panda.h"
#include "extension.h"
#include "dcast.h"

#include "coordinateSystem.h"
#include "eggData.h"
#include "load_egg_file.h"
#include "pandaNode.h"
#include "pandabase.h"

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#define PY_SSIZE_T_CLEAN 1

#if PYTHON_FRAMEWORK
  #include <Python/Python.h>
#else
  #include "Python.h"
#endif

/**
 * Extern declarations for imported classes
 */
// Filename
#ifndef LINK_ALL_STATIC
static struct Dtool_PyTypedObject *Dtool_Ptr_Filename;
inline static Filename *Dtool_Coerce_Filename(PyObject *args, Filename &coerced) {
  nassertr(Dtool_Ptr_Filename != NULL, NULL);
  nassertr(Dtool_Ptr_Filename->_Dtool_Coerce != NULL, NULL);
  return ((Filename *(*)(PyObject *, Filename &))Dtool_Ptr_Filename->_Dtool_Coerce)(args, coerced);
}
#else
extern struct Dtool_PyTypedObject Dtool_Filename;
static struct Dtool_PyTypedObject *const Dtool_Ptr_Filename = &Dtool_Filename;
extern Filename *Dtool_Coerce_Filename(PyObject *args, Filename &coerced);
#endif
// PandaNode
#ifndef LINK_ALL_STATIC
static struct Dtool_PyTypedObject *Dtool_Ptr_PandaNode;
#else
extern struct Dtool_PyTypedObject Dtool_PandaNode;
static struct Dtool_PyTypedObject *const Dtool_Ptr_PandaNode = &Dtool_PandaNode;
#endif
// BamCacheRecord
#ifndef LINK_ALL_STATIC
static struct Dtool_PyTypedObject *Dtool_Ptr_BamCacheRecord;
#else
extern struct Dtool_PyTypedObject Dtool_BamCacheRecord;
static struct Dtool_PyTypedObject *const Dtool_Ptr_BamCacheRecord = &Dtool_BamCacheRecord;
#endif
// EggData
#ifndef LINK_ALL_STATIC
static struct Dtool_PyTypedObject *Dtool_Ptr_EggData;
#else
extern struct Dtool_PyTypedObject Dtool_EggData;
static struct Dtool_PyTypedObject *const Dtool_Ptr_EggData = &Dtool_EggData;
#endif

/**
 * Python wrappers for global functions
 */
/**
 * Python function wrapper for:
 * PointerTo< PandaNode > load_egg_file(Filename const &filename, CoordinateSystem cs = ::CS_default, BamCacheRecord *record = 0)
 */
static PyObject *Dtool_load_egg_file_1(PyObject *, PyObject *args, PyObject *kwds) {
  // 1-PointerTo< PandaNode > load_egg_file(Filename const &filename, CoordinateSystem cs = ::CS_default, BamCacheRecord *record = 0)
  PyObject *param0;
  int param1 = ::CS_default;
  PyObject *param2 = NULL;
  static const char *keyword_list[] = {"filename", "cs", "record", NULL};
  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|iO:load_egg_file", (char **)keyword_list, &param0, &param1, &param2)) {
    Filename param0_local;
    Filename const *param0_this = Dtool_Coerce_Filename(param0, param0_local);
    if (!(param0_this != NULL)) {
      return Dtool_Raise_ArgTypeError(param0, 0, "load_egg_file", "Filename");
    }
    BamCacheRecord *param2_this = 0;
    if (param2 != (PyObject *)NULL) {
      param2_this = (BamCacheRecord *)DTOOL_Call_GetPointerThisClass(param2, Dtool_Ptr_BamCacheRecord, 2, "load_egg_file", false, true);
    }
    if ((param2 == NULL || param2_this != NULL)) {
      PointerTo< PandaNode > return_value = load_egg_file(*param0_this, (CoordinateSystem)param1, param2_this);
      if (Dtool_CheckErrorOccurred()) {
        return NULL;
      }
      // Transfer ownership of return_value.
      PandaNode *return_ptr = return_value.p();
      return_value.cheat() = NULL;
      if (return_ptr == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
      } else {
        return DTool_CreatePyInstanceTyped((void *)return_ptr, *Dtool_Ptr_PandaNode, true, false, return_ptr->as_typed_object()->get_type_index());
      }
    }
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "load_egg_file(const Filename filename, int cs, BamCacheRecord record)\n");
  }
  return NULL;
}

#ifndef NDEBUG
static const char *Dtool_load_egg_file_1_comment =
  "C++ Interface:\n"
  "load_egg_file(const Filename filename, int cs, BamCacheRecord record)\n";
#else
static const char *Dtool_load_egg_file_1_comment = NULL;
#endif

/**
 * Python function wrapper for:
 * PointerTo< PandaNode > load_egg_data(EggData *data, CoordinateSystem cs = ::CS_default)
 */
static PyObject *Dtool_load_egg_data_2(PyObject *, PyObject *args, PyObject *kwds) {
  // 1-PointerTo< PandaNode > load_egg_data(EggData *data, CoordinateSystem cs = ::CS_default)
  PyObject *param0;
  int param1 = ::CS_default;
  static const char *keyword_list[] = {"data", "cs", NULL};
  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|i:load_egg_data", (char **)keyword_list, &param0, &param1)) {
    EggData *param0_this = (EggData *)DTOOL_Call_GetPointerThisClass(param0, Dtool_Ptr_EggData, 0, "load_egg_data", false, true);
    if (param0_this != NULL) {
      PointerTo< PandaNode > return_value = load_egg_data(param0_this, (CoordinateSystem)param1);
      if (Dtool_CheckErrorOccurred()) {
        return NULL;
      }
      // Transfer ownership of return_value.
      PandaNode *return_ptr = return_value.p();
      return_value.cheat() = NULL;
      if (return_ptr == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
      } else {
        return DTool_CreatePyInstanceTyped((void *)return_ptr, *Dtool_Ptr_PandaNode, true, false, return_ptr->as_typed_object()->get_type_index());
      }
    }
  }
  if (!_PyErr_OCCURRED()) {
    return Dtool_Raise_BadArgumentsError(
      "load_egg_data(EggData data, int cs)\n");
  }
  return NULL;
}

#ifndef NDEBUG
static const char *Dtool_load_egg_data_2_comment =
  "C++ Interface:\n"
  "load_egg_data(EggData data, int cs)\n";
#else
static const char *Dtool_load_egg_data_2_comment = NULL;
#endif


/**
 * Module Object Linker ..
 */
void Dtool_libp3egg2pg_RegisterTypes() {
}

void Dtool_libp3egg2pg_ResolveExternals() {
#ifndef LINK_ALL_STATIC
  // Resolve externally imported types.
  Dtool_Ptr_Filename = LookupRuntimeTypedClass(Filename::get_class_type());
  Dtool_Ptr_PandaNode = LookupRuntimeTypedClass(PandaNode::get_class_type());
  Dtool_Ptr_BamCacheRecord = LookupRuntimeTypedClass(BamCacheRecord::get_class_type());
  Dtool_Ptr_EggData = LookupRuntimeTypedClass(EggData::get_class_type());
#endif
}

void Dtool_libp3egg2pg_BuildInstants(PyObject *module) {
  (void) module;
}

static PyMethodDef python_simple_funcs[] = {
  {"load_egg_file", (PyCFunction) &Dtool_load_egg_file_1, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_load_egg_file_1_comment},
  {"loadEggFile", (PyCFunction) &Dtool_load_egg_file_1, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_load_egg_file_1_comment},
  {"load_egg_data", (PyCFunction) &Dtool_load_egg_data_2, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_load_egg_data_2_comment},
  {"loadEggData", (PyCFunction) &Dtool_load_egg_data_2, METH_VARARGS | METH_KEYWORDS, (const char *)Dtool_load_egg_data_2_comment},
  // Support Function For Dtool_types ... for now in each module ??
  {"Dtool_BorrowThisReference", &Dtool_BorrowThisReference, METH_VARARGS, "Used to borrow 'this' pointer (to, from)\nAssumes no ownership."},
  {"Dtool_AddToDictionary", &Dtool_AddToDictionary, METH_VARARGS, "Used to add items into a tp_dict"},
  {NULL, NULL, 0, NULL}
};

struct LibraryDef libp3egg2pg_moddef = {python_simple_funcs};
static InterrogateModuleDef _in_module_def = {
  1478214078,  /* file_identifier */
  "libp3egg2pg",  /* library_name */
  "KLrJ",  /* library_hash_name */
  "panda3d.egg",  /* module_name */
  "libp3egg2pg.in",  /* database_filename */
  (InterrogateUniqueNameDef *)0,  /* unique_names */
  0,  /* num_unique_names */
  (void **)0,  /* fptrs */
  0,  /* num_fptrs */
  1,  /* first_index */
  15  /* next_index */
};

Configure(_in_configure_libp3egg2pg);
ConfigureFn(_in_configure_libp3egg2pg) {
  interrogate_request_module(&_in_module_def);
}

