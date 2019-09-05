#include <Python.h>
#include "quickxorhash.h"

typedef struct {
    PyObject_HEAD
    qxhash *_hash;
} quickxorhashObject;

static PyObject *
quickxorhash_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    quickxorhashObject *self;
    self = (quickxorhashObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->_hash = qxh_new();
    }
    return (PyObject *) self;
}

static void
quickxorhash_dealloc(quickxorhashObject *self)
{
    qxh_free(self->_hash);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
quickxorhash_update(quickxorhashObject *self, PyObject *data)
{
    char *buf = PyBytes_AsString(data);
    Py_ssize_t size = PyBytes_Size(data);
    qxh_update(self->_hash, (uint8_t *) buf, size);
    Py_RETURN_NONE;
}

static PyObject *
quickxorhash_digest(quickxorhashObject *self, PyObject *Py_UNUSED(ignored))
{
    char *h = qxh_finalize(self->_hash);
    PyObject *res = PyBytes_FromStringAndSize(h, 20);
    free(h);
    return res;
}

static PyMethodDef quickxorhash_methods[] = {
    {"update", (PyCFunction)  quickxorhash_update, METH_O, "Continue hashing of a message by consuming the next chunk of data."},
    {"digest", (PyCFunction)  quickxorhash_digest, METH_NOARGS, "Return the **binary** (non-printable) digest of the message that has been hashed so far."},
    {NULL}  /* Sentinel */
};

static PyTypeObject quickxorhashType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "quickxorhash.quickxorhash",
    .tp_basicsize = sizeof(quickxorhashObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = quickxorhash_new,
    .tp_dealloc = (destructor) quickxorhash_dealloc,
    .tp_methods = quickxorhash_methods,
};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "quickxorhash",
    "Quick XOR Hash for OneDrive for Business",
    -1,
};

PyMODINIT_FUNC PyInit_quickxorhash(void)
{
    PyObject *m;
    if (PyType_Ready(&quickxorhashType) < 0)
        return NULL;
    m = PyModule_Create(&myModule);
    if (m == NULL)
        return NULL;
    Py_INCREF(&quickxorhashType);
    PyModule_AddObject(m, "quickxorhash", (PyObject *) &quickxorhashType);
    return m;
}
