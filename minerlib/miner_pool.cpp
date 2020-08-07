#include "miner_pool.h"
#include "mining_algorithm.h"
#include <boost/bind.hpp>
#include <iostream>

namespace stratum
{
	miner_pool::miner_pool(unsigned thread_num) :
		working_(io_service_),
        thread_num_(thread_num),
        target_cpu_usage_(0.5),
        initial_sleep_frequency_(0.5)
	{
		start();
	}

	miner_pool::~miner_pool()
	{
		stop();
	}

	void miner_pool::set_job(const binary& blob, uint32_t target, job_callback cb)
	{
		stop();
		for (unsigned i = 0; i < thread_num_; i++)
			io_service_.post(boost::bind(&miner_pool::calc, blob,
			target, 
			std::numeric_limits<uint32_t>::max() / thread_num_ * i, 
            cb, std::ref(stop_flag_), std::ref(hashes_), target_cpu_usage_,
            std::ref(initial_sleep_frequency_)));
		start();
	}

	void miner_pool::stop_current_job()
	{
		stop();
	}

    void miner_pool::calc(const binary& blob, uint32_t target,
        uint32_t start_nonce, job_callback cb,
        std::atomic_flag& stop, hash_counter& hashes,
        double target_cpu_usage,
        std::atomic<double> &initial_sleep_frequency)
	{
		std::unique_ptr<mining_algorithm> alg =
			mining_algorithm::factory(mining_algorithm::CRYPTONIGHT, blob,
			target, start_nonce);
        cpuload cpu;
        unsigned count = 1;
        unsigned sleep_count = 0;
        double sleep_frequency = initial_sleep_frequency;
		while (stop.test_and_set())
		{
            if (double(sleep_count) / double(count + sleep_count) < sleep_frequency) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);
                sleep_count++;
            } else {
                if (alg->process_next_nonce())
                    cb(alg->nonce(), alg->binary_res());
                count++;
            }
            if((count + sleep_count) % 100 == 0)
            {
                double current_cpu_usage = cpu.usage();
                if ( current_cpu_usage > target_cpu_usage)
                    sleep_frequency *= std::min(2.0, current_cpu_usage / target_cpu_usage);
                else
                    sleep_frequency /= std::min(1.5, target_cpu_usage / current_cpu_usage);
            }
		}
		hashes.add_hashes(count);
        initial_sleep_frequency = sleep_frequency;
		stop.clear();
	}

	void miner_pool::stop()
	{
		io_service_.stop();
		stop_flag_.clear();
		for (auto& t : pool_)
			t.join();
		pool_.clear();
	}

	void miner_pool::start()
	{
		stop_flag_.test_and_set();
		io_service_.reset();
		for (unsigned i = 0; i < thread_num_; i++)
		{
			pool_.push_back(
				std::thread(
					boost::bind(&boost::asio::io_service::run, &io_service_)
				)
			);
		}
	}

	double miner_pool::hash_per_second() const
	{
        return hashes_.hash_per_second();
    }

    double miner_pool::cpu_usage() const
    {
        double res = cpu_.usage();
        cpu_.reset();
        return res;
    }

}
