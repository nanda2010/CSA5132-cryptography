#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generateDSAKey(DSA **dsa)
{
    *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(*dsa);
}

void generateRSAKey(RSA **rsa)
{
    *rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
}

void signDSA(DSA *dsa, const unsigned char *msg, size_t msg_len)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    DSA_SIG *signature;

    SHA1(msg, msg_len, hash);
    signature = DSA_do_sign(hash, SHA_DIGEST_LENGTH, dsa);

    printf("DSA Signature: %s\n", BN_bn2hex(signature->r));
    printf("%s\n", BN_bn2hex(signature->s));

    DSA_SIG_free(signature);
}

void signRSA(RSA *rsa, const unsigned char *msg, size_t msg_len)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    unsigned char signature[RSA_size(rsa)];
    unsigned int sig_len;

    SHA1(msg, msg_len, hash);
    RSA_sign(NID_sha1, hash, SHA_DIGEST_LENGTH, signature, &sig_len, rsa);

    printf("RSA Signature: ");
    for (int i = 0; i < sig_len; ++i)
        printf("%02x", signature[i]);
    printf("\n");
}

int main()
{
    DSA *dsa_key;
    RSA *rsa_key;

    unsigned char msg[] = "This is a message to be signed.";

    printf("Generating DSA key pair...\n");
    generateDSAKey(&dsa_key);

    printf("Generating RSA key pair...\n");
    generateRSAKey(&rsa_key);

    printf("Signing the message with DSA...\n");
    signDSA(dsa_key, msg, strlen((const char *)msg));

    printf("\n");

    printf("Signing the message with RSA...\n");
    signRSA(rsa_key, msg, strlen((const char *)msg));

    DSA_free(dsa_key);
    RSA_free(rsa_key);

    return 0;
}
