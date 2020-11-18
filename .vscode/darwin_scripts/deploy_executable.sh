yes | rm -r deployment/vehicle_dynamics_simulation_darwin
mkdir -p deployment/vehicle_dynamics_simulation_darwin
cp "$(bazel info bazel-genfiles)/vehicle_dynamics_simulation" deployment/vehicle_dynamics_simulation_darwin/
cp vehicle_specifications/mazda_rx8.yaml deployment/vehicle_dynamics_simulation_darwin/
cd deployment
zip -r vehicle_dynamics_simulation_darwin.zip vehicle_dynamics_simulation_darwin