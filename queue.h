#if !defined(QUEUE_H)
#define QUEUE_H

#include <string_view>
#include <deque>
#include <mutex>

class NetQueue
{
    private:
        std::deque<std::string> queue;
        // std::mutex mux;

    public:
        NetQueue()
        {}

        virtual ~NetQueue() {
            // clear all data from the queue - make its size 0
            queue.clear();
        }

        int size() const
        {
            // std::scoped_lock lock(mux);
            return static_cast<int>(queue.size());
        }

        bool empty() const
        {
            // std::scoped_lock lock(mux);
            return queue.empty();
        }

        std::string &front()
        {
            // std::scoped_lock lock(mux);
            return queue.front();
        }

        std::string &back()
        {
            // std::scoped_lock lock(mux);
            return queue.back();
        }

        void push_front(std::string msg)
        {
            // std::scoped_lock lock(mux);
            queue.emplace_front(
                std::move(msg)
                );
        }

        void push_back(std::string msg)
        {
            // std::scoped_lock lock(mux);
            queue.emplace_back(
                std::move(msg)
                );
        }

        std::string pop_front()
        {
            std::string toReturn{std::move(queue.front())};
            queue.pop_front();
            return toReturn;
        }

        std::string pop_back()
        {
            std::string toReturn{std::move(queue.back())};
            queue.pop_back();
            return toReturn;
        }

};

#endif