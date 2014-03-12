// Please download and extract a copy of the PolarSSL code from
//   their official site and use that - how do you know where my
//   code has been?

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "config.h"

// Below are the PolarSSL files we actually need.
#include "polarssl-1.3.4/include/polarssl/md5.h"
#include "polarssl-1.3.4/include/polarssl/sha1.h"
// sha256.h is named sha2.h in earlier PolarSSL versions
#include "polarssl-1.3.4/include/polarssl/sha256.h"
// sha512.h is named sha4.h in earlier PolarSSL versions
#include "polarssl-1.3.4/include/polarssl/sha512.h"
#include "polarssl-1.3.4/include/polarssl/pkcs5.h"
#include <getopt.h>
#include "polarssl-1.3.4/include/polarssl/version.h"


#define MD5_polarssl           100
#define SHA_1_polarssl         2100
#define SHA_224_polarssl       2200
#define SHA_256_polarssl       2300
#define SHA_384_polarssl       2400
#define SHA_512_polarssl       2500

// Binary printing courtesy https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 


uint8_t constantTimeCompare(uint8_t a[], uint32_t aLen, uint8_t b[], uint32_t bLen)
    {
        // Not quite constant time unless aLen == bLen
        uint8_t compare;
        uint32_t i;
        compare = aLen ^ bLen;
        for (i = 0; i < aLen && i < bLen; i++)
            compare |= (uint8_t)(a[i] ^ b[i]);
        return compare == 0;
    }

int PBKDF2_HMAC_MD5_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t md5_ctx;
    const md_info_t *info_md5;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_md5 = md_info_from_type( POLARSSL_MD_MD5 );
    if( info_md5 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &md5_ctx, info_md5 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &md5_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &md5_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}



int PBKDF2_HMAC_SHA_1_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t sha1_ctx;
    const md_info_t *info_sha1;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_sha1 = md_info_from_type( POLARSSL_MD_SHA1 );
    if( info_sha1 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &sha1_ctx, info_sha1 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &sha1_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &sha1_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}


int PBKDF2_HMAC_SHA_224_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t sha224_ctx;
    const md_info_t *info_sha224;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_sha224 = md_info_from_type( POLARSSL_MD_SHA224 );
    if( info_sha224 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &sha224_ctx, info_sha224 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &sha224_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &sha224_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}

int PBKDF2_HMAC_SHA_256_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t sha256_ctx;
    const md_info_t *info_sha256;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_sha256 = md_info_from_type( POLARSSL_MD_SHA256 );
    if( info_sha256 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &sha256_ctx, info_sha256 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &sha256_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &sha256_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}


int PBKDF2_HMAC_SHA_384_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t sha384_ctx;
    const md_info_t *info_sha384;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_sha384 = md_info_from_type( POLARSSL_MD_SHA384 );
    if( info_sha384 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &sha384_ctx, info_sha384 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &sha384_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &sha384_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}



int PBKDF2_HMAC_SHA_512_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    md_context_t sha512_ctx;
    const md_info_t *info_sha512;
    int ret, i;
    unsigned char digest[outputBytes];

    // credit to https://github.com/polarssl/polarssl/blob/development/library/pkcs5.c pkcs5_self_test

    info_sha512 = md_info_from_type( POLARSSL_MD_SHA512 );
    if( info_sha512 == NULL )
        return( 104 );

    if( ( ret = md_init_ctx( &sha512_ctx, info_sha512 ) ) != 0 )
        return( 103 );

    ret = pkcs5_pbkdf2_hmac( &sha512_ctx, pass, strlen(pass), salt,
                              strlen(salt), iterations, outputBytes, digest );
    if( ret != 0 )
    {
        return( 102 );
    }

    if( ( ret = md_free_ctx( &sha512_ctx ) ) != 0 )
        return( 101 );

    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);

    return(0);
}

/*

int PBKDF2_HMAC_SHA_512_NearlyReferenceOpt1_string(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
//NearlyReferenceOpt1: The first PBKDF2 optimization is to unroll the HMAC, since we can precompute both inner and outer pads only once. 

// we will be using the PolarSSL sha512 function void sha512( const unsigned char *input, size_t ilen, unsigned char output[64], int is384 );



}
*/



