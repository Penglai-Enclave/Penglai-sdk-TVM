#include "psa_crypto_interface.h"

//Currently using the uniform key to encrypt or decrypt the fs
static byte k1[32] =
    {
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
    };

static byte k1_origin[32] =
    {
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
    };

/* FIXME: add the tag length to the crypto buffer size to account for the tag
 * being appended to the ciphertext by the crypto layer.
 */
static uint8_t sst_crypto_iv_buf[SST_IV_LEN_BYTES];

void sst_crypto_get_iv(union sst_crypto_t *crypto)
{
    uint64_t iv_l;
    uint32_t iv_h;

    (void)memcpy(&iv_l, sst_crypto_iv_buf, sizeof(iv_l));
    (void)memcpy(&iv_h, (sst_crypto_iv_buf+sizeof(iv_l)), sizeof(iv_h));
    iv_l++;
    /* If overflow, increment the MSBs */
    if (iv_l == 0) {
        iv_h++;
    }

    /* Update the local buffer */
    (void)memcpy(sst_crypto_iv_buf, &iv_l, sizeof(iv_l));
    (void)memcpy((sst_crypto_iv_buf + sizeof(iv_l)), &iv_h, sizeof(iv_h));
    /* Update the caller buffer */
    (void)memcpy(crypto->ref.iv, sst_crypto_iv_buf, SST_IV_LEN_BYTES);
}

void sst_crypto_set_iv(const union sst_crypto_t *crypto)
{
    (void)memcpy(sst_crypto_iv_buf, crypto->ref.iv, SST_IV_LEN_BYTES);
}

