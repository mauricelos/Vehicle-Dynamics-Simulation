yes | rm -r deployment/vehicle_dynamics_simulation_windows
mkdir -p deployment/vehicle_dynamics_simulation_windows/
cp "$(bazel info bazel-genfiles)/vehicle_dynamics_simulation.exe" deployment/vehicle_dynamics_simulation_windows/
cp vehicle_specifications/mazda_rx8.yaml deployment/vehicle_dynamics_simulation_windows/