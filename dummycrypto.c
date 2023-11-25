#include <windows.h>
#include <stdbool.h>

#include "CRYPTO/pwd2key.h"
#include "CRYPTO/aes.h"


static void __attribute__((noreturn)) not_implemented(void)
{
    MessageBox(NULL, "Not implemented", "Not implemented. Try using GPG to encrypt.", MB_OK);
    while (true)
    {
        asm("int $3");
    }
}

void derive_key(
        const unsigned char pwd[],   /* the PASSWORD, and   */
        unsigned int pwd_len,        /*    its length       */ 
        const unsigned char salt[],  /* the SALT and its    */
        unsigned int salt_len,       /*    length           */
        unsigned int iter,      /* the number of iterations */
        unsigned char key[],    /* space for the output key */
        unsigned int key_len)   /* and its required length  */
{
    not_implemented();
}

AES_RETURN aes_encrypt_key(const unsigned char *key, int key_len, aes_encrypt_ctx cx[1])
{
    not_implemented();
}

AES_RETURN aes_decrypt_key(const unsigned char *key, int key_len, aes_decrypt_ctx cx[1])
{
    not_implemented();
}

AES_RETURN aes_cbc_encrypt(const unsigned char *ibuf, unsigned char *obuf,
                    int len, unsigned char *iv, const aes_encrypt_ctx cx[1])
{
    not_implemented();
}

AES_RETURN aes_cbc_decrypt(const unsigned char *ibuf, unsigned char *obuf,
                    int len, unsigned char *iv, const aes_decrypt_ctx cx[1])
{
    not_implemented();
}

