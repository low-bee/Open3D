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

#include "open3d/camera/PinholeCameraTrajectory.h"
#include "open3d/geometry/RGBDImage.h"
#include "open3d/geometry/TriangleMesh.h"
#include "open3d/pipelines/color_map/ColorMapOptimizer.h"
#include "open3d/utility/Console.h"

#include "pybind/docstring.h"
#include "pybind/pipelines/color_map/color_map.h"

namespace open3d {

void pybind_color_map(py::module &m) {
    py::module m_submodule = m.def_submodule("color_map");

    py::class_<pipelines::color_map::ColorMapOptimizer> color_map_optimizer(
            m_submodule, "ColorMapOptimizer",
            "Class for color map optimization.");
    color_map_optimizer.def(
            py::init([](const geometry::TriangleMesh &mesh,
                        const std::vector<std::shared_ptr<geometry::RGBDImage>>
                                &images_rgbd,
                        const camera::PinholeCameraTrajectory
                                &camera_trajectory) {
                return new pipelines::color_map::ColorMapOptimizer(
                        mesh, images_rgbd, camera_trajectory);
            }),
            "mesh"_a, "images_rgbd"_a, "camera_trajectory"_a);
    color_map_optimizer.def_property_readonly(
            "mesh",
            [](const pipelines::color_map::ColorMapOptimizer &optimizer) {
                return optimizer.GetMesh();
            });
    color_map_optimizer.def(
            "run_rigid_optimization",
            &pipelines::color_map::ColorMapOptimizer::RunRigidOptimization,
            "maximum_iteration"_a = 0, "maximum_allowable_depth"_a = 2.5,
            "depth_threshold_for_visibility_check"_a = 0.03,
            "depth_threshold_for_discontinuity_check"_a = 0.1,
            "half_dilation_kernel_size_for_discontinuity_map"_a = 3,
            "image_boundary_margin"_a = 10, "invisible_vertex_color_knn"_a = 3);
    color_map_optimizer.def(
            "run_non_rigid_optimization",
            &pipelines::color_map::ColorMapOptimizer::RunNonRigidOptimization,
            "number_of_vertical_anchors"_a = 16,
            "non_rigid_anchor_point_weight"_a = 0.316,
            "maximum_iteration"_a = 0, "maximum_allowable_depth"_a = 2.5,
            "depth_threshold_for_visibility_check"_a = 0.03,
            "depth_threshold_for_discontinuity_check"_a = 0.1,
            "half_dilation_kernel_size_for_discontinuity_map"_a = 3,
            "image_boundary_margin"_a = 10, "invisible_vertex_color_knn"_a = 3);
}

}  // namespace open3d