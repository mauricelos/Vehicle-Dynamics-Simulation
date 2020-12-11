yes | rm -r -f deployment/vehicle_dynamics_simulation_linux
mkdir -p deployment/vehicle_dynamics_simulation_linux/
cp "$(bazel info bazel-genfiles)/vehicle_dynamics_simulation" deployment/vehicle_dynamics_simulation_linux/
cp vehicle_specifications/mazda_rx8.yaml deployment/vehicle_dynamics_simulation_linux/
cd deployment
zip -r vehicle_dynamics_simulation_linux.zip vehicle_dynamics_simulation_linux