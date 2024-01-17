#pragma once
#include <psa/crypto.h>

#define BLOCK_SIZE      PSA_BLOCK_CIPHER_BLOCK_LENGTH( PSA_KEY_TYPE_AES )
#define KEY_SIZE_BITS   128

extern const psa_algorithm_t alg;
extern const size_t tag_len;

int encrypt(uint8_t *input_buffer, uint8_t *output_buffer, int len, size_t *ciphertext_len);