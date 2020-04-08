//
//  format-base6.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "format-base6.hpp"

#include <stdexcept>

#include "params.hpp"
#include "utils.hpp"
#include "random.hpp"

void FormatBase6::process_input(Params* p) {
    auto input = p->get_one_argument();
    auto entropy = digits_to_data(input, 0, 5);
    p->seed = deterministic_random(entropy, p->count);
}

void FormatBase6::process_output(Params* p) {
    p->output = data_to_ints(p->seed, 0, 5, "");
}
