load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

buildifier(
    name = "buildifier",
)

cc_library(
    name = "vehicle_dynamics_simulation_lib",
    srcs = [
        "src/engine.cpp",
        "src/transmission.cpp",
        "src/utils.cpp",
        "src/vehicle.cpp",
        "src/vehicle_logger.cpp",
        "src/vehicle_model.cpp",
        "src/vehicle_stats.cpp",
    ],
    hdrs = [
        "include/engine.h",
        "include/transmission.h",
        "include/utils.h",
        "include/vehicle.h",
        "include/vehicle_logger.h",
        "include/vehicle_model.h",
        "include/vehicle_stats.h",
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    includes = ["include"],
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    strip_include_prefix = "include",
    deps = ["@spline_lib"],
)

cc_library(
    name = "vehicle_specification_parser",
    srcs = ["src/vehicle_specification_parser.cpp"],
    hdrs = ["include/vehicle_specification_parser.h"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    includes = ["include"],
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    strip_include_prefix = "include",
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_binary(
    name = "vehicle_dynamics_simulation",
    srcs = ["src/main.cpp"],
    args = [
        "--race",
        "vehicle_specifications/mazda_rx8_8HP70.yaml",
        "vehicle_specifications/mazda_rx8_8HP70_boosted.yaml",
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    data = glob(["vehicle_specifications/*.yaml"]),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        ":vehicle_specification_parser",
    ],
)

cc_test(
    name = "vehicle_specification_parser_test",
    srcs = ["test/vehicle_specification_parser_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    data = glob(["vehicle_specifications/*.yaml"]),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_specification_parser",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "engine_test",
    srcs = ["test/engine_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "transmission_test",
    srcs = ["test/transmission_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "utils_test",
    srcs = ["test/utils_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "vehicle_test",
    srcs = ["test/vehicle_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "vehicle_stats_test",
    srcs = ["test/vehicle_stats_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "vehicle_logger_test",
    srcs = ["test/vehicle_logger_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "vehicle_model_test",
    srcs = ["test/vehicle_model_test.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [],
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-std=c++17",
            "-lstdc++fs",
        ],
    }),
    deps = [
        ":vehicle_dynamics_simulation_lib",
        "@gtest//:gtest_main",
    ],
)
