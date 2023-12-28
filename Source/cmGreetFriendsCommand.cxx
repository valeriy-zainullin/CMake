/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include "cmGreetFriendsCommand.h"

#include "cmExecutionStatus.h"
#include "cmSystemTools.h"

#include <cassert>
#include <iostream>
#include <random>

struct RandomIndexGen {
    std::mt19937_64 generator;
    std::uniform_int_distribution<size_t> distribution;

    static std::random_device::result_type get_seed() {
        std::random_device rd;
//        return std::random_device()();
        return rd();
    }

    RandomIndexGen(size_t num_items)
        : generator(get_seed()), distribution(0, num_items - 1) {
        assert(num_items != 0);
    }

    size_t get_index() {
        // May result in entropy loss (if size_t is greater than 64 :)),
        //   but it's alright for our purposes.
        return distribution(generator);
    }

    RandomIndexGen(RandomIndexGen&&) = default;
};

// cmGreetFriendsCommand
bool cmGreetFriendsCommand(std::vector<std::string> const& args,
                    cmExecutionStatus& status)
{
  if (!args.empty()) {
    status.SetError("called with incorrect number of arguments");
    return false;
  }

   static std::vector<std::string_view> messages = {
      "Hello, friends!",
      "Well, hello friends!",
      "Yo! How's it going man?",
      "Внимание, сегодня вам повезло (use UTF-8). "
      "Вы получили неожиданное сообщение от дальнего друга, который желает вам удачи!"
  };

  static RandomIndexGen generator(messages.size());

  size_t index = generator.get_index();
  // Will retry 1 time if gets a lucky message. So it should be less probable than
  //   any more regular message. Should be a really lucky one.
  // Wanted to do 3 initially, but then nobody's going to see the lucky message.
  // Easy to calculate assuming experiments "obtaining a random number"
  //   are independent (which should be so). Also, they are uniformly distributed (at least we try
  //   to make them like this with uniform_int_distrubution).
  // 1/4, 1/4, 1/4, 1/4
  //                1/4, 1/4, 1/4, 1/4
  // 1/4 + 1/4 * 1/4, (repeats 2 times more), 1/4 * 1/4
  for (size_t i = 0; i < 1 && index == messages.size() - 1; ++i) {
      index = generator.get_index();
  }

  std::cout << messages[index] << std::endl;

  return true;
}
