// Copyright 2018, OpenCensus Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <limits.h>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "absl/strings/str_cat.h"
#include "grpc/stackdriver.h"
#include "opencensus/exporters/stats/stackdriver/stackdriver_exporter.h"
#include "opencensus/exporters/trace/stackdriver/stackdriver_exporter.h"

// OS X defines _POSIX_HOST_NAME_MAX instead.
#ifndef HOST_NAME_MAX
#ifdef _POSIX_HOST_NAME_MAX
#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#else
#define HOST_NAME_MAX 255  // SUSv2 says 255 is the limit.
#endif
#endif

void RegisterStackdriverExporters() {
  const char *project_id = getenv("STACKDRIVER_PROJECT_ID");
  if (project_id == nullptr) {
    std::cerr << "The STACKDRIVER_PROJECT_ID environment variable is not set: "
                 "not exporting to Stackdriver.\n";
    return;
  }
  char hostname[HOST_NAME_MAX + 1];
  if (gethostname(hostname, sizeof(hostname)) == -1) {
    std::cerr << "gethostname() failed: " << strerror(errno) << "\n";
    strncpy(hostname, "hostname", sizeof(hostname) - 1);
    hostname[sizeof(hostname) - 1] = 0;
  }

  opencensus::exporters::stats::StackdriverOptions stats_opts;
  stats_opts.project_id = project_id;
  stats_opts.opencensus_task = absl::StrCat("cpp-", getpid(), "@", hostname);

  std::cout << "RegisterStackdriverExporters:\n";
  std::cout << "  project_id = \"" << stats_opts.project_id << "\"\n";
  std::cout << "  opencensus_task = \"" << stats_opts.opencensus_task << "\"\n";

  opencensus::exporters::trace::StackdriverOptions trace_opts;
  trace_opts.project_id = project_id;

  opencensus::exporters::stats::StackdriverExporter::Register(stats_opts);
  opencensus::exporters::trace::StackdriverExporter::Register(trace_opts);
}
