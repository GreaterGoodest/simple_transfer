#include <psa/crypto.h>
#include <string.h>
#include <stdlib.h>

#include "crypto.h"

const psa_algorithm_t alg = PSA_ALG_GCM;
const size_t tag_len = PSA_AEAD_TAG_LENGTH( PSA_KEY_TYPE_AES, KEY_SIZE_BITS, alg );

int encrypt(uint8_t *input_buffer, uint8_t *output_buffer, int len, size_t *ciphertext_len)
{
    int result = 0;

    //Arrays are technically data structures...
    const uint8_t key[16] = { 0x36, 0x86, 0x42, 0x00, 0xe0, 0xea, 0xf5, 0x28,
                            0x4d, 0x88, 0x4a, 0x0e, 0x77, 0xd3, 0x16, 0x46 };


    const uint8_t iv[BLOCK_SIZE] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
                                    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    result = psa_crypto_init(); 
    if (PSA_SUCCESS != result)
    {
        printf("Failed to init crypto system: %d\n", result);
        return 1;
    }

    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_id_t psa_key = PSA_KEY_ID_NULL;
    psa_set_key_usage_flags( &attributes, PSA_KEY_USAGE_ENCRYPT );
    psa_set_key_algorithm( &attributes, alg );
    psa_set_key_type( &attributes, PSA_KEY_TYPE_AES );

    result = psa_import_key(&attributes, key, sizeof(key), &psa_key);
    if (PSA_SUCCESS != result) {
        printf("Failed to import key: %d\n", result);
        return 1;
    }

    result = psa_aead_encrypt( psa_key, alg, iv, sizeof(iv), NULL, 0,
                            input_buffer, len, output_buffer, len + tag_len, ciphertext_len);

    if (PSA_SUCCESS != result)
    {
        printf("psa_aead_encrypt failed: %d\n", result);
        return 1;
    }

    return 0;
}
