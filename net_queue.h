#include <deque>
#include <mutex>


class NetQueue
{
    private:
        std::deque<int> queue;
        std::mutex mux;

    public:
        NetQueue()
        {}

        virtual ~NetQueue() {
            // clear all data from the queue - make its size 0
            queue.clear();
        }

        int size() const
        {
            std::scoped_lock lock(mux);
            return queue.size();
        }

        bool empty() const
        {
            std::scoped_lock lock(mux);
            return queue.empty();
        }

        int &front()
        {
            std::scoped_lock lock(mux);
            return queue.front();
        }

        int &back()
        {
            std::scoped_lock lock(mux);
            return queue.back();
        }

        // void push_front(int &msg)
        // {
        //     std::scoped_lock lock(mux);
        //     queue.emplace_front(
        //         std::move(msg)
        //     );
        // }

        // void push_back(int &msg)
        // {
        //     std::scoped_lock lock(mux);
        //     queue.emplace_back(
        //         std::move(msg)
        //     );
        // }

};