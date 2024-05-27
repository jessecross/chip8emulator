load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "chip8_emulator",
    srcs = ["emulator.cpp"],
    deps = [
        ":chip8_cpu",
        ":chip8_graphics",
        ":chip8_input",
    ],
)

cc_library(
    name = "chip8_cpu",
    srcs = ["cpu.cpp"],
    hdrs = ["cpu.h"],
)

cc_library(
    name = "chip8_graphics",
    srcs = ["graphics.cpp"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "chip8_input",
    srcs = ["input.cpp"],
    hdrs = ["input.h"],
)
