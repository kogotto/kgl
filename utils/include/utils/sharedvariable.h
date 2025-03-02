#include <utility>
#include <mutex>

namespace ut {

template <typename Lock, typename Data>
class LockedPtr {
public:

    LockedPtr(Lock&& lock, Data& data):
        lock(std::move(lock)), data(data)
    {}

    Data& operator*() & {
        return data;
    }

    const Data& operator*() const& {
        return data;
    }

    Data& operator*() && {
        // some crush
    }

    Data* operator->() & {
        return &data;
    }

    const Data* operator->() const& {
        return &data;
    }

    Data* operator->() && {
        // some crush
    }

private:
    Lock lock;
    Data& data;
};

template <typename Data, typename Mutex = std::mutex>
class Variable {
public:

    template <typename... Args>
    Variable(Args&&... args):
        data(std::forward<Args>(args)...)
    {}

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;

    Variable(Variable&&) = default;
    Variable& operator=(Variable&&) = default;

    LockedPtr<std::unique_lock<Mutex>, Data> uniqueLock() {
        return {std::unique_lock{mutex}, data};
    }

    LockedPtr<std::unique_lock<Mutex>, const Data> uniqueLock() const {
        return {std::unique_lock{mutex}, data};
    }

private:
    mutable Mutex mutex;
    Data data;
};

} // namespace ut
