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
class SharedVariable {
public:

    template <typename... Args>
    SharedVariable(Args&&... args):
        data(std::forward<Args>(args)...)
    {}

    SharedVariable(const SharedVariable&) = delete;
    SharedVariable& operator=(const SharedVariable&) = delete;

    SharedVariable(SharedVariable&&) = default;
    SharedVariable& operator=(SharedVariable&&) = default;

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
