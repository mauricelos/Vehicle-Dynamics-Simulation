For Windows all commands need to be run with the flag: --experimental_enable_runfiles 
Also Windows need to be of version 1703 or higher and developer mode need to be activated (or bazel needs to be run as administrator)
Otherwise bazel will not create symlinks for the yaml file stored in vehicle_specification
Windows requires 7-Zip for deploying exectuables and git bash for VS Code tasks and git hooks