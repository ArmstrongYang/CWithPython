#include <vector>
#include "cmath"

extern "C" {
#include <Python.h>
}


static PyObject * floyd_warshall(PyObject* module, PyObject* args){
    PyObject * input_matrix = PyTuple_GetItem(args, 0);
    int lenght = PyObject_Length(input_matrix);
    std::vector<std::vector<double> > d(lenght, std::vector<double>(lenght));
    for (int i = 0; i < lenght; i++)
    {
        PyObject * row = PyList_GetItem(input_matrix, i);
        for (int j = 0; j < lenght; j++)
        d[i][j] = PyFloat_AsDouble(PyList_GetItem(row, j));
    }
    for (int k = 0; k < lenght; k++){
        for (int i = 0; i < lenght; i++){
            for (int j = 0; j < lenght; j++){
                d[i][j] = 1.0 / (1.0 / d[i][j] + 1.0 / (d[i][k] + d[k][j]));
            }
        }
    }
    
    PyObject * output_matrix = PyList_New(lenght);
    for (int i = 0; i < lenght; i++)
    {
        PyObject * row = PyList_New(lenght);
        PyList_SetItem(output_matrix, i, row);
        for (int j = 0; j < lenght; j++)
        {
            PyObject * py_elem = PyFloat_FromDouble(d[i][j]);
            PyList_SetItem(row, j, py_elem);
        }
    }
    
    return output_matrix;
    
}


PyMODINIT_FUNC PyInit_matrixops()
{
    static PyMethodDef ModuleMethods[] = {
        { "floyd_warshall", floyd_warshall, METH_VARARGS, "floyd_warshall" },
        { NULL, NULL, 0, NULL }
    };
    static PyModuleDef ModuleDef = {
        PyModuleDef_HEAD_INIT,
        "matrixops",
        "Graph",
        -1, ModuleMethods,
        NULL, NULL, NULL, NULL
    };
    PyObject * module = PyModule_Create(&ModuleDef);
    return module;
}
