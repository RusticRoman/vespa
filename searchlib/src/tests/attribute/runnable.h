// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#pragma once

#include <mutex>
#include <condition_variable>
#include <vespa/fastos/thread.h>

namespace search {

class Runnable : public FastOS_Runnable
{
protected:
    uint32_t                _id;
    std::mutex              _lock;
    std::condition_variable _cond;
    bool                    _done;
    bool                    _stopped;

public:
    Runnable(uint32_t id) :
        _id(id), _lock(), _cond(), _done(false), _stopped(false)
    { }
    void Run(FastOS_ThreadInterface *, void *) override {
        doRun();

        std::lock_guard<std::mutex> guard(_lock);
        _stopped = true;
        _cond.notify_all();
    }
    virtual void doRun() = 0;
    void stop() {
        std::lock_guard<std::mutex> guard(_lock);
        _done = true;
    }
    void join() {
        std::unique_lock<std::mutex> guard(_lock);
        while (!_stopped) {
            _cond.wait(guard);
        }
    }
};

} // search

