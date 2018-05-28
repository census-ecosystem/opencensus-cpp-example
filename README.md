# OpenCensus C++ Example
[![Build Status][travis-image]][travis-url]

This is an example project using
[opencensus-cpp](https://github.com/census-instrumentation/opencensus-cpp)
for instrumentation.

## Quickstart:

```shell
$ git clone https://github.com/census-ecosystem/opencensus-cpp-example.git
$ cd opencensus-cpp-example
$ bazel build //trace:example //helloworld:helloworld //grpc:all
$ bazel-bin/trace/example
$ bazel-bin/helloworld/helloworld
$ bazel-bin/grpc/hello_server 9001

# While the server is running:

$ bazel-bin/grpc/hello_client '[::]:9001'
```

This is not an officially supported Google product.

[travis-image]: https://travis-ci.org/census-ecosystem/opencensus-cpp-example.svg?branch=master
[travis-url]: https://travis-ci.org/census-ecosystem/opencensus-cpp-example