psa_status_t psa_aesgcm_decrypt(
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *tag,
                              size_t tag_len,
                              const uint8_t *ciphertext,
                              size_t ciphertext_length,
                              uint8_t *plaintext,
                              size_t plaintext_size,
                              size_t *plaintext_length)
{
    psa_status_t status;
    int ret;
    Aes dec;
    wc_AesInit(&dec, NULL, -2);                         
    wc_AesGcmSetKey(&dec, k1, sizeof(k1));
    // eapp_print("//psa_aesgcm_decrypt: nonce\n");
    // for (int i = 0; i < nonce_length; i++)
    // {
    //     eapp_print("%c", *(nonce + i));
    // }
    // eapp_print("\n//psa_aesgcm_decrypt: additional_data\n");
    // for (int i = 0; i < additional_data_length; i++)
    // {
    //     eapp_print("%c", *(additional_data + i));
    // }
    // eapp_print("\n//psa_aesgcm_decrypt: tag\n");
    // for (int i = 0; i < tag_len; i++)
    // {
    //     eapp_print("%c", *(tag + i));
    // }
    // eapp_print("\n//psa_aesgcm_decrypt: ciphertext\n");
    // for (int i = 0; i < ciphertext_length; i++)
    // {
    //     eapp_print("%c", *(ciphertext + i));
    // }
    ret = wc_AesGcmDecrypt(&dec, plaintext, ciphertext, ciphertext_length,
                        nonce, nonce_length, tag, tag_len, additional_data, additional_data_length);
    if (ret < 0)
    {
        eapp_print("psa_aesgcm_decrypt: wc_AesGcmDecrypt is failed, err id %d\n", ret);
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    *plaintext_length = ciphertext_length;
    return PSA_SUCCESS;
}

psa_status_t psa_aesgcm_encrypt(
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *tag,
                              size_t tag_len,
                              const uint8_t *plaintext,
                              size_t plaintext_length,
                              uint8_t *ciphertext,
                              size_t ciphertext_size,
                              size_t *ciphertext_length)
{
    psa_status_t status;
    int ret;
    Aes enc;
    wc_AesInit(&enc, NULL, -2);
    wc_AesGcmSetKey(&enc, k1, sizeof(k1));
    ret = wc_AesGcmEncrypt(&enc, ciphertext, plaintext, plaintext_length,
                        nonce, nonce_length, tag, tag_len, additional_data, additional_data_length);
    // eapp_print("//psa_aesgcm_encrypt: nonce\n");
    // for (int i = 0; i < nonce_length; i++)
    // {
    //     eapp_print("%c", *(nonce + i));
    // }
    // eapp_print("\n//psa_aesgcm_encrypt: additional_data\n");
    // for (int i = 0; i < additional_data_length; i++)
    // {
    //     eapp_print("%c", *(additional_data + i));
    // }
    // eapp_print("\n//psa_aesgcm_encrypt: tag\n");
    // for (int i = 0; i < tag_len; i++)
    // {
    //     eapp_print("%c", *(tag + i));
    // }
    // if (ret < 0)
    // {
    //     eapp_print("psa_aesgcm_decrypt: wc_AesGcmDecrypt is failed \n");
    //     return PSA_ERROR_INVALID_SIGNATURE;
    // }
    *ciphertext_length = plaintext_length;
    // eapp_print("\n//psa_aesgcm_decrypt: ciphertext\n");
    // for (int i = 0; i < *ciphertext_length; i++)
    // {
    //     eapp_print("%c", *(ciphertext + i));
    // }
    return PSA_SUCCESS;
}

psa_status_t sst_crypto_auth_and_decrypt(const union sst_crypto_t *crypto,
                                         const uint8_t *add,
                                         size_t add_len,
                                         uint8_t *in,
                                         size_t in_len,
                                         uint8_t *out,
                                         size_t out_size,
                                         size_t *out_len,
                                         uint8_t *salt,
                                         size_t salt_len)
{
    psa_status_t status;

    int ret_derivation = wc_HKDF(WC_SHA256, k1_origin, sizeof(k1), salt, salt_len,
    NULL, 0, k1, sizeof(k1));
    if(ret_derivation < 0)
    {
        eapp_print("sst_crypto_auth_and_decrypt: wc_HKDF is failed \n");
    }
    status = psa_aesgcm_decrypt(crypto->ref.iv, SST_IV_LEN_BYTES,
                              add, add_len,
                              crypto->ref.tag, SST_TAG_LEN_BYTES,
                              in, in_len,
                              out, out_size, out_len);
    if (status != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    return PSA_SUCCESS;
}

psa_status_t sst_crypto_encrypt_and_tag(union sst_crypto_t *crypto,
                                        const uint8_t *add,
                                        size_t add_len,
                                        const uint8_t *in,
                                        size_t in_len,
                                        uint8_t *out,
                                        size_t out_size,
                                        size_t *out_len,
                                        uint8_t *salt,
                                        size_t salt_len)
{
    psa_status_t status;
    int ret_derivation = wc_HKDF(WC_SHA256, k1_origin, sizeof(k1), salt, salt_len,
    NULL, 0, k1, sizeof(k1));
    if(ret_derivation < 0)
    {
        eapp_print("sst_crypto_encrypt_and_tag: wc_HKDF is failed \n");
    }
    status = psa_aesgcm_encrypt(crypto->ref.iv, SST_IV_LEN_BYTES,
                              add, add_len,
                              crypto->ref.tag, SST_TAG_LEN_BYTES,
                              in, in_len,
                              out, out_size, out_len);
  
    if (status != PSA_SUCCESS) {
        eapp_print("sst_crypto_encrypt_and_tag: psa_aesgcm_encrypt is failed \n");
        return PSA_ERROR_GENERIC_ERROR;
    }

    return PSA_SUCCESS;
}

psa_status_t sst_crypto_generate_auth_tag(union sst_crypto_t *crypto,
                                          const uint8_t *add,
                                          uint32_t add_len,
                                          uint8_t *salt,
                                          size_t salt_len)
{
    psa_status_t status;
    size_t out_len;
    int ret_derivation = wc_HKDF(WC_SHA256, k1_origin, sizeof(k1), salt, salt_len,
    NULL, 0, k1, sizeof(k1));
    if(ret_derivation < 0)
    {
        eapp_print("sst_crypto_generate_auth_tag: wc_HKDF is failed \n");
    }
    status = psa_aesgcm_encrypt(
                              crypto->ref.iv, SST_IV_LEN_BYTES,
                              add, add_len,
                              crypto->ref.tag, SST_TAG_LEN_BYTES, 
                              NULL, 0,
                              NULL, 0, &out_len);
    if (status != PSA_SUCCESS) {
        eapp_print("sst_crypto_generate_auth_tag: psa_aesgcm_encrypt is failed \n");
        return PSA_ERROR_GENERIC_ERROR;
    }

    return PSA_SUCCESS;
}

psa_status_t sst_crypto_authenticate(const union sst_crypto_t *crypto,
                                     const uint8_t *add,
                                     uint32_t add_len,
                                     uint8_t *salt,
                                     size_t salt_len)
{
    psa_status_t status;
    size_t out_len;
    int ret_derivation = wc_HKDF(WC_SHA256, k1_origin, sizeof(k1), salt, salt_len,
    NULL, 0, k1, sizeof(k1));
    if(ret_derivation < 0)
    {
        eapp_print("sst_crypto_authenticate: wc_HKDF is failed \n");
    }
    status = psa_aesgcm_decrypt(crypto->ref.iv, SST_IV_LEN_BYTES,
                              add, add_len,
                              crypto->ref.tag, SST_TAG_LEN_BYTES,
                              NULL, 0,
                              NULL, 0, &out_len);
    if (status != PSA_SUCCESS) {
        eapp_print("sst_crypto_authenticate: psa_aesgcm_decrypt is failed \n");
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    return PSA_SUCCESS;
}