sed -i 's#$(readlink.*#'"'$(head -n 1 bazel-bin/buildifier.bash.runfiles_manifest | cut -d' ' -f2)'"'#g' "bazel-bin/buildifier.bash" && ./bazel-bin/buildifier.bash
