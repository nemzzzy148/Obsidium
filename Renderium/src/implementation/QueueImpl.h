//
// Created by Nemesis Verstraete on 30/08/2026.
//

#pragma once
#include <Error.h>
#include <memory>

#include "Queue.h"
#include "Result.h"

namespace rhi {

template<typename Api>
class QueueImpl : public renderium::Queue::Impl {
public:
    using Queue = Api::Queue;
    using QueueResult = renderium::Result<std::unique_ptr<QueueImpl>, renderium::Error>;
    static QueueResult create(const Api::Device& device) {
        auto result = Queue::create(device);
        if (!result.isOk()) {
            return QueueResult::err(renderium::Error::QueueCreateError);
        }
        return QueueResult::ok(std::unique_ptr<QueueImpl>(new QueueImpl(std::move(result.unwrap()))));
    }
private:
    explicit QueueImpl(Queue queue) : queue(std::move(queue)) {}

    Queue queue;
};

}