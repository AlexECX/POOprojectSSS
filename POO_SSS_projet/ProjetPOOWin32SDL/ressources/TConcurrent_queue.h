#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>

template<typename Data>
class concurrent_queue
{
private:
	std::queue<Data> the_queue;
	std::mutex the_mutex;
	std::condition_variable the_condition_variable;
public:
	void push_back(Data const& data)
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		//boost::mutex::scoped_lock lock(the_mutex);
		the_queue.push(data);
		lock.unlock();
		the_condition_variable.notify_one();
	}

	Data const& front() 
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		return the_queue.front();
	}

	bool empty() 
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		//boost::mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	void pop_front()
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		//boost::mutex::scoped_lock lock(the_mutex);
		the_queue.pop();
	}

	bool try_pop(/*Data& popped_value*/)
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		//boost::mutex::scoped_lock lock(the_mutex);
		if (the_queue.empty())
		{
			return false;
		}

		/*popped_value = the_queue.front();*/
		the_queue.pop();
		return true;
	}

	void wait_and_pop(/*Data& popped_value*/)
	{
		std::unique_lock<std::mutex> lock(the_mutex);
		//boost::mutex::scoped_lock lock(the_mutex);
		while (the_queue.empty())
		{
			the_condition_variable.wait(lock);
		}

		/*popped_value = the_queue.front();*/
		the_queue.pop();
	}

};

