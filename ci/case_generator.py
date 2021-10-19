#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse
import yaml


def generate_build_config():
    targets = {
        f"{p}_{avx}{compiler}_{math}_build": {
            "extends": [f".{math}_image", f".{p}_{avx}{compiler}", ".build"]
        }
        for p in ["cpu", "gpu"]
        for avx in ["none", "avx"]
        for math in ["mkl", "oss"]
        for compiler in ["", "_gcc"]
        if not (p == "gpu" and compiler == "_gcc")
    }
    print(yaml.dump(targets))


def generate_build_deb_config():
    targets = {
        f"gpu_sm_{sm}_{math}_build": {
            "extends": [f".{math}_image", ".build_deb"],
            "variables": {
                "PRESET": "gpu-avx-none",
                "MONOLISH_NVIDIA_GPU_ARCH": f"sm_{sm}",
            },
        }
        for math in ["mkl", "oss"]
        for sm in ["52", "60", "61", "70", "75", "80"]
    }
    print(yaml.dump(targets))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("target", choices=["build", "build_deb"])
    args = parser.parse_args()

    if args.target == "build":
        generate_build_config()
    if args.target == "build_deb":
        generate_build_deb_config()