int main(int argc, char **argv)
{
  char *pass = NULL;
  char *salt = NULL;
  char *expected = NULL;
  char *algoString = NULL;
  uint32_t iterations = 0;
  uint32_t outputBytes = 0;
  uint16_t algo = 0;
  int c;
  uint8_t verbose = 0;
  uint8_t help = 0;
  uint8_t interactive = 0;
  char version[64];
  
  // Interactive mode vars below
  size_t maxLen = 65535;
  char *inPass;
  char *inSalt;
  char *inIterations;
  char *inOutputBytes;
  char *inAlgoString;
  inPass = (char *) calloc (maxLen + 1,1);
  inSalt = (char *) calloc (maxLen + 1,1);
  inIterations = (char *) calloc (maxLen + 1,1);
  inOutputBytes = (char *) calloc (maxLen + 1,1);
  inAlgoString = (char *) calloc (maxLen + 1,1);


  opterr = 0;
  
  while ((c = getopt (argc, argv, "nhva:p:P:s:S:i:o:O:e:")) != -1)
    switch (c)
      {
      case 'a':
        algoString = optarg;
        break;
      case 'p':
        pass = optarg;
        break;
      case 's':
        salt = optarg;
        break;
      case 'i':
        iterations = atoi(optarg);
        break;
      case 'o':
        outputBytes = atoi(optarg);
        break;
      case 'v':
        verbose = 1;
        break;
      case 'h':
        help = 1;
        break;
      case 'e':
        expected = optarg;
        break;
      case 'n':
        interactive = 1;
        break;
      case '?':
        puts("Case ?");fflush;
       if (optopt == 'c')
         fprintf (stderr, "Option -%c requires an argument.\n", optopt);
       else if (isprint (optopt))
         fprintf (stderr, "Unknown option `-%c'.\n", optopt);
       else
         fprintf (stderr,
                  "Unknown option character `\\x%x'.\n",
                  optopt);
       return 1;
      default:
        puts("Case default");fflush;
        break;//abort ();
      }
      
  if (help)
    {
    printf("Compiled with the source code of PolarSSL, version: %s",POLARSSL_VERSION_STRING_FULL);
    #ifdef POLARSSL_SHA512_ALT
      puts(" POLARSSL_SHA512_ALT 1");
    #endif
    version_get_string_full(version);
    printf(" Running with the source code of PolarSSL, version: %s\n",version);
    printf("Example: %s -a SHA-512 -p password -s salt -i 131072 -o 64\n",argv[0]);
    puts("\nOptions: ");
    puts("  -h                 help");
    puts("  -v                 Verbose");
    puts("  -a algo            algorithm, valid values SHA-512|SHA-384|SHA-256|SHA-224|SHA-1|MD5   Note that in particular, SHA-384 and SHA-512 use 64-bit operations which as of 2014 penalize GPU's (attackers) much, much more than CPU's (you).  Use one of these two if at all possible.");
    puts("  -p password        Password to hash");
    puts("  -P passwordfmt     NOT YET IMPLEMENTED - always string");
    puts("  -s salt            Salt for the hash.  Should be long and cryptographically random.");
    puts("  -S saltfmt         NOT YET IMPLEMENTED - always string");
    puts("  -i iterations      Number of iterations, as high as you can handle the delay for, at least 16384 recommended.");
    puts("  -o bytes           Number of bytes of output; for password hashing, keep less than or equal to native hash size (MD5 <=16, SHA-1 <=20, SHA-256 <=32, SHA-512 <=64)");
    puts("  -O outputfmt       Output format NOT YET IMPLEMENTED - always HEX (lowercase)");
    puts("  -e hash            Expected hash (in the same format as outputfmt) results in output of 0 <actual> <expected> = different, 1 = same NOT YET IMPLEMENTED");
    puts("  -n                 Interactive mode - DOES NOT NEED other command line arguments");
    }
     

  if (interactive)
    {
    int lenRead;
    puts("Enter pass: ");
    lenRead = getline (&inPass, &maxLen, stdin);
    inPass[lenRead-1] = 0;
    puts("Enter salt: ");
    lenRead = getline (&inSalt, &maxLen, stdin);
    inSalt[lenRead-1] = 0;
    puts("Enter iterations: ");
    lenRead = getline (&inIterations, &maxLen, stdin);
    puts("Enter outputBytes: ");
    lenRead = getline (&inOutputBytes, &maxLen, stdin);
    puts("Enter algorithm - valid values are one of SHA-512|SHA-384|SHA-256|SHA-224|SHA-1|MD5: ");
    lenRead = getline (&inAlgoString, &maxLen, stdin);
    inAlgoString[lenRead-1] = 0;
    pass = inPass;    
    salt = inSalt;
    iterations = atoi(inIterations);
    outputBytes = atoi(inOutputBytes);
    algoString = inAlgoString;
    
    // Yes, for real we'd actually check lenRead to see if there were error conditions.
    //  std::cout << "Enter expected result hash (lower case hex): ";
    //  std::cin >> expected;
    }

  if (strcmp(algoString,"SHA-512")==0)
    {
      algo = SHA_512_polarssl;
    }
  else if (strcmp(algoString,"SHA-384")==0)
    {
      algo = SHA_384_polarssl;
    }
  else if (strcmp(algoString,"SHA-256")==0)
    {
      algo = SHA_256_polarssl;
    }
  else if (strcmp(algoString,"SHA-224")==0)
    {
      algo = SHA_224_polarssl;
    }
  else if (strcmp(algoString,"SHA-1")==0)
    {
      algo = SHA_1_polarssl;
    }
  else if (strcmp(algoString,"MD5")==0)
    {
      algo = MD5_polarssl;
    }
  else
    {
      printf("ERROR: -a argument '%s' unknown.\n",algoString);
      return 4;
    }





  if (verbose)
    {
    printf("Interpreted arguments: algo %i password %s salt %s iterations %i outputbytes %i\n\n",algo,pass,salt,iterations,outputBytes);
    }

  if (algo <= 0)
    {
    puts("You must select a known algorithm identifier.");
    return 10;
    }

  if (iterations <= 0)
    {
    puts("You must select at least one iteration (and preferably tens of thousands or (much) more.");
    return 11;
    }

  if (outputBytes <= 0)
    {
    puts("You must select at least one byte of output length.");
    return 12;
    }
    
  // 2*outputBytes+1 is 2 hex bytes per binary byte, and one character at the end for the string-terminating \0
  char hexResult[2*outputBytes+1];
  memset(hexResult,0,sizeof(hexResult));
  char binResult[outputBytes];
  memset(hexResult,0,sizeof(binResult));

//    printf("Computing PBKDF2(HMAC-SHA512, '%s', '%s', %d, %d) ...\n", pass, salt, iterations, outputBytes);
  switch (algo)
    {
    case SHA_512_polarssl:
      if (verbose && outputBytes > 64)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_SHA_512_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    case SHA_384_polarssl:
      if (verbose && outputBytes > 48)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_SHA_384_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    case SHA_256_polarssl:
      if (verbose && outputBytes > 32)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_SHA_256_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    case SHA_224_polarssl:
      if (verbose && outputBytes > 28)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_SHA_224_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    case SHA_1_polarssl:
      if (verbose && outputBytes > 20)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_SHA_1_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    case MD5_polarssl:
      if (verbose && outputBytes > 16)
      {
        puts("WARNING: If you intend to use the result for password hashing, you should not choose a length greater than the native output size of the underlying hash function.");
      }
      PBKDF2_HMAC_MD5_string(pass, salt, iterations, outputBytes, hexResult);
      break;
    default:
      printf("Invalid algorithm choice.  Internal value %i\n",algo);
      return 2;
    }

  if (expected == NULL)
    {
    // Normal output
    printf("%s\n", hexResult);
    }
  else 
    {
    // Did it match or not?
    if (constantTimeCompare(expected,strlen(expected),hexResult,strlen(hexResult)))
      {
      puts("1");
      }
    else
      {
      printf("0 %s %s\n",hexResult,expected);
      }
    }
    
  
  return 0;
}
