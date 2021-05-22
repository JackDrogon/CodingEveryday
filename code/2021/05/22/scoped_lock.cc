#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace
{
struct Employee {
	Employee(std::string id_arg) : id(id_arg)
	{
	}

	std::string output() const
	{
		std::string ret = "Employee " + id + " has lunch partners: ";
		for (const auto &partner : lunch_partners) {
			ret += (partner + " ");
		}
		return ret;
	}

	std::string id;
	std::vector<std::string> lunch_partners;
	std::mutex mutex;
};

void send_mail(Employee &, Employee &)
{
	// simulate a time-consuming messaging operation
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void assign_lunch_partner(Employee &employee1, Employee &employee2)
{
	static std::mutex io_mutex;
	{
		std::lock_guard<std::mutex> lk(io_mutex);

		std::cout << employee1.id << " and " << employee2.id
			  << " are waiting for locks" << std::endl;
	}

	{
		// use std::scoped_lock to acquire two locks without worrying about
		// other calls to assign_lunch_partner deadlocking us
		// and it also provides a convenient RAII-style mechanism

		// Equivalent code 1 (using std::lock and std::lock_guard)
		// std::lock(employee1.m, employee2.m);
		// std::lock_guard<std::mutex> lk1(employee1.m, std::adopt_lock);
		// std::lock_guard<std::mutex> lk2(employee2.m, std::adopt_lock);

		// Equivalent code 2 (if unique_locks are needed, e.g. for condition variables)
		// std::unique_lock<std::mutex> lk1(employee1.m, std::defer_lock);
		// std::unique_lock<std::mutex> lk2(employee2.m, std::defer_lock);
		// std::lock(lk1, lk2);
		std::scoped_lock lock(employee1.mutex, employee2.mutex);
		{
			std::lock_guard<std::mutex> lk(io_mutex);
			std::cout << employee1.id << " and " << employee2.id
				  << " got locks" << std::endl;
		}
		employee1.lunch_partners.push_back(employee2.id);
		employee2.lunch_partners.push_back(employee1.id);
	}

	send_mail(employee1, employee2);
	send_mail(employee2, employee1);
}
} // namespace

int main()
{
	Employee alice("alice"), bob("bob"), christina("christina"),
		dave("dave");

	// assign in parallel threads because mailing users about lunch assignments
	// takes a long time
	std::vector<std::thread> threads;
	threads.emplace_back(assign_lunch_partner, std::ref(alice),
			     std::ref(bob));
	threads.emplace_back(assign_lunch_partner, std::ref(christina),
			     std::ref(bob));
	threads.emplace_back(assign_lunch_partner, std::ref(christina),
			     std::ref(alice));
	threads.emplace_back(assign_lunch_partner, std::ref(dave),
			     std::ref(bob));

	for (auto &thread : threads) {
		thread.join();
	}

	std::cout << alice.output() << '\n'
		  << bob.output() << '\n'
		  << christina.output() << '\n'
		  << dave.output() << '\n';
}
