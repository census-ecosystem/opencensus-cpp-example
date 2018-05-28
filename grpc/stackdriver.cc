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

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "absl/strings/str_cat.h"
#include "grpc/stackdriver.h"
#include "opencensus/exporters/stats/stackdriver/stackdriver_exporter.h"
#include "opencensus/exporters/trace/stackdriver/stackdriver_exporter.h"

void RegisterStackdriverExporters() {
  const char* project_id = getenv("STACKDRIVER_PROJECT_ID");
  if (project_id == nullptr) {
    std::cerr << "The STACKDRIVER_PROJECT_ID environment variable is not set: "
                 "not exporting to Stackdriver.\n";
    return;
  }
  const char* hostname = getenv("HOSTNAME");
  if (hostname == nullptr) hostname = "hostname";
  const std::string opencensus_task =
      absl::StrCat("cpp-", getpid(), "@", hostname);
  opencensus::exporters::stats::StackdriverExporter::Register(project_id,
                                                              opencensus_task);
  opencensus::exporters::trace::StackdriverExporter::Register(project_id);
}
