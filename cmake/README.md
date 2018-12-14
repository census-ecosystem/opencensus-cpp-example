# Experimental CMake support

The CMake build system is still experimental and could change.

## Quickstart:

```shell
cmake -H. -B.build
cmake --build .build
.build/helloworld/helloworld
.build/trace/example
```

Using `.build` as the build directory so that it doesn't collide with the
uppercase BUILD file on Windows.
