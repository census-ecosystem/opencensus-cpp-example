> **Warning**
>
> OpenCensus and OpenTracing have merged to form [OpenTelemetry](https://opentelemetry.io), which serves as the next major version of OpenCensus and OpenTracing.
>
> OpenTelemetry has now reached feature parity with OpenCensus, with tracing and metrics SDKs available in .NET, Golang, Java, NodeJS, and Python. **All OpenCensus Github repositories, except [census-instrumentation/opencensus-python](https://github.com/census-instrumentation/opencensus-python), will be archived on July 31st, 2023**. We encourage users to migrate to OpenTelemetry by this date.
>
> To help you gradually migrate your instrumentation to OpenTelemetry, bridges are available in Java, Go, Python, and JS. [**Read the full blog post to learn more**](https://opentelemetry.io/blog/2023/sunsetting-opencensus/).

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
