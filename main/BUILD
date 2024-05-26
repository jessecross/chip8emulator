load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "chip8_emulator",
    srcs = ["emulator.cpp"],
    deps = [":chip8_cpu"],
)

cc_library(
    name = "chip8_cpu",
    srcs = ["cpu.cpp"],
    hdrs = ["cpu.h"],
)