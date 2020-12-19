// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <vector>

#include "open3d/core/Tensor.h"
#include "open3d/core/TensorKey.h"
#include "open3d/utility/Optional.h"
#include "pybind/core/core.h"
#include "pybind/docstring.h"
#include "pybind/open3d_pybind.h"
#include "pybind/pybind_utils.h"

namespace open3d {
namespace core {

void pybind_core_extra(py::class_<Tensor>& tensor) {
    utility::LogInfo("pybind_core_extra");

    tensor.def("__getitem__", [](const Tensor& tensor, int key) {
        utility::LogInfo("__getitem__ int");
    });

    tensor.def("__getitem__", [](const Tensor& tensor, py::slice key) {
        // PYBIND11_SLICE_OBJECT is PySliceObject.
        PySliceObject* slice_key = reinterpret_cast<PySliceObject*>(key.ptr());
        utility::LogInfo("start is None {}",
                         (int)py::detail::PyNone_Check(slice_key->start));
        utility::LogInfo("step is None {}",
                         (int)py::detail::PyNone_Check(slice_key->step));
        utility::LogInfo("stop is None {}",
                         (int)py::detail::PyNone_Check(slice_key->stop));

        utility::LogInfo("__getitem__ slice");
    });
}

}  // namespace core
}  // namespace open3d