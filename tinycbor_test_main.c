//  Demo Program for TinyCBOR on NuttX
#include <nuttx/config.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../libs/libtinycbor/src/cbor.h"     //  For Tiny CBOR Library

static void test_cbor(void);
static void test_cbor2(void);

/// Main Program
int main(int argc, FAR char *argv[]) {
    //  Test CBOR Encoding for { "t": 1234 }
    test_cbor();

    //  Test CBOR Encoding for { "t": 1234, "l": 2345 }
    test_cbor2();
    return 0;
}

/// Test CBOR Encoding for { "t": 1234 }
static void test_cbor(void) {
    puts("test_cbor: Encoding { \"t\": 1234 }");

    //  Max output size is 50 bytes (which fits in a LoRa packet)
    uint8_t output[50];

    //  Our CBOR Encoder and Map Encoder
    CborEncoder encoder, mapEncoder;

    //  Init our CBOR Encoder
    cbor_encoder_init(
        &encoder,        //  CBOR Encoder
        output,          //  Output Buffer
        sizeof(output),  //  Output Buffer Size
        0                //  Options
    );

    //  Create a Map Encoder that maps keys to values
    CborError res = cbor_encoder_create_map(
        &encoder,     //  CBOR Encoder
        &mapEncoder,  //  Map Encoder
        1             //  Number of Key-Value Pairs
    );    
    assert(res == CborNoError);

    //  First Key-Value Pair: Map the Key
    res = cbor_encode_text_stringz(
        &mapEncoder,  //  Map Encoder
        "t"           //  Key
    );    
    assert(res == CborNoError);

    //  First Key-Value Pair: Map the Value
    res = cbor_encode_int(
        &mapEncoder,  //  Map Encoder 
        1234          //  Value
    );
    assert(res == CborNoError);

    //  Close the Map Encoder
    res = cbor_encoder_close_container(
        &encoder,    //  CBOR Encoder
        &mapEncoder  //  Map Encoder
    );
    assert(res == CborNoError);

    //  How many bytes were encoded
    size_t output_len = cbor_encoder_get_buffer_size(
        &encoder,  //  CBOR Encoder
        output     //  Output Buffer
    );
    printf("CBOR Output: %d bytes\n", output_len);

    //  Dump the encoded CBOR output (6 bytes):
    //  0xa1 0x61 0x74 0x19 0x04 0xd2
    for (int i = 0; i < output_len; i++) {
        printf("  0x%02x\n", output[i]);
    }
    puts("");
}

/// Test CBOR Encoding for { "t": 1234, "l": 2345 }
static void test_cbor2(void) {
    puts("test_cbor2: Encoding { \"t\": 1234, \"l\": 2345 }");

    //  Max output size is 50 bytes (which fits in a LoRa packet)
    uint8_t output[50];

    //  Our CBOR Encoder and Map Encoder
    CborEncoder encoder, mapEncoder;

    //  Init our CBOR Encoder
    cbor_encoder_init(
        &encoder,        //  CBOR Encoder
        output,          //  Output Buffer
        sizeof(output),  //  Output Buffer Size
        0                //  Options
    );

    //  Create a Map Encoder that maps keys to values
    CborError res = cbor_encoder_create_map(
        &encoder,     //  CBOR Encoder
        &mapEncoder,  //  Map Encoder
        2             //  Number of Key-Value Pairs
    );    
    assert(res == CborNoError);

    //  First Key-Value Pair: Map the Key
    res = cbor_encode_text_stringz(
        &mapEncoder,  //  Map Encoder
        "t"           //  Key
    );    
    assert(res == CborNoError);

    //  First Key-Value Pair: Map the Value
    res = cbor_encode_int(
        &mapEncoder,  //  Map Encoder 
        1234          //  Value
    );
    assert(res == CborNoError);

    //  Second Key-Value Pair: Map the Key
    res = cbor_encode_text_stringz(
        &mapEncoder,  //  Map Encoder
        "l"           //  Key
    );    
    assert(res == CborNoError);

    //  Second Key-Value Pair: Map the Value
    res = cbor_encode_int(
        &mapEncoder,  //  Map Encoder 
        2345          //  Value
    );
    assert(res == CborNoError);

    //  Close the Map Encoder
    res = cbor_encoder_close_container(
        &encoder,    //  CBOR Encoder
        &mapEncoder  //  Map Encoder
    );
    assert(res == CborNoError);

    //  How many bytes were encoded
    size_t output_len = cbor_encoder_get_buffer_size(
        &encoder,  //  CBOR Encoder
        output     //  Output Buffer
    );
    printf("CBOR Output: %d bytes\n", output_len);

    //  Dump the encoded CBOR output (11 bytes):
    //  0xa2 0x61 0x74 0x19 0x04 0xd2 0x61 0x6c 0x19 0x09 0x29
    for (int i = 0; i < output_len; i++) {
        printf("  0x%02x\n", output[i]);
    }
    puts("");
}

/* 
Output Log:

nsh> tinycbor_test
test_cbor: Encoding { "t": 1234 }
CBOR Output: 6 bytes
  0xa1
  0x61
  0x74
  0x19
  0x04
  0xd2
test_cbor2: Encoding { "t": 1234, "l": 2345 }
CBOR Output: 11 bytes
  0xa2
  0x61
  0x74
  0x19
  0x04
  0xd2
  0x61
  0x6c
  0x19
  0x09
  0x29
*/