## Vehicle Dynamics Simulation

![version](https://img.shields.io/badge/version-1.0-green)

### Prerequisites for development

- **Linux** (tested with Ubuntu 18.04)
    - [`gcc/g++`](https://gcc.gnu.org/install/) (tested with _8.4.0_, needs C++17 filesystem support)
    - [`Bazel`](https://docs.bazel.build/versions/master/install.html) (tested with _3.7.0_)(_**optional**_, bazelisk can also be used)
    - [`clang-format`](https://releases.llvm.org/download.html) (tested with _6.0.0_, default Ubuntu 18.04)(_**optional**_, only for commits)
    - [`git`](https://git-scm.com/downloads) (tested with _2.17.1_)(_**optional**_, only for commits)

- **Windows** (tested with Windows 10 1903)
    - [`Windows developer mode`](https://docs.microsoft.com/de-de/windows/apps/get-started/enable-your-device-for-development) needs to be enabled for experimental symlink support 
    - [`MSVC`](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) (tested with _v142_ toolset, needs C++17 filesystem support)
    - [`Bazel`](https://docs.bazel.build/versions/master/install.html) (tested with _3.4.1_)(_**optional**_, bazelisk can also be used)
        - [`Python`](https://www.python.org/downloads/windows/) (_**required**_, in case bazelisk is used)
    - [`clang-format`](https://releases.llvm.org/download.html) (tested with _12.0.0_)(_**optional**_, only for commits)
    - [`git`](https://git-scm.com/downloads) (tested with _2.28.0_)(_**optional**_, only for commits)
    - [`7-Zip`](https://www.7-zip.de/) (tested with _19.00_)(_**optional**_, only for deployment)

- **MacOS** (tested with Catalina 10.15.7 and Big Sur 11.0.1)
    - [`XCode Command Line Tools/Apple clang`](https://developer.apple.com/xcode/resources/) (tested with _12.0.0_, needs C++17 filesystem support)
    - [`Bazel`](https://docs.bazel.build/versions/master/install.html) (tested with _3.7.0_)(_**optional**_, bazelisk can also be used)
    - [`clang-format`](https://releases.llvm.org/download.html) (tested with _12.0.0_)(_**optional**_, only for commits)
    - [`git`](https://git-scm.com/downloads) (tested with _2.28.0_)(_**optional**_, only for commits)

**Don't forget to clone using:** 

```git clone --recurse-submodules https://github.com/mauricelos/Vehicle-Dynamics-Simulation.git```

If you want to use this repo without a local install of bazel
___

### How to run vehicle dynamics simulation

The vehicle dynamics simulation executable uses yaml files to retrieve information about the vehicle's properties. The executable can either get these yaml files automatically from the directory that it is placed in or it can take paths to yaml files via command line arguments

**Command line options for vehicle dynamics simulation:**

```
Usage: ./vehicle_dynamics_simulation <race option> <yaml_file> <yaml_file> ...
Options:
    -r|--race   - Allows two vehicles to race (only available in command line 
                  and only if exactly two yamls are given, this arg needs 
                  to be the first argument passed to the executable)
```

**Using the binary as standalone**:

- [`Download`](https://github.com/mauricelos/Vehicle-Dynamics-Simulation/releases/latest) the binary for your respective platform and extract the folder
- Modify the yaml file based on your vehicle
- Execute vehicle dynamics simulation
    - Double click the executable or
    - Execute via command line
- The executable will run the vehicle simulation for the given yaml file/s
- The result will be printed in the console and log files for the run will be created


___

### Usage with VS Code tasks and launch

This project was developed with [`VS Code`](https://code.visualstudio.com/) therefore it has VS Code specific functionalities like running tasks and launch code in the debugger. Build tasks can be selected for execution via <kbd>ctrl</kbd> + <kbd>shift</kbd> + <kbd>B</kbd> on Windows and Linux and via <kbd>command</kbd> + <kbd>shift</kbd> + <kbd>B</kbd> on MacOS

Following build [tasks](./.vscode/tasks.json) are available:

- Various build tasks
- Get latest version of bazelisk
- Run Buildifier
- Run clang-format
- Run vehicle dynamics simulation
- Clean bazel container
- Deploy binary

Following test [tasks](./.vscode/tasks.json) are available:

- Run/Test all unit tests
- Run/Test individual unit tests

Following [launches](./.vscode/launch.json) are available:

- Debug unit tests
- Debug vehicle dynamics simulation

A common workflow would be to modify code and run the vehicle dynamics simulation for checking resulting changes followed by the execution of specific unit tests or even all tests via the [`VS Code tasks`](https://code.visualstudio.com/docs/editor/tasks). In case of a runtime issue the developer can launch vehicle dynamics simulation in the debugger or tackle bugs by debugging inside the unit tests with [`VS Code launch/debugger`](https://code.visualstudio.com/docs/editor/debugging). Once a new feautre is developed the developer can deploy it using the deploy task. This will export the binary and a configuration yaml file to a dedicated deployment folder inside the workspace

___

### Usage with Bazel/Bazelisk commands

This project is using bazel/bazelisk as its compiler tool. Bazel can be used to compile/run and test the code as well. Here are some examples for useful bazel commands:

```
bazel run :vehicle_dynamics_simulation    -> For running the main executable
bazel test :all                           -> To run all tests
bazel test :<specific unit test>          -> To run only a certain test
bazel clean                               -> For cleaning up
bazel build :all                          -> To build all targets
bazel build :<specific target>            -> To build only a certain target

or

./bazelisk/bazelisk.py run :vehicle_dynamics_simulation    -> For running the main executable
./bazelisk/bazelisk.py test :all                           -> To run all tests
./bazelisk/bazelisk.py test :<specific unit test>          -> To run only a certain test
./bazelisk/bazelisk.py clean                               -> For cleaning up
./bazelisk/bazelisk.py build :all                          -> To build all targets
./bazelisk/bazelisk.py build :<specific target>            -> To build only a certain target
```

**Caution: Windows users** will need to use ```--experimental_enable_runfiles``` for some targets including ```vehicle_dynamics_simulation``` binary

___

### Git Hooks

This project comes with a pre-commit git hook. This ensures that all code pushed to the repository is meeting the required quality standard. The pre-commit hook executes buildifier, clang-format and runs all tests. In case of changes to files due to the run of buildifier or clang-format the script will terminate the commit attempt and ask to add the newly changed files to the commit. In case that tests are failing the script will also terminate the commit attempt and the developer should fix the failing tests. If all checks are passed the git commit will be proceeded and the changes can be pushed.

Git hooks can be enbaled by running following command:

```
git config --local core.hooksPath git_hooks/
```

___

### Overview of folders and files

```
Vehicle-Dynamics-Simulation
├── BUILD
├── README.md
├── WORKSPACE
├── git_hooks
│   └── pre-commit
├── include
│   ├── engine.h
│   ├── transmission.h
│   ├── utils.h
│   ├── vehicle.h
│   ├── vehicle_logger.h
│   ├── vehicle_model.h
│   ├── vehicle_specification_parser.h
│   └── vehicle_stats.h
├── spline_lib.BUILD
├── src
│   ├── engine.cpp
│   ├── main.cpp
│   ├── transmission.cpp
│   ├── utils.cpp
│   ├── vehicle.cpp
│   ├── vehicle_logger.cpp
│   ├── vehicle_model.cpp
│   ├── vehicle_specification_parser.cpp
│   └── vehicle_stats.cpp
├── test
│   ├── engine_test.cpp
│   ├── transmission_test.cpp
│   ├── utils_test.cpp
│   ├── vehicle_logger_test.cpp
│   ├── vehicle_model_test.cpp
│   ├── vehicle_specification_parser_test.cpp
│   ├── vehicle_stats_test.cpp
│   └── vehicle_test.cpp
└── vehicle_specifications
    ├── mazda_rx8.yaml
    ├── mazda_rx8_10LXX.yaml
    ├── mazda_rx8_8HP70.yaml
    ├── mazda_rx8_8HP70_boosted.yaml
    ├── mazda_rx8_9G_tronic_new.yaml
    ├── mazda_rx8_9G_tronic_old.yaml
    ├── mazda_rx8_GS7D36sg.yaml
    └── wrong_format.yaml
```
