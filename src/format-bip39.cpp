//
//  format-bip39.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "format-bip39.hpp"

#include <strings.h>
#include <bc-bip39/bc-bip39.h>

#include "params.hpp"
#include "utils.hpp"

bool format_bip39_is_seed_length_valid(size_t seed_len) {
    if(!(12 <= seed_len && seed_len <= 32)) { return false; }
    if(seed_len % 2 != 0) { return false; }
    return true;
}

void format_bip39_process_output(format* f, params* p) {
    if(!format_bip39_is_seed_length_valid(p->seed.size())) { return; }

    size_t max_mnemonics_len = 300;
    char mnemonics[max_mnemonics_len];
    size_t len = bip39_mnemonics_from_secret(&p->seed[0], p->seed.size(), mnemonics, max_mnemonics_len);
    char* string = (char*)malloc(len);
    strcpy(string, mnemonics);
    p->output = string;
}

static void format_bip39_dispose(format* f) {
    free(f);
}

format* format_bip39_new() {
    format* f = (format*)calloc(sizeof(format), 1);
    f->key = format_key_bip39;
    f->name = "bip39";
    f->process_output = format_bip39_process_output;
    f->dispose = format_bip39_dispose;
    return f;
}
