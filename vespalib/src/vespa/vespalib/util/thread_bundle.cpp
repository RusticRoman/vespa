// Copyright Yahoo. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "thread_bundle.h"
#include "exceptions.h"

namespace vespalib {

ThreadBundle &
ThreadBundle::trivial() {
    struct TrivialThreadBundle : ThreadBundle {
        size_t size() const override { return 1; }
        void run(const std::vector<Runnable*> &targets) override {
            if (targets.size() == 1) {
                targets[0]->run();
            } else if (targets.size() > 1) {
                throw IllegalArgumentException("too many targets");
            }
        };
    };
    static TrivialThreadBundle trivial_thread_bundle;
    return trivial_thread_bundle;
}

} // namespace vespalib
