// Copyright 2017, OpenCensus Authors
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

// Example of OpenCensus tracing and custom trace exporter.

#include <iostream>

#include "absl/memory/memory.h"
#include "absl/synchronization/notification.h"
#include "absl/time/clock.h"
#include "opencensus/trace/exporter/span_data.h"
#include "opencensus/trace/exporter/span_exporter.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/span.h"

namespace {

using ::opencensus::trace::exporter::SpanData;

absl::Notification* Notification() {
  static absl::Notification g_notification;
  return &g_notification;
}

class MyTraceExporter
    : public ::opencensus::trace::exporter::SpanExporter::Handler {
 public:
  void Export(const std::vector<SpanData>& spans) override {
    for (const auto& span : spans) {
      std::cout << span.DebugString() << "\n";
    }
    Notification()->Notify();
  }

  static void Register() {
    ::opencensus::trace::exporter::SpanExporter::RegisterHandler(
        absl::make_unique<MyTraceExporter>());
  }

  static void Wait() {
    std::cout << "Waiting for exporter...\n";
    Notification()->WaitForNotification();
  }
};

}  // namespace

int main() {
  MyTraceExporter::Register();
  static ::opencensus::trace::AlwaysSampler sampler;
  auto span =
      ::opencensus::trace::Span::StartSpan("MySpan",
                                           /*parent=*/nullptr, {&sampler});
  span.AddAnnotation("Hello, I'm a span.");
  span.End();
  MyTraceExporter::Wait();
}
