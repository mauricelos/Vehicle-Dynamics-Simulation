"%ProgramFiles%/Git/bin/bash.exe" .vscode/windows_scripts/deploy_executable.sh
cd deployment
"%ProgramFiles%/7-Zip/7z.exe" a -tzip vehicle_dynamics_simulation_windows.zip vehicle_dynamics_simulation_windows
